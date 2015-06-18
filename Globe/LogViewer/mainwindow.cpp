
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2014 Igor Mironchik

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

// LogViewer include.
#include <LogViewer/mainwindow.hpp>
#include <LogViewer/configuration.hpp>
#include <LogViewer/log.hpp>

// Globe include.
#include <Globe/Core/log_event_selector.hpp>
#include <Globe/Core/log_event_view.hpp>
#include <Globe/Core/select_query_navigation.hpp>

// Qt include.
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QWidget>
#include <QSqlQuery>
#include <QApplication>

// QtConfFile include.
#include <QtConfFile/Utils>


namespace LogViewer {

//
// MainWindowPrivate
//

class MainWindowPrivate {
public:
	MainWindowPrivate()
		:	m_selector( 0 )
		,	m_view( 0 )
		,	m_logPageSize( 30 )
		,	m_havePrevLogPage( false )
		,	m_haveNextLogPage( false )
		,	m_pos( 0 )
	{
	}

	//! Selector.
	Globe::LogEventSelector * m_selector;
	//! View.
	Globe::LogEventView * m_view;
	//! Query.
	QSqlQuery m_query;
	//! Size of the log page.
	int m_logPageSize;
	//! Have previous log page.
	bool m_havePrevLogPage;
	//! Have next log page.
	bool m_haveNextLogPage;
	//! Position in query.
	int m_pos;
}; // class MainWindowPrivate


//
// MainWindow
//

MainWindow::MainWindow( QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new MainWindowPrivate )
{
	init();
}

MainWindow::~MainWindow()
{
}

static MainWindow * mainWindowInstancePointer = 0;

void
MainWindow::cleanup()
{
	delete mainWindowInstancePointer;

	mainWindowInstancePointer = 0;
}

MainWindow &
MainWindow::instance()
{
	if( !mainWindowInstancePointer )
	{
		mainWindowInstancePointer = new MainWindow;

		qAddPostRoutine( &MainWindow::cleanup );
	}

	return *mainWindowInstancePointer;
}

void
MainWindow::init()
{
	setWindowTitle( tr( "Event Log" ) );

	QWidget * centralWidget = new QWidget( this );

	QVBoxLayout * layout = new QVBoxLayout( centralWidget );

	d->m_selector = new Globe::LogEventSelector( centralWidget );

	setNavigationButtons();

	d->m_view = new Globe::LogEventView( centralWidget );

	layout->addWidget( d->m_selector );
	layout->addWidget( d->m_view );

	setCentralWidget( centralWidget );

	connect( d->m_selector->navigationWidget(),
		&Globe::SelectQueryNavigation::executeButtonClicked,
		this, &MainWindow::selectFromLog );
	connect( d->m_selector->navigationWidget(),
		&Globe::SelectQueryNavigation::goToNextPageButtonClicked,
		this, &MainWindow::nextLogPage );
	connect( d->m_selector->navigationWidget(),
		&Globe::SelectQueryNavigation::goToPreviousPageButtonClicked,
		this, &MainWindow::prevLogPage );
	connect( d->m_selector->navigationWidget(),
		&Globe::SelectQueryNavigation::goToStartPageButtonClicked,
		this, &MainWindow::goToFirstLogPage );
	connect( d->m_selector->navigationWidget(),
		&Globe::SelectQueryNavigation::goToEndPageButtonClicked,
		this, &MainWindow::goToLastLogPage );

	connect( &Log::instance(), &Log::error,
		this, &MainWindow::logError );
	connect( &Log::instance(), &Log::ready,
		this, &MainWindow::logReady );
	connect( &Configuration::instance(), &Configuration::error,
		this, &MainWindow::cfgError );
}

void
MainWindow::setNavigationButtons()
{
	if( d->m_havePrevLogPage )
		d->m_selector->navigationWidget()->enablePreviousButtons( true );
	else
		d->m_selector->navigationWidget()->enablePreviousButtons( false );

	if( d->m_haveNextLogPage )
		d->m_selector->navigationWidget()->enableNextButtons( true );
	else
		d->m_selector->navigationWidget()->enableNextButtons( false );
}

QList< Globe::LogEventRecord >
MainWindow::readLog()
{
	QList< Globe::LogEventRecord > records;

	int size = 0;

	do
	{
		Globe::LogEventRecord record(
			(Globe::LogLevel) d->m_query.value( 0 ).toInt(),
			d->m_query.value( 1 ).toString(),
			d->m_query.value( 2 ).toString() );

		records.append( record );

		++size;
		++d->m_pos;

		if( size == d->m_logPageSize )
			break;
	} while( d->m_query.next() );

	return records;
}

QList< Globe::LogEventRecord >
MainWindow::readLogFirstTime()
{
	QList< Globe::LogEventRecord > records;

	int size = 0;

	while( d->m_query.next() )
	{
		Globe::LogEventRecord record(
			(Globe::LogLevel) d->m_query.value( 0 ).toInt(),
			d->m_query.value( 1 ).toString(),
			d->m_query.value( 2 ).toString() );

		records.append( record );

		++size;
		++d->m_pos;

		if( size == d->m_logPageSize )
			break;
	}

	return records;
}

void
MainWindow::start()
{
	show();

	Configuration::instance().readConfiguration();

	Log::instance().init();
}

void
MainWindow::cfgError( const QString & what )
{
	QMessageBox::critical( this, tr( "Error in configuration..." ),
		what );

	qApp->quit();
}

void
MainWindow::logError()
{
	QMessageBox::critical( this, tr( "Unable to open database..." ),
		tr( "Unable to open database." ) );

	qApp->quit();
}

void
MainWindow::logReady()
{
}

void
MainWindow::selectFromLog()
{
	d->m_pos = 0;
	d->m_haveNextLogPage = false;
	d->m_havePrevLogPage = false;

	d->m_query = Log::instance().readEventLog( d->m_selector->startDateTime(),
		d->m_selector->endDateTime() );

	QList< Globe::LogEventRecord > records = readLogFirstTime();

	if( d->m_query.next() )
		d->m_haveNextLogPage = true;
	else
		d->m_haveNextLogPage = false;

	setNavigationButtons();

	d->m_view->model()->initModel( records );

	d->m_view->resizeColumnToContents( 0 );
}

void
MainWindow::nextLogPage()
{
	d->m_havePrevLogPage = true;

	QList< Globe::LogEventRecord > records;

	if( d->m_query.seek( d->m_pos ) )
	{
		records = readLog();

		if( d->m_query.next() )
			d->m_haveNextLogPage = true;
		else
		{
			d->m_haveNextLogPage = false;
			d->m_pos += ( d->m_logPageSize - ( d->m_pos % d->m_logPageSize ) );
		}
	}
	else
		d->m_haveNextLogPage = false;

	setNavigationButtons();

	d->m_view->model()->initModel( records );
}

void
MainWindow::prevLogPage()
{
	d->m_haveNextLogPage = true;

	QList< Globe::LogEventRecord > records;

	d->m_pos -= ( d->m_logPageSize * 2 );

	if( !d->m_pos )
		d->m_havePrevLogPage = false;

	if( d->m_query.seek( d->m_pos ) )
	{
		if( d->m_query.previous() )
			d->m_havePrevLogPage = true;
		else
			d->m_havePrevLogPage = false;

		d->m_query.next();

		records = readLog();
	}
	else
		d->m_haveNextLogPage = false;

	setNavigationButtons();

	d->m_view->model()->initModel( records );
}

void
MainWindow::goToFirstLogPage()
{
	d->m_pos = 0;
	d->m_haveNextLogPage = true;
	d->m_havePrevLogPage = false;

	QList< Globe::LogEventRecord > records;

	d->m_query.seek( d->m_pos );

	records = readLog();

	setNavigationButtons();

	d->m_view->model()->initModel( records );
}

void
MainWindow::goToLastLogPage()
{
	d->m_haveNextLogPage = false;
	d->m_havePrevLogPage = true;

	do {
		d->m_pos += d->m_logPageSize;
	} while( d->m_query.seek( d->m_pos ) );

	d->m_pos -= d->m_logPageSize;

	d->m_query.seek( d->m_pos );

	QList< Globe::LogEventRecord > records = readLog();

	d->m_pos += ( d->m_logPageSize - ( d->m_pos % d->m_logPageSize ) );

	setNavigationButtons();

	d->m_view->model()->initModel( records );
}

} /* namespace LogViewer */

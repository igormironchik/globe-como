
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2013 Igor Mironchik

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

// Globe include.
#include <Globe/log_sources_window.hpp>
#include <Globe/tool_window_object.hpp>
#include <Globe/log.hpp>
#include <Globe/log_sources_selector.hpp>
#include <Globe/log_sources_view.hpp>
#include <Globe/select_query_navigation.hpp>
#include <Globe/log_sources_window_cfg.hpp>
#include <Globe/globe_menu.hpp>

// Qt include.
#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QWidget>
#include <QSqlQuery>

// QtConfFile include.
#include <QtConfFile/Utils>


namespace Globe {

//
// LogSourcesWindowPrivate
//

class LogSourcesWindowPrivate {
public:
	LogSourcesWindowPrivate()
		:	m_toolWindowObject( 0 )
		,	m_selector( 0 )
		,	m_view( 0 )
		,	m_logPageSize( 100 )
		,	m_havePrevLogPage( false )
		,	m_haveNextLogPage( false )
		,	m_pos( 0 )
	{
	}

	//! Tool window object.
	ToolWindowObject * m_toolWindowObject;
	//! Selector.
	LogSourcesSelector * m_selector;
	//! View.
	LogSourcesView * m_view;
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
}; // class LogSourcesWindowPrivate


//
// LogSourcesWindow
//

LogSourcesWindow::LogSourcesWindow( QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new LogSourcesWindowPrivate )
{
	init();
}

LogSourcesWindow::~LogSourcesWindow()
{
}

LogSourcesWindow &
LogSourcesWindow::instance()
{
	static LogSourcesWindow inst;

	return inst;
}

ToolWindowObject *
LogSourcesWindow::toolWindowObject()
{
	return d->m_toolWindowObject;
}

void
LogSourcesWindow::saveConfiguration( const QString & fileName )
{
	try {
		LogSourcesCfgTag tag( LogSourcesCfg( windowStateCfg( this ) ) );

		QtConfFile::writeQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
			"Sources log window configuration saved into \"%1\" file." )
				.arg( fileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to save sources log window configuration to file "
			"\"%1\".\n"
			"%2" )
				.arg( fileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( 0,
			tr( "Unable to save sources log window configuration..." ),
			tr( "Unable to save sources log window configuration...\n\n%1" )
				.arg( x.whatAsQString() ) );
	}
}

void
LogSourcesWindow::readConfiguration( const QString & fileName )
{
	LogSourcesCfgTag tag;

	try {
		QtConfFile::readQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
			"Sources log window configuration loaded from file \"%1\"." )
				.arg( fileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to read sources log window configuration from file "
			"\"%1\".\n"
			"%2" )
				.arg( fileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( 0,
			tr( "Unable to read sources log window configuration..." ),
			tr( "Unable to read sources log window configuration...\n\n%1" )
				.arg( x.whatAsQString() ) );

		return;
	}

	restoreWindowState( tag.cfg().windowState(), this );
}

void
LogSourcesWindow::initMenu( const Menu & menu )
{
	menuBar()->addMenu( menu.fileMenu() );

	QMenu * toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );

	foreach( ToolWindowObject * obj, menu.toolWindows() )
		if( obj != d->m_toolWindowObject )
			toolsMenu->addAction( obj->menuEntity() );

	menuBar()->addMenu( menu.settingsMenu() );
}

void
LogSourcesWindow::closeEvent( QCloseEvent * event )
{
	hide();

	event->accept();
}

void
LogSourcesWindow::init()
{
	setWindowTitle( tr( "Sources Log" ) );

	QAction * showAction = new QAction( tr( "So&urces Log" ), this );
	showAction->setShortcut( QKeySequence( tr( "Alt+U" ) ) );
	d->m_toolWindowObject = new ToolWindowObject( showAction, this, this );

	QWidget * centralWidget = new QWidget( this );

	QVBoxLayout * layout = new QVBoxLayout( centralWidget );

	d->m_selector = new LogSourcesSelector( centralWidget );

	setNavigationButtons();

	d->m_view = new LogSourcesView( centralWidget );

	layout->addWidget( d->m_selector );
	layout->addWidget( d->m_view );

	setCentralWidget( centralWidget );

	connect( d->m_selector->navigationWidget(), SIGNAL( executeButtonClicked() ),
		this, SLOT( selectFromLog() ) );
	connect( d->m_selector->navigationWidget(),
		SIGNAL( goToNextPageButtonClicked() ), this,
		SLOT( nextLogPage() ) );
	connect( d->m_selector->navigationWidget(),
		SIGNAL( goToPreviousPageButtonClicked() ), this,
		SLOT( prevLogPage() ) );
	connect( d->m_selector->navigationWidget(),
		SIGNAL( goToStartPageButtonClicked() ), this,
		SLOT( goToFirstLogPage() ) );
	connect( d->m_selector->navigationWidget(),
		SIGNAL( goToEndPageButtonClicked() ), this,
		SLOT( goToLastLogPage() ) );
}

void
LogSourcesWindow::setNavigationButtons()
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

QList< LogSourcesRecord >
LogSourcesWindow::readLog()
{
	QList< LogSourcesRecord > records;

	int size = 0;

	do
	{
		LogSourcesRecord record( d->m_query.value( 0 ).toString(),
			d->m_query.value( 1 ).toString(),
			Como::Source( (Como::Source::Type) d->m_query.value( 2 ).toInt(),
				d->m_query.value( 3 ).toString(),
				d->m_query.value( 4 ).toString(),
				d->m_query.value( 5 ),
				d->m_query.value( 6 ).toString() ) );

		records.append( record );

		++size;
		++d->m_pos;

		if( size == d->m_logPageSize )
			break;
	} while( d->m_query.next() );

	return records;
}

QList< LogSourcesRecord >
LogSourcesWindow::readLogFirstTime()
{
	QList< LogSourcesRecord > records;

	int size = 0;

	while( d->m_query.next() )
	{
		LogSourcesRecord record( d->m_query.value( 0 ).toString(),
			d->m_query.value( 1 ).toString(),
			Como::Source( (Como::Source::Type) d->m_query.value( 2 ).toInt(),
				d->m_query.value( 3 ).toString(),
				d->m_query.value( 4 ).toString(),
				d->m_query.value( 5 ),
				d->m_query.value( 6 ).toString() ) );

		records.append( record );

		++size;
		++d->m_pos;

		if( size == d->m_logPageSize )
			break;
	}

	return records;
}

void
LogSourcesWindow::selectFromLog()
{
	d->m_pos = 0;
	d->m_haveNextLogPage = false;
	d->m_havePrevLogPage = false;

	d->m_query = Log::instance().readSourcesLog( d->m_selector->startDateTime(),
		d->m_selector->endDateTime(),
		d->m_selector->channelName(),
		d->m_selector->sourceName(),
		d->m_selector->typeName() );

	QList< LogSourcesRecord > records = readLogFirstTime();

	if( d->m_query.next() )
		d->m_haveNextLogPage = true;
	else
		d->m_haveNextLogPage = false;

	setNavigationButtons();

	d->m_view->model()->initModel( records );

	d->m_view->resizeColumnToContents( 0 );
}

void
LogSourcesWindow::nextLogPage()
{
	d->m_havePrevLogPage = true;

	QList< LogSourcesRecord > records;

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
LogSourcesWindow::prevLogPage()
{
	d->m_haveNextLogPage = true;

	QList< LogSourcesRecord > records;

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
LogSourcesWindow::goToFirstLogPage()
{
	d->m_pos = 0;
	d->m_haveNextLogPage = true;
	d->m_havePrevLogPage = false;

	QList< LogSourcesRecord > records;

	d->m_query.seek( d->m_pos );

	records = readLog();

	setNavigationButtons();

	d->m_view->model()->initModel( records );
}

void
LogSourcesWindow::goToLastLogPage()
{
	d->m_haveNextLogPage = false;
	d->m_havePrevLogPage = true;

	do {
		d->m_pos += d->m_logPageSize;
	} while( d->m_query.seek( d->m_pos ) );

	d->m_pos -= d->m_logPageSize;

	d->m_query.seek( d->m_pos );

	QList< LogSourcesRecord > records = readLog();

	d->m_pos += ( d->m_logPageSize - ( d->m_pos % d->m_logPageSize ) );

	setNavigationButtons();

	d->m_view->model()->initModel( records );
}

} /* namespace Globe */

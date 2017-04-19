
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Globe include.
#include <Globe/Core/log_event_view_window.hpp>
#include <Globe/Core/tool_window_object.hpp>
#include <Globe/Core/log.hpp>
#include <Globe/Core/log_event_selector.hpp>
#include <Globe/Core/log_event_view.hpp>
#include <Globe/Core/select_query_navigation.hpp>
#include <Globe/Core/log_event_view_window_cfg.hpp>
#include <Globe/Core/globe_menu.hpp>

// Qt include.
#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QWidget>
#include <QSqlQuery>
#include <QCoreApplication>

// QtConfFile include.
#include <QtConfFile/Utils>


namespace Globe {

//
// LogEventWindowPrivate
//

class LogEventWindowPrivate {
public:
	LogEventWindowPrivate()
		:	m_toolWindowObject( 0 )
		,	m_selector( 0 )
		,	m_view( 0 )
		,	m_logPageSize( 30 )
		,	m_havePrevLogPage( false )
		,	m_haveNextLogPage( false )
		,	m_pos( 0 )
	{
	}

	//! Tool window object.
	ToolWindowObject * m_toolWindowObject;
	//! Selector.
	LogEventSelector * m_selector;
	//! View.
	LogEventView * m_view;
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
}; // class LogEventWindowPrivate


//
// LogEventWindow
//

LogEventWindow::LogEventWindow( QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new LogEventWindowPrivate )
{
	init();
}

LogEventWindow::~LogEventWindow()
{
}

static LogEventWindow * logEventWindowInstancePointer = 0;

void
LogEventWindow::cleanup()
{
	delete logEventWindowInstancePointer;

	logEventWindowInstancePointer = 0;
}

LogEventWindow &
LogEventWindow::instance()
{
	if( !logEventWindowInstancePointer )
	{
		logEventWindowInstancePointer = new LogEventWindow;

		qAddPostRoutine( &LogEventWindow::cleanup );
	}

	return *logEventWindowInstancePointer;
}

ToolWindowObject *
LogEventWindow::toolWindowObject()
{
	return d->m_toolWindowObject;
}

void
LogEventWindow::saveConfiguration( const QString & fileName )
{
	try {
		LogEventCfgTag tag( LogEventCfg( windowStateCfg( this ) ) );

		QtConfFile::writeQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
			"Event's log window configuration saved into \"%1\" file." )
				.arg( fileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to save event's log window configuration to file "
			"\"%1\".\n"
			"%2" )
				.arg( fileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( 0,
			tr( "Unable to save event's log window configuration..." ),
			tr( "Unable to save event's log window configuration...\n\n%1" )
				.arg( x.whatAsQString() ) );
	}
}

void
LogEventWindow::readConfiguration( const QString & fileName )
{
	LogEventCfgTag tag;

	try {
		QtConfFile::readQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
			"Event's log window configuration loaded from file \"%1\"." )
				.arg( fileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to read event's log window configuration from file "
			"\"%1\".\n"
			"%2" )
				.arg( fileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( 0,
			tr( "Unable to read event's log window configuration..." ),
			tr( "Unable to read event's log window configuration...\n\n%1" )
				.arg( x.whatAsQString() ) );

		return;
	}

	restoreWindowState( tag.cfg().windowState(), this );
}

void
LogEventWindow::initMenu( const Menu & menu )
{
	menuBar()->addMenu( menu.fileMenu() );

	QMenu * toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );

	foreach( ToolWindowObject * obj, menu.toolWindows() )
		if( obj != d->m_toolWindowObject )
			toolsMenu->addAction( obj->menuEntity() );

	menuBar()->addMenu( menu.settingsMenu() );
}

void
LogEventWindow::closeEvent( QCloseEvent * event )
{
	hide();

	event->accept();
}

void
LogEventWindow::init()
{
	setWindowTitle( tr( "Event Log" ) );

	QAction * showAction = new QAction( tr( "Event &Log" ), this );
	showAction->setShortcut( QKeySequence( tr( "Alt+L" ) ) );
	d->m_toolWindowObject = new ToolWindowObject( showAction, this, this );

	QWidget * centralWidget = new QWidget( this );

	QVBoxLayout * layout = new QVBoxLayout( centralWidget );

	d->m_selector = new LogEventSelector( centralWidget );

	setNavigationButtons();

	d->m_view = new LogEventView( centralWidget );

	layout->addWidget( d->m_selector );
	layout->addWidget( d->m_view );

	setCentralWidget( centralWidget );

	connect( d->m_selector->navigationWidget(),
		&SelectQueryNavigation::executeButtonClicked,
		this, &LogEventWindow::selectFromLog );
	connect( d->m_selector->navigationWidget(),
		&SelectQueryNavigation::goToNextPageButtonClicked,
		this, &LogEventWindow::nextLogPage );
	connect( d->m_selector->navigationWidget(),
		&SelectQueryNavigation::goToPreviousPageButtonClicked,
		this, &LogEventWindow::prevLogPage );
	connect( d->m_selector->navigationWidget(),
		&SelectQueryNavigation::goToStartPageButtonClicked,
		this, &LogEventWindow::goToFirstLogPage );
	connect( d->m_selector->navigationWidget(),
		&SelectQueryNavigation::goToEndPageButtonClicked,
		this, &LogEventWindow::goToLastLogPage );
}

void
LogEventWindow::setNavigationButtons()
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

QList< LogEventRecord >
LogEventWindow::readLog()
{
	QList< LogEventRecord > records;

	int size = 0;

	do
	{
		LogEventRecord record( (LogLevel) d->m_query.value( 0 ).toInt(),
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

QList< LogEventRecord >
LogEventWindow::readLogFirstTime()
{
	QList< LogEventRecord > records;

	int size = 0;

	while( d->m_query.next() )
	{
		LogEventRecord record( (LogLevel) d->m_query.value( 0 ).toInt(),
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
LogEventWindow::selectFromLog()
{
	d->m_pos = 0;
	d->m_haveNextLogPage = false;
	d->m_havePrevLogPage = false;

	d->m_query = Log::instance().readEventLog( d->m_selector->startDateTime(),
		d->m_selector->endDateTime() );

	QList< LogEventRecord > records = readLogFirstTime();

	if( d->m_query.next() )
		d->m_haveNextLogPage = true;
	else
		d->m_haveNextLogPage = false;

	setNavigationButtons();

	d->m_view->model()->initModel( records );

	d->m_view->resizeColumnToContents( 0 );
}

void
LogEventWindow::nextLogPage()
{
	d->m_havePrevLogPage = true;

	QList< LogEventRecord > records;

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
LogEventWindow::prevLogPage()
{
	d->m_haveNextLogPage = true;

	QList< LogEventRecord > records;

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
LogEventWindow::goToFirstLogPage()
{
	d->m_pos = 0;
	d->m_haveNextLogPage = true;
	d->m_havePrevLogPage = false;

	QList< LogEventRecord > records;

	d->m_query.seek( d->m_pos );

	records = readLog();

	setNavigationButtons();

	d->m_view->model()->initModel( records );
}

void
LogEventWindow::goToLastLogPage()
{
	d->m_haveNextLogPage = false;
	d->m_havePrevLogPage = true;

	do {
		d->m_pos += d->m_logPageSize;
	} while( d->m_query.seek( d->m_pos ) );

	d->m_pos -= d->m_logPageSize;

	d->m_query.seek( d->m_pos );

	QList< LogEventRecord > records = readLog();

	d->m_pos += ( d->m_logPageSize - ( d->m_pos % d->m_logPageSize ) );

	setNavigationButtons();

	d->m_view->model()->initModel( records );
}

} /* namespace Globe */

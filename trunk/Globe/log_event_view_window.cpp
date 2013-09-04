
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
#include <Globe/log_event_view_window.hpp>
#include <Globe/tool_window_object.hpp>
#include <Globe/log.hpp>
#include <Globe/log_event_selector.hpp>
#include <Globe/log_event_view.hpp>

// Qt include.
#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QWidget>

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
	{
	}

	//! Tool window object.
	ToolWindowObject * m_toolWindowObject;
	//! Selector.
	LogEventSelector * m_selector;
	//! View.
	LogEventView * m_view;
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

ToolWindowObject *
LogEventWindow::toolWindowObject()
{
	return d->m_toolWindowObject;
}

void
LogEventWindow::saveConfiguration( const QString & fileName )
{
//	try {
//		SourcesMainWindowTag tag( d->m_widget->channelName(),
//			windowStateCfg( this ) );

//		QtConfFile::writeQtConfFile( tag, fileName,
//			QTextCodec::codecForName( "UTF-8" ) );

//		Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
//			"Sources main window's configuration saved into \"%1\" file." )
//				.arg( fileName ) );
//	}
//	catch( const QtConfFile::Exception & x )
//	{
//		Log::instance().writeMsgToEventLog( LogLevelError, QString(
//			"Unable to save sources main window's configuration to file "
//			"\"%1\". %2" )
//				.arg( fileName )
//				.arg( x.whatAsQString() ) );

//		QMessageBox::critical( this,
//			tr( "Unable to save sources main window configuration..." ),
//			x.whatAsQString() );
//	}
}

void
LogEventWindow::readConfiguration( const QString & fileName )
{
//	SourcesMainWindowTag tag;

//	try {
//		QtConfFile::readQtConfFile( tag, fileName,
//			QTextCodec::codecForName( "UTF-8" ) );

//		Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
//			"Sources main window's configuration loaded from file \"%1\"." )
//				.arg( fileName ) );
//	}
//	catch( const QtConfFile::Exception & x )
//	{
//		Log::instance().writeMsgToEventLog( LogLevelError, QString(
//			"Unable to read sources main window's configuration from file "
//			"\"%1\". %2" )
//				.arg( fileName )
//				.arg( x.whatAsQString() ) );

//		QMessageBox::critical( this,
//			tr( "Unable to read sources main window configuration..." ),
//			x.whatAsQString() );

//		return;
//	}

//	d->m_widget->setChannelName( tag.channelName() );

//	restoreWindowState( tag.windowState(), this );
}

void
LogEventWindow::initMenu( QMenu * fileMenu, QMenu * settingsMenu,
	const QList< ToolWindowObject* > & toolWindows )
{
	menuBar()->addMenu( fileMenu );

	QMenu * toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );

	foreach( ToolWindowObject * obj, toolWindows )
		if( obj != d->m_toolWindowObject )
			toolsMenu->addAction( obj->menuEntity() );

	menuBar()->addMenu( settingsMenu );
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
	d->m_toolWindowObject = new ToolWindowObject( showAction, this, this );

	QWidget * centralWidget = new QWidget( this );

	QVBoxLayout * layout = new QVBoxLayout( centralWidget );

	d->m_selector = new LogEventSelector( centralWidget );

	d->m_view = new LogEventView( centralWidget );

	layout->addWidget( d->m_selector );
	layout->addWidget( d->m_view );

	setCentralWidget( centralWidget );
}

} /* namespace Globe */

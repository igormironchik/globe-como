
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
#include <Globe/sources_mainwindow.hpp>
#include <Globe/tool_window_object.hpp>
#include <Globe/sources.hpp>
#include <Globe/sources_widget.hpp>
#include <Globe/channels.hpp>
#include <Globe/sources_mainwindow_cfg.hpp>
#include <Globe/log.hpp>
#include <Globe/globe_menu.hpp>

// Qt include.
#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

// QtConfFile include.
#include <QtConfFile/Utils>


namespace Globe {

//
// SourcesMainWindowPrivate
//

class SourcesMainWindowPrivate {
public:
	SourcesMainWindowPrivate()
		:	m_toolWindowObject( 0 )
		,	m_widget( 0 )
	{
	}

	//! Tool window object.
	ToolWindowObject * m_toolWindowObject;
	//! Sources widget.
	SourcesWidget * m_widget;
}; // class SourcesMainWindowPrivate


//
// SourcesMainWindow
//

SourcesMainWindow::SourcesMainWindow( QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new SourcesMainWindowPrivate )
{
	init();
}

SourcesMainWindow::~SourcesMainWindow()
{
}

SourcesMainWindow &
SourcesMainWindow::instance()
{
	static SourcesMainWindow inst;

	return inst;
}

ToolWindowObject *
SourcesMainWindow::toolWindowObject()
{
	return d->m_toolWindowObject;
}

void
SourcesMainWindow::initMenu( const Menu & menu )
{
	menuBar()->addMenu( menu.fileMenu() );

	QMenu * toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );

	foreach( ToolWindowObject * obj, menu.toolWindows() )
		if( obj != d->m_toolWindowObject )
			toolsMenu->addAction( obj->menuEntity() );

	menuBar()->addMenu( menu.settingsMenu() );
}

void
SourcesMainWindow::closeEvent( QCloseEvent * event )
{
	hide();

	event->accept();
}

void
SourcesMainWindow::init()
{
	setWindowTitle( tr( "Sources Manager" ) );

	QAction * showAction = new QAction( tr( "&Sources" ), this );
	d->m_toolWindowObject = new ToolWindowObject( showAction, this, this );

	d->m_widget = new SourcesWidget( this );

	setCentralWidget( d->m_widget );
}

void
SourcesMainWindow::saveConfiguration( const QString & fileName )
{
	try {
		SourcesMainWindowTag tag( d->m_widget->channelName(),
			windowStateCfg( this ) );

		QtConfFile::writeQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
			"Sources main window's configuration saved into \"%1\" file." )
				.arg( fileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to save sources main window's configuration to file "
			"\"%1\".\n"
			"%2" )
				.arg( fileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( 0,
			tr( "Unable to save sources main window configuration..." ),
			x.whatAsQString() );
	}
}

void
SourcesMainWindow::readConfiguration( const QString & fileName )
{
	SourcesMainWindowTag tag;

	try {
		QtConfFile::readQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
			"Sources main window's configuration loaded from file \"%1\"." )
				.arg( fileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to read sources main window's configuration from file "
			"\"%1\".\n"
			"%2" )
				.arg( fileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( 0,
			tr( "Unable to read sources main window configuration..." ),
			x.whatAsQString() );

		return;
	}

	d->m_widget->setChannelName( tag.channelName() );

	restoreWindowState( tag.windowState(), this );
}

} /* namespace Globe */

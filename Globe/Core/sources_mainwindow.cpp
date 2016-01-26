
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

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
#include <Globe/Core/sources_mainwindow.hpp>
#include <Globe/Core/tool_window_object.hpp>
#include <Globe/Core/sources.hpp>
#include <Globe/Core/sources_widget.hpp>
#include <Globe/Core/channels.hpp>
#include <Globe/Core/sources_mainwindow_cfg.hpp>
#include <Globe/Core/log.hpp>
#include <Globe/Core/globe_menu.hpp>

// Qt include.
#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QCoreApplication>

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

static SourcesMainWindow * sourcesMainWindowInstancePointer = 0;

void
SourcesMainWindow::cleanup()
{
	delete sourcesMainWindowInstancePointer;

	sourcesMainWindowInstancePointer = 0;
}

SourcesMainWindow &
SourcesMainWindow::instance()
{
	if( !sourcesMainWindowInstancePointer )
	{
		sourcesMainWindowInstancePointer = new SourcesMainWindow;

		qAddPostRoutine( &SourcesMainWindow::cleanup );
	}

	return *sourcesMainWindowInstancePointer;
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
	showAction->setShortcut( QKeySequence( tr( "Alt+E" ) ) );
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
			tr( "Unable to save sources main window configuration...\n\n%1" )
				.arg( x.whatAsQString() ) );
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
			tr( "Unable to read sources main window configuration...\n\n%1" )
				.arg( x.whatAsQString() ) );

		return;
	}

	d->m_widget->setChannelName( tag.channelName() );

	restoreWindowState( tag.windowState(), this );
}

} /* namespace Globe */

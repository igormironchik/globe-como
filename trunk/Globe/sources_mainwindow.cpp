
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

// Qt include.
#include <QtGui/QCloseEvent>
#include <QtGui/QApplication>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QMessageBox>

// QtConfFile include.
#include <QtConfFile/Utils>


namespace Globe {

//
// SourcesMainWindowPrivate
//

class SourcesMainWindowPrivate {
public:
	SourcesMainWindowPrivate( SourcesManager * sourcesManager,
		ChannelsManager * channelsManager )
		:	m_sourcesManager( sourcesManager )
		,	m_channelsManager( channelsManager )
		,	m_toolWindowObject( 0 )
		,	m_widget( 0 )
	{
	}

	//! Sources manager.
	SourcesManager * m_sourcesManager;
	//! Channels manager.
	ChannelsManager * m_channelsManager;
	//! Tool window object.
	ToolWindowObject * m_toolWindowObject;
	//! Sources widget.
	SourcesWidget * m_widget;
}; // class SourcesMainWindowPrivate


//
// SourcesMainWindow
//

SourcesMainWindow::SourcesMainWindow( SourcesManager * sourcesManager,
	ChannelsManager * channelsManager,
	QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new SourcesMainWindowPrivate( sourcesManager, channelsManager ) )
{
	init();
}

SourcesMainWindow::~SourcesMainWindow()
{
}

ToolWindowObject *
SourcesMainWindow::toolWindowObject()
{
	return d->m_toolWindowObject;
}

void
SourcesMainWindow::initToolsMenu( const QList< ToolWindowObject* > & toolWindows )
{
	QMenu * toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );

	foreach( ToolWindowObject * obj, toolWindows )
		if( obj != d->m_toolWindowObject )
			toolsMenu->addAction( obj->menuEntity() );
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
	QMenu * fileMenu = menuBar()->addMenu( tr( "&File" ) );
	fileMenu->addAction( QIcon( ":/img/exit_22x22.png" ),
		tr( "E&xit" ), qApp, SLOT( quit() ), QKeySequence( tr( "Ctrl+Q" ) ) );

	QAction * showAction = new QAction( tr( "&Sources" ), this );
	d->m_toolWindowObject = new ToolWindowObject( showAction, this, this );

	d->m_widget = new SourcesWidget( d->m_sourcesManager, d->m_channelsManager,
		this );

	setCentralWidget( d->m_widget );
}

void
SourcesMainWindow::saveConfiguration( const QString & fileName )
{
	SourcesMainWindowTag tag( d->m_widget->channelName(),
		windowStateCfg( this ) );

	try {
		QtConfFile::writeQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		QMessageBox::critical( this,
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
	}
	catch( const QtConfFile::Exception & x )
	{
		QMessageBox::critical( this,
			tr( "Unable to read sources main window configuration..." ),
			x.whatAsQString() );

		return;
	}

	d->m_widget->setChannelName( tag.channelName() );

	restoreWindowState( tag.windowState(), this );
}

} /* namespace Globe */

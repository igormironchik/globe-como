
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 Igor Mironchik

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
#include <Globe/mainwindow.hpp>
#include <Globe/channels_list.hpp>
#include <Globe/tool_window_object.hpp>
#include <Globe/configuration.hpp>
#include <Globe/properties.hpp>

// Qt include.
#include <QtGui/QApplication>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QCloseEvent>


namespace Globe {

//
// MainWindowPrivate
//

class MainWindowPrivate {
public:
	MainWindowPrivate( const QString & cfgFileName,
		MainWindow * mainWindow,
		ChannelsManager * channelsManager, DB * db,
		PropertiesManager * propertiesManager,
		const QList< ToolWindowObject* > & toolWindows )
		:	m_channelsManager( channelsManager )
		,	m_db( db )
		,	m_list( 0 )
		,	m_propertiesManager( propertiesManager )
		,	m_cfgWasSaved( false )
		,	m_toolWindows( toolWindows )
		,	m_cfg( cfgFileName, mainWindow, channelsManager,
				db, propertiesManager )
	{
	}

	//! Channels manager.
	ChannelsManager * m_channelsManager;
	//! Database.
	DB * m_db;
	//! List with channels.
	ChannelsList * m_list;
	//! Properties manager.
	PropertiesManager * m_propertiesManager;
	//! Flag that shows was configuration saved or not.
	bool m_cfgWasSaved;
	//! Tool window objects.
	QList< ToolWindowObject* > m_toolWindows;
	//! Configuration.
	Configuration m_cfg;
}; // class MainWindowPrivate


//
// MainWindow
//

MainWindow::MainWindow( const QString & cfgFileName,
	ChannelsManager * channelsManager, DB * db,
	PropertiesManager * propertiesManager,
	const QList< ToolWindowObject* > & toolWindows,
	QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new MainWindowPrivate( cfgFileName, this, channelsManager, db,
			propertiesManager, toolWindows ) )
{
	init();
}

MainWindow::~MainWindow()
{
}

ChannelsList *
MainWindow::list()
{
	return d->m_list;
}

void
MainWindow::init()
{
	connect( qApp, SIGNAL( aboutToQuit() ),
		this, SLOT( aboutToQuit() ) );

	QMenu * fileMenu = menuBar()->addMenu( tr( "&File" ) );
	fileMenu->addAction( QIcon( ":/img/exit_22x22.png" ),
		tr( "E&xit" ), qApp, SLOT( quit() ), QKeySequence( tr( "Ctrl+Q" ) ) );

	QMenu * toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );

	foreach( ToolWindowObject * obj, d->m_toolWindows )
		toolsMenu->addAction( obj->menuEntity() );

	d->m_list = new ChannelsList( d->m_channelsManager,
		ShowAll, Qt::AscendingOrder, this );

	setCentralWidget( d->m_list );

	d->m_propertiesManager->initToolsMenu( d->m_toolWindows );
}

void
MainWindow::start()
{
	d->m_cfg.loadConfiguration();

	show();
}

void
MainWindow::closeEvent( QCloseEvent * event )
{
	event->accept();

	saveConfiguration();

	QApplication::quit();
}

void
MainWindow::aboutToQuit()
{
	saveConfiguration();
}

void
MainWindow::saveConfiguration()
{
	if( !d->m_cfgWasSaved )
	{
		d->m_cfg.saveConfiguration();

		d->m_cfgWasSaved = true;
	}
}

} /* namespace Globe */

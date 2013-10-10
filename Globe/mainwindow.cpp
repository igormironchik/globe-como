
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
#include <Globe/mainwindow.hpp>
#include <Globe/channels_list.hpp>
#include <Globe/tool_window_object.hpp>
#include <Globe/configuration.hpp>
#include <Globe/scrolled_widget.hpp>
#include <Globe/channel_view_window.hpp>
#include <Globe/channel_name_dialog.hpp>
#include <Globe/log.hpp>
#include <Globe/configuration_dialog.hpp>
#include <Globe/globe_menu.hpp>
#include <Globe/properties_manager.hpp>
#include <Globe/sources_mainwindow.hpp>
#include <Globe/log_event_view_window.hpp>
#include <Globe/sources.hpp>
#include <Globe/sounds.hpp>

// Qt include.
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>


namespace Globe {

//
// MainWindowPrivate
//

class MainWindowPrivate {
public:
	MainWindowPrivate()
		:	m_list( 0 )
		,	m_cfgWasSaved( false )
		,	m_confDialog( 0 )
	{
	}

	//! \return Channel view window for the given \arg channelName channel.
	ChannelViewWindow * channelViewWindow( const QString & channelName )
	{
		foreach( ChannelViewWindow * window, m_channelViewWindows )
			if( window->channel() == channelName )
				return window;

		return 0;
	}

	//! List with channels.
	ChannelsList * m_list;
	//! Flag that shows was configuration saved or not.
	bool m_cfgWasSaved;
	//! Channel view windows.
	QList< ChannelViewWindow* > m_channelViewWindows;
	//! Map of the channel view windows configuration.
	QMap< QString, ChannelViewWindowCfg > m_channelViewWindowsCfg;
	//! Configuration dialog.
	ConfigurationDialog * m_confDialog;
	//! Menu.
	Menu m_menu;
}; // class MainWindowPrivate


//
// MainWindow
//

MainWindow::MainWindow( QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new MainWindowPrivate )
{
}

MainWindow::~MainWindow()
{
}

MainWindow &
MainWindow::instance()
{
	static MainWindow inst;

	return inst;
}

ChannelsList *
MainWindow::list()
{
	return d->m_list;
}

void
MainWindow::init( const QList< ToolWindowObject* > & toolWindows )
{
	connect( qApp, SIGNAL( aboutToQuit() ),
		this, SLOT( aboutToQuit() ) );

	QMenu * fileMenu = menuBar()->addMenu( tr( "&File" ) );

	QMenu * newMenu = fileMenu->addMenu( QIcon( ":/img/new_22x22.png" ),
		tr( "New" ) );

	newMenu->addAction( tr( "Channel View" ), this,
		SLOT( newChannelView() ) );

	fileMenu->addSeparator();

	fileMenu->addAction( QIcon( ":/img/exit_22x22.png" ),
		tr( "E&xit" ), qApp, SLOT( quit() ), QKeySequence( tr( "Ctrl+Q" ) ) );

	QMenu * toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );

	QMenu * settingsMenu = menuBar()->addMenu( tr( "&Settings" ) );

	settingsMenu->addAction( QIcon( ":/img/settings_22x22.png" ),
		tr( "&Settings" ), this, SLOT( settings() ) );

	d->m_menu = Menu( fileMenu, settingsMenu, toolWindows );

	foreach( ToolWindowObject * obj, d->m_menu.toolWindows() )
		toolsMenu->addAction( obj->menuEntity() );

	d->m_confDialog = new ConfigurationDialog( this );

	ScrolledView * area = new ScrolledView( this );

	d->m_list = new ChannelsList( ShowAll, Qt::AscendingOrder, this );

	area->setWidget( d->m_list );

	setCentralWidget( area );

	PropertiesManager::instance().initMenu( d->m_menu );
	SourcesMainWindow::instance().initMenu( d->m_menu );
	LogEventWindow::instance().initMenu( d->m_menu );
	Sounds::instance().initMenu( d->m_menu );
}

void
MainWindow::start()
{
	Configuration::instance().loadConfiguration();

	d->m_confDialog->initUiWithSettings();

	Log::instance().writeMsgToEventLog( LogLevelInfo,
		QLatin1String( "Application started." ) );

	show();
}

void
MainWindow::channelViewWindowClosed( ChannelViewWindow * window )
{
	ChannelViewWindowCfg cfg = window->cfg();

	if( d->m_channelViewWindowsCfg.find( cfg.channelName() ) !=
		d->m_channelViewWindowsCfg.end() )
			d->m_channelViewWindowsCfg[ cfg.channelName() ] = cfg;
	else
		d->m_channelViewWindowsCfg.insert( cfg.channelName(), cfg );

	d->m_channelViewWindows.removeAll( window );
}

void
MainWindow::showChannelView( const QString & channelName )
{
	ChannelViewWindow * window = d->channelViewWindow( channelName );

	if( window )
	{
		if( window->isMinimized() )
			window->showNormal();
		else
			window->show();

		window->activateWindow();
	}
	else
	{
		window = new ChannelViewWindow;

		window->initMenu( d->m_menu );

		if( !window->setChannel( channelName ) )
			window->deleteLater();
		else
		{
			d->m_channelViewWindows.append( window );

			if( d->m_channelViewWindowsCfg.find( channelName ) !=
				d->m_channelViewWindowsCfg.end() )
					window->setWindowCfg(
						d->m_channelViewWindowsCfg[ channelName ] );
			else
				window->show();
		}
	}
}

void
MainWindow::closeEvent( QCloseEvent * event )
{
	event->accept();

	saveConfiguration();

	Log::instance().writeMsgToEventLog( LogLevelInfo,
		QLatin1String( "Application finished." ) );

	QApplication::quit();
}

WindowsCfg
MainWindow::windowsCfg() const
{
	WindowsCfg cfg;

	QList< ChannelViewWindowCfg > channelViewWindows;

	foreach( ChannelViewWindow * window, d->m_channelViewWindows )
		channelViewWindows.append( window->cfg() );

	cfg.setChannelViewWindows( channelViewWindows );

	return cfg;
}

void
MainWindow::restoreWindows( const WindowsCfg & cfg )
{
	foreach( const ChannelViewWindowCfg & c, cfg.channelViewWindows() )
	{
		d->m_channelViewWindowsCfg.insert( c.channelName(), c );

		showChannelView( c.channelName() );
	}
}

void
MainWindow::aboutToQuit()
{
	saveConfiguration();

	Log::instance().writeMsgToEventLog( LogLevelInfo,
		QLatin1String( "Application finished." ) );
}

void
MainWindow::newChannelView()
{
	QString channel;

	ChannelNameDialog dlg( channel, SourcesManager::instance().channelsNames(),
		this );

	if( QDialog::Accepted == dlg.exec() )
		showChannelView( channel );
}

void
MainWindow::settings()
{
	if( d->m_confDialog->exec() == QDialog::Accepted )
	{
	}
}

void
MainWindow::saveConfiguration()
{
	if( !d->m_cfgWasSaved )
	{
		Configuration::instance().saveConfiguration();

		d->m_cfgWasSaved = true;
	}
}

} /* namespace Globe */

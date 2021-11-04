
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2020 Igor Mironchik

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
#include <Core/mainwindow.hpp>
#include <Core/channels_list.hpp>
#include <Core/tool_window_object.hpp>
#include <Core/configuration.hpp>
#include <Core/scrolled_widget.hpp>
#include <Core/channel_view_window.hpp>
#include <Core/channel_name_dialog.hpp>
#include <Core/log.hpp>
#include <Core/configuration_dialog.hpp>
#include <Core/globe_menu.hpp>
#include <Core/properties_manager.hpp>
#include <Core/sources_mainwindow.hpp>
#include <Core/log_event_view_window.hpp>
#include <Core/log_sources_window.hpp>
#include <Core/sources.hpp>
#include <Core/sounds.hpp>
#include <Core/utils.hpp>
#include <Core/channels.hpp>

#include <Scheme/window.hpp>

// Qt include.
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>
#include <QFileDialog>
#include <QSessionManager>
#include <QCoreApplication>
#include <QMessageBox>


namespace Globe {

//
// MainWindowPrivate
//

class MainWindowPrivate {
public:
	explicit MainWindowPrivate( MainWindow * parent )
		:	m_list( 0 )
		,	m_cfgWasSaved( false )
		,	m_confDialog( 0 )
		,	m_windows( m_channelViewWindows, m_schemeWindows, m_aggregates,
				parent )
		,	m_menu( Q_NULLPTR )
		,	m_winMenu( Q_NULLPTR )
		,	m_isQuit( false )
	{
	}

	//! \return Channel view window for the given channel.
	ChannelViewWindow * channelViewWindow( const QString & channelName )
	{
		foreach( ChannelViewWindow * window, m_channelViewWindows )
			if( window->channel() == channelName )
				return window;

		return 0;
	}

	//! \return Scheme window for the given configuration file.
	Scheme::Window * schemeWindow( const QString & fileName )
	{
		foreach( Scheme::Window * window, m_schemeWindows )
			if( window->cfg().schemeCfgFile() == fileName )
				return window;

		return 0;
	}

	//! List with channels.
	ChannelsList * m_list;
	//! Flag that shows was configuration saved or not.
	bool m_cfgWasSaved;
	//! Channel view windows.
	QList< ChannelViewWindow* > m_channelViewWindows;
	//! Scheme windows.
	QList< Scheme::Window* > m_schemeWindows;
	//! Aggregate windows.
	QList< Scheme::Window* > m_aggregates;
	//! Map of the channel view windows configuration.
	QMap< QString, ChannelViewWindowCfg > m_channelViewWindowsCfg;
	//! Map of the scheme windows configurations.
	QMap< QString, Scheme::WindowCfg > m_schemeWindowsCfg;
	//! Configuration dialog.
	ConfigurationDialog * m_confDialog;
	//! Windows list auxiliary struct.
	WindowsList m_windows;
	//! Menu.
	QScopedPointer< Menu > m_menu;
	//! Windows menu helper.
	WindowsMenu * m_winMenu;
	//! Is application quit already?
	bool m_isQuit;
}; // class MainWindowPrivate


//
// MainWindow
//

MainWindow::MainWindow( QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new MainWindowPrivate( this ) )
{
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

ChannelsList *
MainWindow::list()
{
	return d->m_list;
}

void
MainWindow::init( const QList< ToolWindowObject* > & toolWindows )
{
	connect( qApp, &QApplication::aboutToQuit,
		this, &MainWindow::aboutToQuit );

	connect( this, &MainWindow::windowCreated,
		this, &MainWindow::updateWindowsMenu );
	connect( this, &MainWindow::windowClosed,
		this, &MainWindow::updateWindowsMenu );

	QMenu * fileMenu = menuBar()->addMenu( tr( "&File" ) );

	QMenu * newMenu = fileMenu->addMenu( QIcon( ":/img/new_22x22.png" ),
		tr( "New" ) );

	newMenu->addAction( tr( "Channel View" ), this,
		SLOT( newChannelView() ) );

	newMenu->addAction( tr( "Scheme" ), this,
		SLOT( newSchemeWindow() ) );

	QMenu * openMenu = fileMenu->addMenu( QIcon( ":img/open_22x22.png" ),
		tr( "Open" ) );

	openMenu->addAction( tr( "Scheme" ), this,
		SLOT( openScheme() ) );

	fileMenu->addAction( QIcon( ":/img/save_22x22.png" ),
		tr( "Save Configuration" ), this, SLOT( save() ),
		QKeySequence( tr( "Ctrl+S" ) ) );

	fileMenu->addSeparator();

	fileMenu->addAction( QIcon( ":/img/exit_22x22.png" ),
		tr( "E&xit" ), this, SLOT( shutdown() ),
		QKeySequence( tr( "Ctrl+Q" ) ) );

	QMenu * toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );

	QMenu * settingsMenu = menuBar()->addMenu( tr( "&Settings" ) );

	settingsMenu->addAction( QIcon( ":/img/settings_22x22.png" ),
		tr( "&Settings" ), this, SLOT( settings() ),
		QKeySequence( tr( "Alt+C" ) ) );

	QMenu * windowsMenu = menuBar()->addMenu( tr( "&Windows" ) );

	QMenu * help = menuBar()->addMenu( tr( "&Help" ) );

	help->addAction( QIcon( ":/img/globe_22x22.png" ),
		tr( "About" ), this, &MainWindow::about );

	help->addAction( QIcon( ":/img/qt.png" ),
		tr( "About Qt" ), this, &MainWindow::aboutQt );

	d->m_menu.reset( new Menu( fileMenu, settingsMenu,
		toolWindows, d->m_windows, help ) );

	foreach( ToolWindowObject * obj, d->m_menu->toolWindows() )
		toolsMenu->addAction( obj->menuEntity() );

	d->m_winMenu = new WindowsMenu( windowsMenu, this, d->m_menu->windows(),
		this );

	d->m_confDialog = new ConfigurationDialog( this );

	ScrolledView * area = new ScrolledView( this );

	d->m_list = new ChannelsList( ShowAll, Qt::AscendingOrder, this );

	area->setWidget( d->m_list );

	setCentralWidget( area );

	PropertiesManager::instance().initMenu( *d->m_menu );
	SourcesMainWindow::instance().initMenu( *d->m_menu );
	LogEventWindow::instance().initMenu( *d->m_menu );
	LogSourcesWindow::instance().initMenu( *d->m_menu );
	Sounds::instance().initMenu( *d->m_menu );
}

const Menu &
MainWindow::menu() const
{
	return *d->m_menu;
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

	emit windowClosed( window );
}

void
MainWindow::schemeWindowClosed( Scheme::Window * window )
{
	Scheme::WindowCfg cfg = window->cfg();

	if( d->m_schemeWindowsCfg.find( cfg.schemeCfgFile() ) !=
		d->m_schemeWindowsCfg.end() )
			d->m_schemeWindowsCfg[ cfg.schemeCfgFile() ] = cfg;
	else
		d->m_schemeWindowsCfg.insert( cfg.schemeCfgFile(), cfg );

	d->m_schemeWindows.removeAll( window );

	emit windowClosed( window );
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

		window->initMenu( *d->m_menu );

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

		emit windowCreated( window );
	}
}

void
MainWindow::showScheme( const QString & cfgFile, bool newScheme )
{
	Scheme::Window * window = d->schemeWindow( cfgFile );

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
		window = new Scheme::Window;

		window->initMenu( *d->m_menu );

		if( newScheme )
			window->createNewScheme( cfgFile );
		else
			window->loadScheme( cfgFile );

		d->m_schemeWindows.append( window );

		if( d->m_schemeWindowsCfg.find( cfgFile ) !=
			d->m_schemeWindowsCfg.end() )
				window->setCfg(
					d->m_schemeWindowsCfg[ cfgFile ] );
		else
			window->show();

		emit windowCreated( window );
	}
}

void
MainWindow::save()
{
	saveConfiguration();

	d->m_cfgWasSaved = false;
}

void
MainWindow::sessionFinished( QSessionManager & )
{
	saveConfiguration();
}

void
MainWindow::addAggregate( Scheme::Window * w )
{
	if( !d->m_aggregates.contains( w ) )
	{
		d->m_aggregates.append( w );

		emit windowCreated( w );
	}
}

void
MainWindow::removeAggregate( Scheme::Window * w )
{
	d->m_aggregates.removeOne( w );

	emit windowClosed( w );
}

Scheme::Window *
MainWindow::findAggregate( const QString & name )
{
	for( auto * w : qAsConst( d->m_aggregates ) )
	{
		if( w->schemeName() == name )
			return w;
	}

	return Q_NULLPTR;
}

void
MainWindow::closeEvent( QCloseEvent * event )
{
	if( !d->m_isQuit )
		shutdown();

	event->accept();
}

WindowsCfg
MainWindow::windowsCfg() const
{
	WindowsCfg cfg;

	QList< ChannelViewWindowCfg > channelViewWindows;

	foreach( ChannelViewWindow * window, d->m_channelViewWindows )
		channelViewWindows.append( window->cfg() );

	cfg.setChannelViewWindows( channelViewWindows );

	QList< Scheme::WindowCfg > schemeWindows;

	foreach( Scheme::Window * window, d->m_schemeWindows )
		schemeWindows.append( window->cfg() );

	cfg.setSchemeWindows( schemeWindows );

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

	foreach( const Scheme::WindowCfg & c, cfg.schemeWindows() )
	{
		d->m_schemeWindowsCfg.insert( c.schemeCfgFile(), c );

		showScheme( c.schemeCfgFile() );
	}
}

void
MainWindow::aboutToQuit()
{
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
MainWindow::newSchemeWindow()
{
	QString fileName = QFileDialog::getSaveFileName( this,
		tr( "Save New Scheme" ),
		Configuration::instance().path() + QLatin1String( "schemes" ),
		tr( "Scheme (*.scheme)" ) );

	if( !fileName.isEmpty() )
	{
		fileName = relativeFilePath( fileName, Configuration::instance().path() );

		showScheme( fileName, true );
	}
}

void
MainWindow::openScheme()
{
	QString fileName = QFileDialog::getOpenFileName( this,
		tr( "Open Scheme" ),
		Configuration::instance().path() + QLatin1String( "schemes" ),
		tr( "Scheme (*.scheme)" ) );

	if( !fileName.isEmpty() )
	{
		fileName = relativeFilePath( fileName, Configuration::instance().path() );

		showScheme( fileName );
	}
}

void
MainWindow::settings()
{
	d->m_confDialog->exec();
}

void
MainWindow::shutdown()
{
	const QMessageBox::StandardButton btn = QMessageBox::question( this,
		tr( "Saving configuration..." ),
		tr( "Would you like to save configuration?" ),
		QMessageBox::StandardButtons( QMessageBox::Save | QMessageBox::No ),
		QMessageBox::Save );

	if( btn == QMessageBox::Save )
		saveConfiguration();

	foreach( ChannelViewWindow * w, d->m_channelViewWindows )
		w->close();

	foreach( Scheme::Window * w, d->m_schemeWindows )
		w->close();

	ChannelsManager::instance().shutdown();

	d->m_isQuit = true;

	QApplication::quit();
}

void
MainWindow::updateWindowsMenu( QWidget * )
{
	d->m_winMenu->update();
}

void
MainWindow::about()
{
	QMessageBox::about( this, tr( "About Globe" ),
		tr( "Globe - Monitoring application.\n\n"
			"Author - Igor Mironchik (igor.mironchik at gmail dot com).\n\n"
			"Copyright (c) 2012-2020 Igor Mironchik.\n\n"
			"Licensed under GNU GPL 3.0." ) );
}

void
MainWindow::aboutQt()
{
	QMessageBox::aboutQt( this );
}

void
MainWindow::saveConfiguration()
{
	if( !d->m_cfgWasSaved )
	{
		Configuration::instance().saveConfiguration();

		foreach( Scheme::Window * w, d->m_schemeWindows )
			w->saveScheme();

		d->m_cfgWasSaved = true;
	}
}

} /* namespace Globe */

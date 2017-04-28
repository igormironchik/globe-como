
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
#include <Globe/Core/mainwindow.hpp>
#include <Globe/Core/channels_list.hpp>
#include <Globe/Core/tool_window_object.hpp>
#include <Globe/Core/configuration.hpp>
#include <Globe/Core/scrolled_widget.hpp>
#include <Globe/Core/channel_view_window.hpp>
#include <Globe/Core/channel_name_dialog.hpp>
#include <Globe/Core/log.hpp>
#include <Globe/Core/configuration_dialog.hpp>
#include <Globe/Core/globe_menu.hpp>
#include <Globe/Core/properties_manager.hpp>
#include <Globe/Core/sources_mainwindow.hpp>
#include <Globe/Core/log_event_view_window.hpp>
#include <Globe/Core/log_sources_window.hpp>
#include <Globe/Core/sources.hpp>
#include <Globe/Core/sounds.hpp>
#include <Globe/Core/utils.hpp>
#include <Globe/Core/channels.hpp>

#include <Globe/Scheme/window.hpp>

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
	MainWindowPrivate()
		:	m_list( 0 )
		,	m_cfgWasSaved( false )
		,	m_confDialog( 0 )
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
	//! Map of the channel view windows configuration.
	QMap< QString, ChannelViewWindowCfg > m_channelViewWindowsCfg;
	//! Map of the scheme windows configurations.
	QMap< QString, Scheme::WindowCfg > m_schemeWindowsCfg;
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
	LogSourcesWindow::instance().initMenu( d->m_menu );
	Sounds::instance().initMenu( d->m_menu );

	checkPathAndCreateIfNotExists( QLatin1String( "./etc/schemes" ) );
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
MainWindow::schemeWindowClosed( Scheme::Window * window )
{
	Scheme::WindowCfg cfg = window->cfg();

	if( d->m_schemeWindowsCfg.find( cfg.schemeCfgFile() ) !=
		d->m_schemeWindowsCfg.end() )
			d->m_schemeWindowsCfg[ cfg.schemeCfgFile() ] = cfg;
	else
		d->m_schemeWindowsCfg.insert( cfg.schemeCfgFile(), cfg );

	d->m_schemeWindows.removeAll( window );
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

		window->initMenu( d->m_menu );

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
	}
}

void
MainWindow::save()
{
	d->m_cfgWasSaved = false;

	saveConfiguration();
}

void
MainWindow::sessionFinished( QSessionManager & )
{
	saveConfiguration();
}

void
MainWindow::closeEvent( QCloseEvent * event )
{
	event->accept();

	shutdown();
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
		QLatin1String( "./etc/schemes" ),
		tr( "Scheme (*.scheme)" ) );

	if( !fileName.isEmpty() )
	{
		fileName = relativeFilePath( fileName );

		showScheme( fileName, true );
	}
}

void
MainWindow::openScheme()
{
	QString fileName = QFileDialog::getOpenFileName( this,
		tr( "Open Scheme" ),
		QLatin1String( "./etc/schemes" ),
		tr( "Scheme (*.scheme)" ) );

	if( !fileName.isEmpty() )
	{
		fileName = relativeFilePath( fileName );

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
	QMessageBox dlg( this );

	dlg.setText( tr( "Would you like to save configuration?" ) );
	QPushButton * btn = dlg.addButton( tr( "Yes" ), QMessageBox::AcceptRole );
	dlg.addButton( tr( "No" ), QMessageBox::RejectRole );
	dlg.setDefaultButton( btn );

	if( dlg.exec() == QMessageBox::AcceptRole )
		saveConfiguration();

	foreach( ChannelViewWindow * w, d->m_channelViewWindows )
		w->close();

	foreach( Scheme::Window * w, d->m_schemeWindows )
		w->close();

	ChannelsManager::instance().shutdown();

	QApplication::quit();
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

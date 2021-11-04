
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
#include <Core/configuration.hpp>
#include <Core/channels.hpp>
#include <Core/db.hpp>
#include <Core/properties_manager.hpp>
#include <Core/mainwindow.hpp>
#include <Core/application_cfg.hpp>
#include <Core/window_state_cfg.hpp>
#include <Core/application_cfg.hpp>
#include <Core/channels_cfg.hpp>
#include <Core/mainwindow_cfg.hpp>
#include <Core/channels_list.hpp>
#include <Core/sources_mainwindow.hpp>
#include <Core/windows_cfg.hpp>
#include <Core/color_for_level.hpp>
#include <Core/log.hpp>
#include <Core/log_event_view_window.hpp>
#include <Core/log_sources_window.hpp>
#include <Core/sounds.hpp>
#include <Core/sounds_disabled.hpp>
#include <Core/db_cfg.hpp>
#include <Core/utils.hpp>

// cfgfile include.
#include <cfgfile/all.hpp>

// Qt include.
#include <QMessageBox>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>


namespace Globe {

static const QString defaultAppCfgFileName =
	QLatin1String( "./etc/Globe.cfg" );
static const QString defaultMainWindowCfgFileName =
	QLatin1String( "MainWindow.cfg" );
static const QString defaultChannelsCfgFileName =
	QLatin1String( "Channels.cfg" );
static const QString defaultPropertiesCfgFileName =
	QLatin1String( "Properties.cfg" );
static const QString defaultSourcesMainWindowCfgFileName =
	QLatin1String( "SourcesMainWindow.cfg" );
static const QString defaultWindowsCfgFileName =
	QLatin1String( "Windows.cfg" );
static const QString defaultColorsCfgFilename =
	QLatin1String( "Colors.cfg" );
static const QString defaultDbCfgFileName =
	QLatin1String( "DB.cfg" );
static const QString defaultLogCfgFileName =
	QLatin1String( "Log.cfg" );
static const QString defaultLogEventWindowCfgFileName =
	QLatin1String( "LogEventWindow.cfg" );
static const QString defaultSoundsCfgFileName =
	QLatin1String( "Sounds.cfg" );
static const QString defaultDisabledSoundsCfgFileName =
	QLatin1String( "DisabledSounds.cfg" );
static const QString defaultSourcesLogWindowCfgFileName =
	QLatin1String( "SourcesLogWindow.cfg" );


//
// ConfigurationPrivate
//

class ConfigurationPrivate {
public:
	ConfigurationPrivate()
		:	m_appCfgWasLoaded( false )
	{
	}

	//! Configuration's file name.
	QString m_cfgFileName;
	//! Application's configuration.
	ApplicationCfg m_appCfg;
	//! Was application's configuration loaded?
	bool m_appCfgWasLoaded;
}; // class ConfigurationPrivate


//
// Configuration
//

Configuration::Configuration( QObject * parent )
	:	QObject( parent )
	,	d( new ConfigurationPrivate )
{
}

Configuration::~Configuration()
{
}

static Configuration * configurationInstancePointer = 0;

void
Configuration::cleanup()
{
	delete configurationInstancePointer;

	configurationInstancePointer = 0;
}

Configuration &
Configuration::instance()
{
	if( !configurationInstancePointer )
	{
		configurationInstancePointer = new Configuration;

		qAddPostRoutine( &Configuration::cleanup );
	}

	return *configurationInstancePointer;
}

QString
Configuration::path() const
{
	static const QDir dir( QStringLiteral( "." ) );

	return dir.relativeFilePath( QFileInfo( d->m_cfgFileName ).absolutePath() ) +
		QDir::separator();
}

void
Configuration::loadConfiguration()
{
	Log::instance().writeMsgToEventLog( LogLevelInfo,
		QLatin1String( "Loading configuration..." ) );

	readAppCfg( d->m_cfgFileName );

	readDbCfg( d->m_appCfg.dbCfgFile() );

	readLogCfg( d->m_appCfg.logCfgFile() );

	readPropertiesCfg( d->m_appCfg.propertiesCfgFile() );

	readColorsCfg( d->m_appCfg.colorsCfgFile() );

	readMainWindowCfg( d->m_appCfg.mainWindowCfgFile() );

	readSourcesMainWindowCfg( d->m_appCfg.sourcesMainWindowCfgFile() );

	readLogEventWindowCfg( d->m_appCfg.logEventWindowCfgFile() );

	readSourcesLogWindowCfg( d->m_appCfg.sourcesLogWindowCfgFile() );

	readSoundsCfg( d->m_appCfg.soundsCfgFile() );

	readDisabledSoundsCfg( d->m_appCfg.disabledSoundsCfgFile() );

	readChannelsCfg( d->m_appCfg.channelsCfgFile() );

	readWindowsCfg( d->m_appCfg.windowsCfgFile() );

	if( d->m_appCfgWasLoaded )
		Log::instance().writeMsgToEventLog( LogLevelInfo,
			QLatin1String( "Configuration successfully loaded..." ) );
	else
		Log::instance().writeMsgToEventLog( LogLevelInfo,
			QLatin1String( "Configuration was not loaded. "
				"Use the default configuration." ) );
}

void
Configuration::saveConfiguration()
{
	Log::instance().writeMsgToEventLog( LogLevelInfo,
		QLatin1String( "Saving configuration..." ) );

	const auto dir = path();

	saveLogEventWindowCfg( dir + d->m_appCfg.logEventWindowCfgFile() );

	saveSourcesMainWindowCfg( dir + d->m_appCfg.sourcesMainWindowCfgFile() );

	saveSourcesLogWindowCfg( dir + d->m_appCfg.sourcesLogWindowCfgFile() );

	savePropertiesCfg( dir + d->m_appCfg.propertiesCfgFile() );

	saveChannelsCfg( dir + d->m_appCfg.channelsCfgFile() );

	saveMainWindowCfg( dir + d->m_appCfg.mainWindowCfgFile() );

	saveWindowsCfg( dir + d->m_appCfg.windowsCfgFile() );

	saveColorsCfg( dir + d->m_appCfg.colorsCfgFile() );

	saveDbCfg( dir + d->m_appCfg.dbCfgFile() );

	saveLogCfg( dir + d->m_appCfg.logCfgFile() );

	saveSoundsCfg( dir + d->m_appCfg.soundsCfgFile() );

	saveDisabledSoundsCfg( dir + d->m_appCfg.disabledSoundsCfgFile() );

	saveAppCfg( d->m_cfgFileName );

	Log::instance().writeMsgToEventLog( LogLevelInfo,
		QLatin1String( "Configuration successfully saved..." ) );
}

void
Configuration::setCfgFile( const QString & fileName )
{
	d->m_cfgFileName = fileName;
}

void
Configuration::readAppCfg( const QString & cfgFileName )
{
	if( cfgFileName.isEmpty() )
		d->m_cfgFileName = defaultAppCfgFileName;
	else
		d->m_cfgFileName = cfgFileName;

	QFile file( d->m_cfgFileName );

	if( file.open( QIODevice::ReadOnly ) )
	{
		QTextStream stream( &file );

		try {
			ApplicationCfgTag appCfgTag;

			cfgfile::read_cfgfile( appCfgTag, stream, d->m_cfgFileName );

			file.close();

			Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
				"Application's configuration loaded from file \"%1\"." )
					.arg( cfgFileName ) );

			d->m_appCfg = appCfgTag.cfg();

			d->m_appCfgWasLoaded = true;
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			Log::instance().writeMsgToEventLog( LogLevelError, QString(
				"Unable to load application's configuration from file "
				"\"%1\".\n"
				"%2" )
					.arg( d->m_cfgFileName, x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to load Globe's configuration file..." ),
				x.desc() );
		}
	}
	else
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to load application's configuration from file "
			"\"%1\".\n"
			"Unable to open file." )
				.arg( d->m_cfgFileName ) );

		QMessageBox::critical( 0,
			tr( "Unable to load Globe's configuration file..." ),
			tr( "Unable to open file. Does file \"%1\" exist?\n"
				"Globe will start with empty default configuration.\n"
				"You can configure application and save configuration." )
					.arg( d->m_cfgFileName ) );
	}

	checkPathAndCreateIfNotExists( path() + QLatin1String( "schemes" ) );
	checkPathAndCreateIfNotExists( path() + QLatin1String( "sounds" ) );
	checkPathAndCreateIfNotExists( path() + defaultPropsConfigurationDirectory );
}

void
Configuration::readMainWindowCfg( const QString & cfgFileName )
{
	MainWindowCfg cfg;

	if( !cfgFileName.isEmpty() )
	{
		const auto p = path() + cfgFileName;

		QFile file( p );

		try {
			if( file.open( QIODevice::ReadOnly ) )
			{
				QTextStream stream( &file );

				MainWindowCfgTag tag;

				cfgfile::read_cfgfile( tag, stream, p );

				file.close();

				Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
					"Main window's configuration loaded from file \"%1\"." )
						.arg( p ) );

				cfg = tag.cfg();
			}
			else
			{
				Log::instance().writeMsgToEventLog( LogLevelError, QString(
					"Unable to load main window's configuration from file "
					"\"%1\".\n"
					"Unable to open file." )
						.arg( p ) );

				QMessageBox::critical( 0,
					tr( "Unable to load main window's configuration..." ),
					tr( "Unable to open file \"%1\"." ).arg( p ) );

				return;
			}
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			Log::instance().writeMsgToEventLog( LogLevelError, QString(
				"Unable to load main window's configuration from file "
				"\"%1\".\n"
				"%2" )
					.arg( p, x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to load main window's configuration..." ),
				x.desc() );

			return;
		}
	}
	else
	{
		d->m_appCfg.setMainWindowCfgFile( defaultMainWindowCfgFileName );

		if( d->m_appCfgWasLoaded )
		{
			Log::instance().writeMsgToEventLog( LogLevelWarning, QString(
				"Error in application's configuration...\n"
				"Not specified main window's configuration file.\n"
				"Main window's configuration will not be loaded.\n"
				"At exit configuration of the main window will be saved\n"
				"in \"%1\" file." )
					.arg( path() + defaultMainWindowCfgFileName ) );

			QMessageBox::warning( 0,
				tr( "Error in application's configuration..." ),
				tr( "Not specified main window's configuration file.\n"
					"Main window's configuration will not be loaded.\n"
					"At exit configuration of the main window will be saved\n"
					"in \"%1\" file." )
						.arg( path() + defaultMainWindowCfgFileName ) );
		}
	}

	MainWindow::instance().list()->setShownChannelsMode( cfg.shownChannels() );
	restoreWindowState( cfg.windowState(), &MainWindow::instance() );
}

void
Configuration::readChannelsCfg( const QString & cfgFileName )
{
	AvailableChannelsCfg cfg;

	if( !cfgFileName.isEmpty() )
	{
		const auto p = path() + cfgFileName;

		QFile file( p );

		if( file.open( QIODevice::ReadOnly ) )
		{
			try {
				AvailableChannelsCfgTag tag;

				QTextStream stream( &file );

				cfgfile::read_cfgfile( tag, stream, p );

				file.close();

				Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
					"Channel's configuration loaded from file \"%1\"." )
						.arg( p ) );

				cfg = tag.cfg();
			}
			catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
			{
				file.close();

				Log::instance().writeMsgToEventLog( LogLevelError, QString(
					"Unable to load channels configuration from file "
					"\"%1\".\n"
					"%2" )
						.arg( p, x.desc() ) );

				QMessageBox::critical( 0,
					tr( "Unable to load channels configuration..." ),
					x.desc() );

				return;
			}
		}
		else
		{
			Log::instance().writeMsgToEventLog( LogLevelError, QString(
				"Unable to load channels configuration from file "
				"\"%1\".\n"
				"Unable to open file." )
					.arg( p ) );

			QMessageBox::critical( 0,
				tr( "Unable to load channels configuration..." ),
				tr( "Unable to open file \"%1\"." ).arg( p ) );

			return;
		}
	}
	else
	{
		d->m_appCfg.setChannelsCfgFile( defaultChannelsCfgFileName );

		if( d->m_appCfgWasLoaded )
		{
			Log::instance().writeMsgToEventLog( LogLevelWarning, QString(
				"Error in application's configuration...\n"
				"Not specified channel's configuration file.\n"
				"Channel's configuration will not be loaded.\n"
				"At exit channels configuration will be saved\n"
				"in \"%1\" file." )
					.arg( path() + defaultChannelsCfgFileName ) );

			QMessageBox::warning( 0,
				tr( "Error in application's configuration..." ),
				tr( "Not specified channel's configuration file.\n"
					"Channel's configuration will not be loaded.\n"
					"At exit channels configuration will be saved\n"
					"in \"%1\" file." )
						.arg( path() + defaultChannelsCfgFileName ) );
		}
	}

	foreach( const ChannelCfg & channelCfg, cfg )
	{
		Channel * channel = ChannelsManager::instance().createChannel(
			channelCfg.name(), channelCfg.address(), channelCfg.port(),
			channelCfg.channelType() );

		if( channel )
		{
			MainWindow::instance().list()->addChannel( channel, channelCfg.timeout() );

			if( channelCfg.isMustBeConnected() )
				channel->connectToHost();
		}
		else if( !ChannelsManager::instance().isNameUnique( channelCfg.name() ) )
		{
			Log::instance().writeMsgToEventLog( LogLevelError, QString(
				"Unable to create new channel...\n"
				"Channel with name \"%1\" already exists." )
					.arg( channelCfg.name() ) );

			QMessageBox::critical( 0,
				tr( "Unable to create new channel..." ),
				tr( "Channel with name \"%1\" already exists." )
					.arg( channelCfg.name() ) );
		}
		else if( !ChannelsManager::instance().isAddressAndPortUnique(
			channelCfg.address(), channelCfg.port() ) )
		{
			Log::instance().writeMsgToEventLog( LogLevelError, QString(
				"Unable to create new channel...\n"
				"Channel with address \"%1\" and port %2 already exists." )
					.arg( channelCfg.address(), QString::number( channelCfg.port() ) ) );

			QMessageBox::critical( 0,
				tr( "Unable to create new channel..." ),
				tr( "Channel with address \"%1\" and port %2 already exists." )
					.arg( channelCfg.address(), QString::number( channelCfg.port() ) ) );
		}
	}
}

void
Configuration::readPropertiesCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		PropertiesManager::instance().readConfiguration( path() + cfgFileName );
	else
	{
		d->m_appCfg.setPropertiesCfgFile( defaultPropertiesCfgFileName );

		PropertiesManager::instance().initWithDefaultCfg();

		if( d->m_appCfgWasLoaded )
		{
			Log::instance().writeMsgToEventLog( LogLevelWarning, QString(
				"Error in application's configuration...\n"
				"Not specified properties configuration file.\n"
				"Properties configuration will not be loaded.\n"
				"At exit properties configuration will be saved\n"
				"in \"%1\" file." )
					.arg( path() + defaultPropertiesCfgFileName ) );

			QMessageBox::warning( 0,
				tr( "Error in application's configuration..." ),
				tr( "Not specified properties configuration file.\n"
					"Properties configuration will not be loaded.\n"
					"At exit properties configuration will be saved\n"
					"in \"%1\" file." )
						.arg( path() + defaultPropertiesCfgFileName ) );
		}
	}
}

void
Configuration::readSourcesMainWindowCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		SourcesMainWindow::instance().readConfiguration( path() + cfgFileName );
	else
	{
		d->m_appCfg.setSourcesMainWindowCfgFile(
			defaultSourcesMainWindowCfgFileName );

		if( d->m_appCfgWasLoaded )
		{
			Log::instance().writeMsgToEventLog( LogLevelWarning, QString(
				"Error in application's configuration...\n"
				"Not specified sources main window configuration file.\n"
				"Sources main window configuration will not be loaded.\n"
				"At exit sources main window configuration will be saved\n"
				"in \"%1\" file." )
					.arg( path() + defaultSourcesMainWindowCfgFileName ) );

			QMessageBox::warning( 0,
				tr( "Error in application's configuration..." ),
				tr( "Not specified sources main window configuration file.\n"
					"Sources main window configuration will not be loaded.\n"
					"At exit sources main window configuration will be saved\n"
					"in \"%1\" file." )
						.arg( path() + defaultSourcesMainWindowCfgFileName ) );
		}
	}
}

void
Configuration::readWindowsCfg( const QString & cfgFileName )
{
	WindowsCfg cfg;

	if( !cfgFileName.isEmpty() )
	{
		const auto p = path() + cfgFileName;

		QFile file( p );

		if( file.open( QIODevice::ReadOnly ) )
		{
			try {
				QTextStream stream( &file );

				WindowsTag tag;

				cfgfile::read_cfgfile( tag, stream, p );

				file.close();

				Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
					"Windows configuration loaded from file \"%1\"." )
						.arg( p ) );

				cfg = tag.cfg();
			}
			catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
			{
				file.close();

				Log::instance().writeMsgToEventLog( LogLevelError, QString(
					"Unable to load windows configuration from file "
					"\"%1\".\n"
					"%2" )
						.arg( p, x.desc() ) );

				QMessageBox::critical( 0,
					tr( "Unable to load windows configuration..." ),
					x.desc() );

				return;
			}
		}
		else
		{
			Log::instance().writeMsgToEventLog( LogLevelError, QString(
				"Unable to load windows configuration from file "
				"\"%1\".\n"
				"Unable to open file." )
					.arg( p ) );

			QMessageBox::critical( 0,
				tr( "Unable to load windows configuration..." ),
				tr( "Unable to open file \"%1\"." ).arg( p ) );

			return;
		}
	}
	else
	{
		d->m_appCfg.setWindowsCfgFile( defaultWindowsCfgFileName );

		if( d->m_appCfgWasLoaded )
		{
			Log::instance().writeMsgToEventLog( LogLevelWarning, QString(
				"Error in application's configuration...\n"
				"Not specified windows configuration file.\n"
				"Windows configuration will not be loaded.\n"
				"At exit configuration of the windows will be saved\n"
				"in \"%1\" file." )
					.arg( path() + defaultWindowsCfgFileName ) );

			QMessageBox::warning( 0,
				tr( "Error in application's configuration..." ),
				tr( "Not specified windows configuration file.\n"
					"Windows configuration will not be loaded.\n"
					"At exit configuration of the windows will be saved\n"
					"in \"%1\" file." )
						.arg( path() + defaultWindowsCfgFileName ) );
		}
	}

	MainWindow::instance().restoreWindows( cfg );
}

void
Configuration::readColorsCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		ColorForLevel::instance().readCfg( path() + cfgFileName );
	else
	{
		d->m_appCfg.setColorsCfgFile( defaultColorsCfgFilename );

		if( d->m_appCfgWasLoaded )
		{
			Log::instance().writeMsgToEventLog( LogLevelWarning, QString(
				"Error in application's configuration...\n"
				"Not specified colors configuration file.\n"
				"Colors configuration will not be loaded.\n"
				"At exit colors configuration will be saved\n"
				"in \"%1\" file." )
					.arg( path() + defaultColorsCfgFilename ) );

			QMessageBox::warning( 0,
				tr( "Error in application's configuration..." ),
				tr( "Not specified colors configuration file.\n"
					"Colors configuration will not be loaded.\n"
					"At exit colors configuration will be saved\n"
					"in \"%1\" file." )
						.arg( path() + defaultColorsCfgFilename ) );
		}
	}
}

void
Configuration::readDbCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		DB::instance().readCfg( path() + cfgFileName );
	else
	{
		d->m_appCfg.setDbCfgFile( defaultDbCfgFileName );

		DB::instance().setCfg( DBCfg() );

		if( d->m_appCfgWasLoaded )
		{
			Log::instance().writeMsgToEventLog( LogLevelWarning, QString(
				"Error in application's configuration...\n"
				"Not specified DB configuration file.\n"
				"DB configuration will not be loaded.\n"
				"At exit DB configuration will be saved\n"
				"in \"%1\" file." )
					.arg( path() + defaultDbCfgFileName ) );

			QMessageBox::warning( 0,
				tr( "Error in application's configuration..." ),
				tr( "Not specified DB configuration file.\n"
					"DB configuration will not be loaded.\n"
					"At exit DB configuration will be saved\n"
					"in \"%1\" file." )
						.arg( path() + defaultDbCfgFileName ) );
		}
	}
}

void
Configuration::readLogCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		Log::instance().readCfg( path() + cfgFileName );
	else
	{
		d->m_appCfg.setLogCfgFile( defaultLogCfgFileName );

		Log::instance().initWithDefaultCfg();

		if( d->m_appCfgWasLoaded )
		{
			Log::instance().writeMsgToEventLog( LogLevelWarning, QString(
				"Error in application's configuration...\n"
				"Not specified log configuration file.\n"
				"Log configuration will not be loaded.\n"
				"At exit log configuration will be saved\n"
				"in \"%1\" file." )
					.arg( path() + defaultLogCfgFileName ) );

			QMessageBox::warning( 0,
				tr( "Error in application's configuration..." ),
				tr( "Not specified log configuration file.\n"
					"Log configuration will not be loaded.\n"
					"At exit log configuration will be saved\n"
					"in \"%1\" file." )
						.arg( path() + defaultLogCfgFileName ) );
		}
	}
}

void
Configuration::readLogEventWindowCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		LogEventWindow::instance().readConfiguration( path() + cfgFileName );
	else
	{
		d->m_appCfg.setLogEventWindowCfgFile( defaultLogEventWindowCfgFileName );

		if( d->m_appCfgWasLoaded )
		{
			Log::instance().writeMsgToEventLog( LogLevelWarning, QString(
				"Error in application's configuration...\n"
				"Not specified event's log window configuration file.\n"
				"Event's log window configuration will not be loaded.\n"
				"At exit event's log window configuration will be saved\n"
				"in \"%1\" file." )
					.arg( path() + defaultLogEventWindowCfgFileName ) );

			QMessageBox::warning( 0,
				tr( "Error in application's configuration..." ),
				tr( "Not specified event's log window configuration file.\n"
					"Event's log window configuration will not be loaded.\n"
					"At exit event's log window configuration will be saved\n"
					"in \"%1\" file." )
						.arg( path() + defaultLogEventWindowCfgFileName ) );
		}
	}
}

void
Configuration::readSoundsCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		Sounds::instance().readCfg( path() + cfgFileName );
	else
	{
		d->m_appCfg.setSoundsCfgFile( defaultSoundsCfgFileName );

		if( d->m_appCfgWasLoaded )
		{
			Log::instance().writeMsgToEventLog( LogLevelWarning, QString(
				"Error in application's configuration...\n"
				"Not specified sounds configuration file.\n"
				"Sounds configuration will not be loaded.\n"
				"At exit sounds configuration will be saved\n"
				"in \"%1\" file." )
					.arg( path() + defaultSoundsCfgFileName ) );

			QMessageBox::warning( 0,
				tr( "Error in application's configuration..." ),
				tr( "Not specified sounds configuration file.\n"
					"Sounds configuration will not be loaded.\n"
					"At exit sounds configuration will be saved\n"
					"in \"%1\" file." )
						.arg( path() + defaultSoundsCfgFileName ) );
		}
	}
}

void
Configuration::readDisabledSoundsCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		DisabledSounds::instance().readCfg( path() + cfgFileName );
	else
	{
		d->m_appCfg.setDisabledSoundsCfgFile( defaultDisabledSoundsCfgFileName );

		if( d->m_appCfgWasLoaded )
		{
			Log::instance().writeMsgToEventLog( LogLevelWarning, QString(
				"Error in application's configuration...\n"
				"Not specified disabled sounds configuration file.\n"
				"Disabled sounds configuration will not be loaded.\n"
				"At exit disabled sounds configuration will be saved\n"
				"in \"%1\" file." )
					.arg( path() + defaultDisabledSoundsCfgFileName ) );

			QMessageBox::warning( 0,
				tr( "Error in application's configuration..." ),
				tr( "Not specified disabled sounds configuration file.\n"
					"Disabled sounds configuration will not be loaded.\n"
					"At exit disabled sounds configuration will be saved\n"
					"in \"%1\" file." )
						.arg( path() + defaultDisabledSoundsCfgFileName ) );
		}
	}
}

void
Configuration::readSourcesLogWindowCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		LogSourcesWindow::instance().readConfiguration( path() + cfgFileName );
	else
	{
		d->m_appCfg.setSourcesLogWindowCfgFile( defaultSourcesLogWindowCfgFileName );

		if( d->m_appCfgWasLoaded )
		{
			Log::instance().writeMsgToEventLog( LogLevelWarning, QString(
				"Error in application's configuration...\n"
				"Not specified sources log window's configuration file.\n"
				"Sources log window's configuration will not be loaded.\n"
				"At exit sources log window's configuration will be saved\n"
				"in \"%1\" file." )
					.arg( path() + defaultSourcesLogWindowCfgFileName ) );

			QMessageBox::warning( 0,
				tr( "Error in application's configuration..." ),
				tr( "Not specified sources log window's configuration file.\n"
					"Sources log window's configuration will not be loaded.\n"
					"At exit sources log window's configuration will be saved\n"
					"in \"%1\" file." )
						.arg( path() + defaultSourcesLogWindowCfgFileName ) );
		}
	}
}

void
Configuration::saveAppCfg( const QString & cfgFileName )
{
	QFile file( cfgFileName );

	if( file.open( QIODevice::WriteOnly ) )
	{
		try {
			ApplicationCfgTag tag( d->m_appCfg );

			QTextStream stream( &file );

			cfgfile::write_cfgfile( tag, stream );

			file.close();

			Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
				"Application's configuration saved into file \"%1\"." )
					.arg( cfgFileName ) );
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			Log::instance().writeMsgToEventLog( LogLevelError, QString(
				"Unable to save application's configuration in file "
				"\"%1\".\n"
				"%2" )
					.arg( cfgFileName, x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to save application's configuration..." ),
				x.desc() );
		}
	}
	else
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to save application's configuration in file "
			"\"%1\".\n"
			"Unable to open file." )
				.arg( cfgFileName ) );

		QMessageBox::critical( 0,
			tr( "Unable to save application's configuration..." ),
			tr( "Unable to open file \"%1\"." ).arg( cfgFileName ) );
	}
}

void
Configuration::saveMainWindowCfg( const QString & cfgFileName )
{
	ShownChannels shownChannels =
		MainWindow::instance().list()->shownChannelsMode();

	MainWindowCfg mainWindowCfg( windowStateCfg( &MainWindow::instance() ),
		shownChannels );

	QFile file( cfgFileName );

	if( file.open( QIODevice::WriteOnly ) )
	{
		try {
			MainWindowCfgTag tag( mainWindowCfg );

			QTextStream stream( &file );

			cfgfile::write_cfgfile( tag, stream );

			file.close();

			Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
				"Main window's configuration saved into file \"%1\"." )
					.arg( cfgFileName ) );
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			Log::instance().writeMsgToEventLog( LogLevelError, QString(
				"Unable to save main window's configuration in file "
				"\"%1\".\n"
				"%2" )
					.arg( cfgFileName, x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to save main window's configuration..." ),
				x.desc() );
		}
	}
	else
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to save main window's configuration in file "
			"\"%1\".\n"
			"Unable to open file." )
				.arg( cfgFileName ) );

		QMessageBox::critical( 0,
			tr( "Unable to save main window's configuration..." ),
			tr( "Unable to open file \"%1\"." ).arg( cfgFileName ) );
	}
}

void
Configuration::saveChannelsCfg( const QString & cfgFileName )
{
	QList< Channel* > channels = ChannelsManager::instance().channels();
	AvailableChannelsCfg channelsCfg;

	foreach( Channel * channel, channels )
	{
		ChannelCfg chCfg;

		chCfg.setName( channel->name() );
		chCfg.setAddress( channel->hostAddress() );
		chCfg.setPort( channel->portNumber() );
		chCfg.setMustBeConnected( channel->isMustBeConnected() );
		chCfg.setTimeout( channel->timeout() );
		chCfg.setChannelType( channel->channelType() );

		channelsCfg.append( chCfg );
	}

	QFile file( cfgFileName );

	if( file.open( QIODevice::WriteOnly ) )
	{
		try {
			AvailableChannelsCfgTag tag( channelsCfg );

			QTextStream stream( &file );

			cfgfile::write_cfgfile( tag, stream );

			file.close();

			Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
				"Channels configuration saved into file \"%1\"." )
					.arg( cfgFileName ) );
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			Log::instance().writeMsgToEventLog( LogLevelError, QString(
				"Unable to save channels configuration in file "
				"\"%1\".\n"
				"%2" )
					.arg( cfgFileName, x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to save channels configuration..." ),
				x.desc() );
		}
	}
	else
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to save channels configuration in file "
			"\"%1\".\n"
			"Unable to open file." )
				.arg( cfgFileName ) );

		QMessageBox::critical( 0,
			tr( "Unable to save channels configuration..." ),
			tr( "Unable to open file \"%1\"." ).arg( cfgFileName ) );
	}
}

void
Configuration::savePropertiesCfg( const QString & cfgFileName )
{
	PropertiesManager::instance().saveConfiguration( cfgFileName );
}

void
Configuration::saveSourcesMainWindowCfg( const QString & cfgFileName )
{
	SourcesMainWindow::instance().saveConfiguration( cfgFileName );
}

void
Configuration::saveWindowsCfg( const QString & cfgFileName )
{
	WindowsCfg cfg = MainWindow::instance().windowsCfg();

	QFile file( cfgFileName );

	if( file.open( QIODevice::WriteOnly ) )
	{
		try {
			WindowsTag tag( cfg );

			QTextStream stream( &file );

			cfgfile::write_cfgfile( tag, stream );

			file.close();

			Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
				"Windows configuration saved into file \"%1\"." )
					.arg( cfgFileName ) );
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			Log::instance().writeMsgToEventLog( LogLevelError, QString(
				"Unable to save windows configuration in file "
				"\"%1\".\n"
				"%2" )
					.arg( cfgFileName, x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to save windows configuration..." ),
				x.desc() );
		}
	}
	else
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to save windows configuration in file "
			"\"%1\".\n"
			"Unable to open file." )
				.arg( cfgFileName ) );

		QMessageBox::critical( 0,
			tr( "Unable to save windows configuration..." ),
			tr( "Unable to open file \"%1\"." ).arg( cfgFileName ) );
	}
}

void
Configuration::saveColorsCfg( const QString & cfgFileName )
{
	ColorForLevel::instance().saveCfg( cfgFileName );
}

void
Configuration::saveDbCfg( const QString & cfgFileName )
{
	DB::instance().saveCfg( cfgFileName );
}

void
Configuration::saveLogCfg( const QString & cfgFileName )
{
	Log::instance().saveCfg( cfgFileName );
}

void
Configuration::saveLogEventWindowCfg( const QString & cfgFileName )
{
	LogEventWindow::instance().saveConfiguration( cfgFileName );
}

void
Configuration::saveSoundsCfg( const QString & cfgFileName )
{
	Sounds::instance().saveCfg( cfgFileName );
}

void
Configuration::saveDisabledSoundsCfg( const QString & cfgFileName )
{
	DisabledSounds::instance().saveCfg( cfgFileName );
}

void
Configuration::saveSourcesLogWindowCfg( const QString & cfgFileName )
{
	LogSourcesWindow::instance().saveConfiguration( cfgFileName );
}

} /* namespace Globe */


/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2013 Igor Mironchik

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of d->m_mainWindow software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and d->m_mainWindow permission notice shall be
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
#include <Globe/configuration.hpp>
#include <Globe/channels.hpp>
#include <Globe/db.hpp>
#include <Globe/properties.hpp>
#include <Globe/mainwindow.hpp>
#include <Globe/application_cfg.hpp>
#include <Globe/window_state_cfg.hpp>
#include <Globe/utils.hpp>
#include <Globe/application_cfg.hpp>
#include <Globe/channels_cfg.hpp>
#include <Globe/mainwindow_cfg.hpp>
#include <Globe/channels_list.hpp>
#include <Globe/sources_mainwindow.hpp>
#include <Globe/windows_cfg.hpp>
#include <Globe/color_for_level.hpp>
#include <Globe/log.hpp>
#include <Globe/log_event_view_window.hpp>

// QtConfFile include.
#include <QtConfFile/Utils>
#include <QtConfFile/Exceptions>

// Qt include.
#include <QMessageBox>


namespace Globe {

static const QString defaultAppCfgFileName =
	QLatin1String( "./etc/Globe.cfg" );
static const QString defaultMainWindowCfgFileName =
	QLatin1String( "./etc/MainWindow.cfg" );
static const QString defaultChannelsCfgFileName =
	QLatin1String( "./etc/Channels.cfg" );
static const QString defaultPropertiesCfgFileName =
	QLatin1String( "./etc/Properties.cfg" );
static const QString defaultSourcesMainWindowCfgFileName =
	QLatin1String( "./etc/SourcesMainWindow.cfg" );
static const QString defaultWindowsCfgFileName =
	QLatin1String( "./etc/Windows.cfg" );
static const QString defaultColorsCfgFilename =
	QLatin1String( "./etc/Colors.cfg" );
static const QString defaultDbCfgFileName =
	QLatin1String( "./etc/DB.cfg" );
static const QString defaultLogCfgFileName =
	QLatin1String( "./etc/Log.cfg" );
static const QString defaultLogEventWindowCfgFileName =
	QLatin1String( "./etc/LogEventWindow.cfg" );


//
// ConfigurationPrivate
//

class ConfigurationPrivate {
public:
	ConfigurationPrivate( const QString & cfgFileName,
		MainWindow * mainWindow, ChannelsManager * channelsManager,
		DB * db, PropertiesManager * propertiesManager,
		SourcesMainWindow * sourcesMainWindow,
		LogEventWindow * logEventWindow )
		:	m_mainWindow( mainWindow )
		,	m_channelsManager( channelsManager )
		,	m_db( db )
		,	m_cfgFileName( cfgFileName )
		,	m_propertiesManager( propertiesManager )
		,	m_sourcesMainWindow( sourcesMainWindow )
		,	m_appCfgWasLoaded( false )
		,	m_colorForLevel( new ColorForLevel( m_mainWindow ) )
		,	m_logEventWindow( logEventWindow )
	{
	}

	MainWindow * m_mainWindow;
	ChannelsManager * m_channelsManager;
	DB * m_db;
	PropertiesManager * m_propertiesManager;
	SourcesMainWindow * m_sourcesMainWindow;
	LogEventWindow * m_logEventWindow;

	//! Configuration's file name.
	QString m_cfgFileName;
	//! Application's configuration.
	ApplicationCfg m_appCfg;
	//! Was application's configuration loaded?
	bool m_appCfgWasLoaded;
	//! Correspondence between level and color.
	ColorForLevel * m_colorForLevel;
}; // class ConfigurationPrivate


//
// Configuration
//

Configuration::Configuration( const QString & cfgFileName,
	MainWindow * mainWindow, ChannelsManager * channelsManager,
	DB * db, PropertiesManager * propertiesManager,
	SourcesMainWindow * sourcesMainWindow,
	LogEventWindow * logEventWindow )
	:	d( new ConfigurationPrivate( cfgFileName, mainWindow, channelsManager, db,
			propertiesManager, sourcesMainWindow, logEventWindow ) )
{
}

Configuration::~Configuration()
{
}

void
Configuration::loadConfiguration()
{
	Log::instance().writeMsgToEventLog( LogLevelInfo,
		QLatin1String( "Loading configuration..." ) );

	checkDirAndCreateIfNotExists( QLatin1String( "./" ),
		QLatin1String( "etc" ) );

	readAppCfg( d->m_cfgFileName );

	readLogCfg( d->m_appCfg.logCfgFile() );

	readDbCfg( d->m_appCfg.dbCfgFile() );

	readChannelsCfg( d->m_appCfg.channelsCfgFile() );

	readPropertiesCfg( d->m_appCfg.propertiesCfgFile() );

	readColorsCfg( d->m_appCfg.colorsCfgFile() );

	readMainWindowCfg( d->m_appCfg.mainWindowCfgFile() );

	readSourcesMainWindowCfg( d->m_appCfg.sourcesMainWindowCfgFile() );

	readLogEventWindowCfg( d->m_appCfg.logEventWindowCfgFile() );

	readWindowsCfg( d->m_appCfg.windowsCfgFile() );

	Log::instance().writeMsgToEventLog( LogLevelInfo,
		QLatin1String( "Configuration successfully loaded..." ) );
}

void
Configuration::saveConfiguration()
{
	Log::instance().writeMsgToEventLog( LogLevelInfo,
		QLatin1String( "Saving configuration..." ) );

	saveLogEventWindowCfg( d->m_appCfg.logEventWindowCfgFile() );

	saveSourcesMainWindowCfg( d->m_appCfg.sourcesMainWindowCfgFile() );

	savePropertiesCfg( d->m_appCfg.propertiesCfgFile() );

	saveChannelsCfg( d->m_appCfg.channelsCfgFile() );

	saveMainWindowCfg( d->m_appCfg.mainWindowCfgFile() );

	saveWindowsCfg( d->m_appCfg.windowsCfgFile() );

	saveColorsCfg( d->m_appCfg.colorsCfgFile() );

	saveDbCfg( d->m_appCfg.dbCfgFile() );

	saveLogCfg( d->m_appCfg.logCfgFile() );

	saveAppCfg( d->m_cfgFileName );

	Log::instance().writeMsgToEventLog( LogLevelInfo,
		QLatin1String( "Configuration successfully saved..." ) );
}

ColorForLevel *
Configuration::colorForLevel() const
{
	return d->m_colorForLevel;
}

void
Configuration::readAppCfg( const QString & cfgFileName )
{
	if( cfgFileName.isEmpty() )
		d->m_cfgFileName = defaultAppCfgFileName;
	else
		d->m_cfgFileName = cfgFileName;

	try {
		ApplicationCfgTag appCfgTag;

		QtConfFile::readQtConfFile( appCfgTag,
			d->m_cfgFileName, QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
			"Application's configuration loaded from file \"%1\"." )
				.arg( cfgFileName ) );

		d->m_appCfg = appCfgTag.cfg();

		d->m_appCfgWasLoaded = true;
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to load application's configuration from file "
			"\"%1\".\n"
			"%2" )
				.arg( cfgFileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( d->m_mainWindow,
			tr( "Unable to load Globe's configuration file..." ),
			x.whatAsQString() );
	}
}

void
Configuration::readMainWindowCfg( const QString & cfgFileName )
{
	MainWindowCfg cfg;

	try {
		if( !cfgFileName.isEmpty() )
		{
			MainWindowCfgTag tag;

			QtConfFile::readQtConfFile( tag, cfgFileName,
				QTextCodec::codecForName( "UTF-8" ) );

			Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
				"Main window's configuration loaded from file \"%1\"." )
					.arg( cfgFileName ) );

			cfg = tag.cfg();
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
						.arg( defaultMainWindowCfgFileName ) );

				QMessageBox::warning( d->m_mainWindow,
					tr( "Error in application's configuration..." ),
					tr( "Not specified main window's configuration file.\n"
						"Main window's configuration will not be loaded.\n"
						"At exit configuration of the main window will be saved\n"
						"in \"%1\" file." )
							.arg( defaultMainWindowCfgFileName ) );
			}
		}
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to load main window's configuration from file "
			"\"%1\".\n"
			"%2" )
				.arg( cfgFileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( d->m_mainWindow,
			tr( "Unable to load main window's configuration..." ),
			x.whatAsQString() );

		return;
	}

	d->m_mainWindow->list()->setShownChannelsMode( cfg.shownChannels() );
	restoreWindowState( cfg.windowState(), d->m_mainWindow );
}

void
Configuration::readChannelsCfg( const QString & cfgFileName )
{
	AvailableChannelsCfg cfg;

	try {
		if( !cfgFileName.isEmpty() )
		{
			AvailableChannelsCfgTag tag;

			QtConfFile::readQtConfFile( tag, cfgFileName,
				QTextCodec::codecForName( "UTF-8" ) );

			Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
				"Channel's configuration loaded from file \"%1\"." )
					.arg( cfgFileName ) );

			cfg = tag.cfg();
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
						.arg( defaultChannelsCfgFileName ) );

				QMessageBox::warning( d->m_mainWindow,
					tr( "Error in application's configuration..." ),
					tr( "Not specified channel's configuration file.\n"
						"Channel's configuration will not be loaded.\n"
						"At exit channels configuration will be saved\n"
						"in \"%1\" file." )
							.arg( defaultChannelsCfgFileName ) );
			}
		}
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to load channels configuration from file "
			"\"%1\".\n"
			"%2" )
				.arg( cfgFileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( d->m_mainWindow,
			tr( "Unable to load channels configuration..." ),
			x.whatAsQString() );

		return;
	}

	foreach( const ChannelCfg & channelCfg, cfg )
	{
		Channel * channel = d->m_channelsManager->createChannel( channelCfg.name(),
			channelCfg.address(), channelCfg.port() );

		if( channel )
		{
			d->m_mainWindow->list()->addChannel( channel );

			if( channelCfg.timeout() )
				channel->updateTimeout( channelCfg.timeout() );

			if( channelCfg.isMustBeConnected() )
				channel->connectToHost();
		}
		else if( !d->m_channelsManager->isNameUnique( channelCfg.name() ) )
		{
			Log::instance().writeMsgToEventLog( LogLevelError, QString(
				"Unable to create new channel...\n"
				"Channel with name \"%1\" already exists." )
					.arg( channelCfg.name() ) );

			QMessageBox::critical( d->m_mainWindow,
				tr( "Unable to create new channel..." ),
				tr( "Channel with name \"%1\" already exists." )
					.arg( channelCfg.name() ) );
		}
		else if( !d->m_channelsManager->isAddressAndPortUnique(
			channelCfg.address(), channelCfg.port() ) )
		{
			Log::instance().writeMsgToEventLog( LogLevelError, QString(
				"Unable to create new channel...\n"
				"Channel with address \"%1\" and port %2 already exists." )
					.arg( channelCfg.address().toString() )
					.arg( QString::number( channelCfg.port() ) ) );

			QMessageBox::critical( d->m_mainWindow,
				tr( "Unable to create new channel..." ),
				tr( "Channel with address \"%1\" and port %2 already exists." )
					.arg( channelCfg.address().toString() )
					.arg( QString::number( channelCfg.port() ) ) );
		}
	}
}

void
Configuration::readPropertiesCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		d->m_propertiesManager->readConfiguration( cfgFileName );
	else
	{
		d->m_appCfg.setPropertiesCfgFile( defaultPropertiesCfgFileName );

		if( d->m_appCfgWasLoaded )
		{
			Log::instance().writeMsgToEventLog( LogLevelWarning, QString(
				"Error in application's configuration...\n"
				"Not specified properties configuration file.\n"
				"Properties configuration will not be loaded.\n"
				"At exit properties configuration will be saved\n"
				"in \"%1\" file." )
					.arg( defaultPropertiesCfgFileName ) );

			QMessageBox::warning( d->m_mainWindow,
				tr( "Error in application's configuration..." ),
				tr( "Not specified properties configuration file.\n"
					"Properties configuration will not be loaded.\n"
					"At exit properties configuration will be saved\n"
					"in \"%1\" file." )
						.arg( defaultPropertiesCfgFileName ) );
		}
	}
}

void
Configuration::readSourcesMainWindowCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		d->m_sourcesMainWindow->readConfiguration( cfgFileName );
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
					.arg( defaultSourcesMainWindowCfgFileName ) );

			QMessageBox::warning( d->m_mainWindow,
				tr( "Error in application's configuration..." ),
				tr( "Not specified sources main window configuration file.\n"
					"Sources main window configuration will not be loaded.\n"
					"At exit sources main window configuration will be saved\n"
					"in \"%1\" file." )
						.arg( defaultSourcesMainWindowCfgFileName ) );
		}
	}
}

void
Configuration::readWindowsCfg( const QString & cfgFileName )
{
	WindowsCfg cfg;

	try {
		if( !cfgFileName.isEmpty() )
		{
			WindowsTag tag;

			QtConfFile::readQtConfFile( tag, cfgFileName,
				QTextCodec::codecForName( "UTF-8" ) );

			Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
				"Windows configuration loaded from file \"%1\"." )
					.arg( cfgFileName ) );

			cfg = tag.cfg();
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
						.arg( defaultWindowsCfgFileName ) );

				QMessageBox::warning( d->m_mainWindow,
					tr( "Error in application's configuration..." ),
					tr( "Not specified windows configuration file.\n"
						"Windows configuration will not be loaded.\n"
						"At exit configuration of the windows will be saved\n"
						"in \"%1\" file." )
							.arg( defaultWindowsCfgFileName ) );
			}
		}
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to load windows configuration from file "
			"\"%1\".\n"
			"%2" )
				.arg( cfgFileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( d->m_mainWindow,
			tr( "Unable to load windows configuration..." ),
			x.whatAsQString() );

		return;
	}

	d->m_mainWindow->restoreWindows( cfg );
}

void
Configuration::readColorsCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		d->m_colorForLevel->readCfg( cfgFileName );
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
					.arg( defaultColorsCfgFilename ) );

			QMessageBox::warning( d->m_mainWindow,
				tr( "Error in application's configuration..." ),
				tr( "Not specified colors configuration file.\n"
					"Colors configuration will not be loaded.\n"
					"At exit colors configuration will be saved\n"
					"in \"%1\" file." )
						.arg( defaultColorsCfgFilename ) );
		}
	}
}

void
Configuration::readDbCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		d->m_db->readCfg( cfgFileName );
	else
	{
		d->m_appCfg.setDbCfgFile( defaultDbCfgFileName );

		if( d->m_appCfgWasLoaded )
		{
			Log::instance().writeMsgToEventLog( LogLevelWarning, QString(
				"Error in application's configuration...\n"
				"Not specified DB configuration file.\n"
				"DB configuration will not be loaded.\n"
				"At exit DB configuration will be saved\n"
				"in \"%1\" file." )
					.arg( defaultDbCfgFileName ) );

			QMessageBox::warning( d->m_mainWindow,
				tr( "Error in application's configuration..." ),
				tr( "Not specified DB configuration file.\n"
					"DB configuration will not be loaded.\n"
					"At exit DB configuration will be saved\n"
					"in \"%1\" file." )
						.arg( defaultDbCfgFileName ) );
		}
	}
}

void
Configuration::readLogCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		Log::instance().readCfg( cfgFileName );
	else
	{
		d->m_appCfg.setLogCfgFile( defaultLogCfgFileName );

		if( d->m_appCfgWasLoaded )
		{
			Log::instance().writeMsgToEventLog( LogLevelWarning, QString(
				"Error in application's configuration...\n"
				"Not specified log configuration file.\n"
				"Log configuration will not be loaded.\n"
				"At exit log configuration will be saved\n"
				"in \"%1\" file." )
					.arg( defaultLogCfgFileName ) );

			QMessageBox::warning( d->m_mainWindow,
				tr( "Error in application's configuration..." ),
				tr( "Not specified log configuration file.\n"
					"Log configuration will not be loaded.\n"
					"At exit log configuration will be saved\n"
					"in \"%1\" file." )
						.arg( defaultLogCfgFileName ) );
		}
	}
}

void
Configuration::readLogEventWindowCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		d->m_logEventWindow->readConfiguration( cfgFileName );
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
					.arg( defaultLogEventWindowCfgFileName ) );

			QMessageBox::warning( d->m_mainWindow,
				tr( "Error in application's configuration..." ),
				tr( "Not specified event's log window configuration file.\n"
					"Event's log window configuration will not be loaded.\n"
					"At exit event's log window configuration will be saved\n"
					"in \"%1\" file." )
						.arg( defaultLogEventWindowCfgFileName ) );
		}
	}
}

void
Configuration::saveAppCfg( const QString & cfgFileName )
{
	try {
		ApplicationCfgTag tag( d->m_appCfg );

		QtConfFile::writeQtConfFile( tag, cfgFileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
			"Application's configuration saved into file \"%1\"." )
				.arg( cfgFileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to save application's configuration in file "
			"\"%1\".\n"
			"%2" )
				.arg( cfgFileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( d->m_mainWindow,
			tr( "Unable to save application's configuration..." ),
			x.whatAsQString() );
	}
}

void
Configuration::saveMainWindowCfg( const QString & cfgFileName )
{
	ShownChannels shownChannels = d->m_mainWindow->list()->shownChannelsMode();

	MainWindowCfg mainWindowCfg( windowStateCfg( d->m_mainWindow ), shownChannels );

	try {
		MainWindowCfgTag tag( mainWindowCfg );

		QtConfFile::writeQtConfFile( tag, cfgFileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
			"Main window's configuration saved into file \"%1\"." )
				.arg( cfgFileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to save main window's configuration in file "
			"\"%1\".\n"
			"%2" )
				.arg( cfgFileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( d->m_mainWindow,
			tr( "Unable to save main window's configuration..." ),
			x.whatAsQString() );
	}
}

void
Configuration::saveChannelsCfg( const QString & cfgFileName )
{
	QList< Channel* > channels = d->m_channelsManager->channels();
	AvailableChannelsCfg channelsCfg;

	foreach( Channel * channel, channels )
	{
		ChannelCfg chCfg;

		chCfg.setName( channel->name() );
		chCfg.setAddress( channel->hostAddress() );
		chCfg.setPort( channel->portNumber() );
		chCfg.setMustBeConnected( channel->isMustBeConnected() );
		chCfg.setTimeout( channel->timeout() );

		channelsCfg.append( chCfg );
	}

	try {
		AvailableChannelsCfgTag tag( channelsCfg );

		QtConfFile::writeQtConfFile( tag, cfgFileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
			"Channels configuration saved into file \"%1\"." )
				.arg( cfgFileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to save channels configuration in file "
			"\"%1\".\n"
			"%2" )
				.arg( cfgFileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( d->m_mainWindow,
			tr( "Unable to save channels configuration..." ),
			x.whatAsQString() );
	}
}

void
Configuration::savePropertiesCfg( const QString & cfgFileName )
{
	d->m_propertiesManager->saveConfiguration( cfgFileName );
}

void
Configuration::saveSourcesMainWindowCfg( const QString & cfgFileName )
{
	d->m_sourcesMainWindow->saveConfiguration( cfgFileName );
}

void
Configuration::saveWindowsCfg( const QString & cfgFileName )
{
	WindowsCfg cfg = d->m_mainWindow->windowsCfg();

	try {
		WindowsTag tag( cfg );

		QtConfFile::writeQtConfFile( tag, cfgFileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
			"Windows configuration saved into file \"%1\"." )
				.arg( cfgFileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to save windows configuration in file "
			"\"%1\".\n"
			"%2" )
				.arg( cfgFileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( d->m_mainWindow,
			tr( "Unable to save windows configuration..." ),
			x.whatAsQString() );
	}
}

void
Configuration::saveColorsCfg( const QString & cfgFileName )
{
	d->m_colorForLevel->saveCfg( cfgFileName );
}

void
Configuration::saveDbCfg( const QString & cfgFileName )
{
	d->m_db->saveCfg( cfgFileName );
}

void
Configuration::saveLogCfg( const QString & cfgFileName )
{
	Log::instance().saveCfg( cfgFileName );
}

void
Configuration::saveLogEventWindowCfg( const QString & cfgFileName )
{
	d->m_logEventWindow->saveConfiguration( cfgFileName );
}

} /* namespace Globe */

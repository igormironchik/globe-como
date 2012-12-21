
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 Igor Mironchik

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

// QtConfFile include.
#include <QtConfFile/Utils>
#include <QtConfFile/Exceptions>

// Qt include.
#include <QtGui/QMessageBox>


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


//
// ConfigurationPrivate
//

class ConfigurationPrivate {
public:
	ConfigurationPrivate( const QString & cfgFileName,
		MainWindow * mainWindow, ChannelsManager * channelsManager,
		DB * db, PropertiesManager * propertiesManager,
		SourcesMainWindow * sourcesMainWindow )
		:	m_mainWindow( mainWindow )
		,	m_channelsManager( channelsManager )
		,	m_db( db )
		,	m_cfgFileName( cfgFileName )
		,	m_propertiesManager( propertiesManager )
		,	m_sourcesMainWindow( sourcesMainWindow )
		,	m_appCfgWasLoaded( false )
	{
	}

	MainWindow * m_mainWindow;
	ChannelsManager * m_channelsManager;
	DB * m_db;
	PropertiesManager * m_propertiesManager;
	SourcesMainWindow * m_sourcesMainWindow;

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

Configuration::Configuration( const QString & cfgFileName,
	MainWindow * mainWindow, ChannelsManager * channelsManager,
	DB * db, PropertiesManager * propertiesManager,
	SourcesMainWindow * sourcesMainWindow )
	:	d( new ConfigurationPrivate( cfgFileName, mainWindow, channelsManager, db,
			propertiesManager, sourcesMainWindow ) )
{
}

Configuration::~Configuration()
{
}

void
Configuration::loadConfiguration()
{
	readAppCfg( d->m_cfgFileName );

	readMainWindowCfg( d->m_appCfg.mainWindowCfgFile() );

	readChannelsCfg( d->m_appCfg.channelsCfgFile() );

	readPropertiesCfg( d->m_appCfg.propertiesCfgFile() );

	readSourcesMainWindowCfg( d->m_appCfg.sourcesMainWindowCfgFile() );
}

void
Configuration::saveConfiguration()
{
	saveSourcesMainWindowCfg( d->m_appCfg.sourcesMainWindowCfgFile() );

	savePropertiesCfg( d->m_appCfg.propertiesCfgFile() );

	saveChannelsCfg( d->m_appCfg.channelsCfgFile() );

	saveMainWindowCfg( d->m_appCfg.mainWindowCfgFile() );

	saveAppCfg( d->m_cfgFileName );
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

		d->m_appCfg = appCfgTag.cfg();

		d->m_appCfgWasLoaded = true;
	}
	catch( const QtConfFile::Exception & x )
	{
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

			cfg = tag.cfg();
		}
		else
		{
			d->m_appCfg.setMainWindowCfgFile( defaultMainWindowCfgFileName );

			if( d->m_appCfgWasLoaded )
				QMessageBox::warning( d->m_mainWindow,
					tr( "Error in application's configuration..." ),
					tr( "Not specified main window's configuration file.\n"
						"Main window's configuration will not be loaded.\n"
						"At exit configuration of the main window will be saved\n"
						"in \"%1\" file." )
							.arg( defaultMainWindowCfgFileName ) );
		}
	}
	catch( const QtConfFile::Exception & x )
	{
		QMessageBox::critical( d->m_mainWindow,
			tr( "Unable to load main window's configuration..." ),
			x.whatAsQString() );
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

			cfg = tag.cfg();
		}
		else
		{
			d->m_appCfg.setChannelsCfgFile( defaultChannelsCfgFileName );

			if( d->m_appCfgWasLoaded )
				QMessageBox::warning( d->m_mainWindow,
					tr( "Error in application's configuration..." ),
					tr( "Not specified channel's configuration file.\n"
						"Channel's configuration will not be loaded.\n"
						"At exit channels configuration will be saved\n"
						"in \"%1\" file." )
							.arg( defaultChannelsCfgFileName ) );
		}
	}
	catch( const QtConfFile::Exception & x )
	{
		QMessageBox::critical( d->m_mainWindow,
			tr( "Unable to load channels configuration..." ),
			x.whatAsQString() );
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
			QMessageBox::critical( d->m_mainWindow, tr( "Unable to create new channel..." ),
				tr( "Channel with name \"%1\" already exists." )
					.arg( channelCfg.name() ) );
		else if( !d->m_channelsManager->isAddressAndPortUnique(
			channelCfg.address(), channelCfg.port() ) )
				QMessageBox::critical( d->m_mainWindow, tr( "Unable to create new channel..." ),
					tr( "Channel with address \"%1\" and port %2 already exists." )
						.arg( channelCfg.address().toString() )
						.arg( QString::number( channelCfg.port() ) ) );
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
			QMessageBox::warning( d->m_mainWindow,
				tr( "Error in application's configuration..." ),
				tr( "Not specified properties configuration file.\n"
					"Properties configuration will not be loaded.\n"
					"At exit properties configuration will be saved\n"
					"in \"%1\" file." )
						.arg( defaultPropertiesCfgFileName ) );
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
			QMessageBox::warning( d->m_mainWindow,
				tr( "Error in application's configuration..." ),
				tr( "Not specified sources main window configuration file.\n"
					"Sources main window configuration will not be loaded.\n"
					"At exit sources main window configuration will be saved\n"
					"in \"%1\" file." )
						.arg( defaultSourcesMainWindowCfgFileName ) );
	}
}

void
Configuration::saveAppCfg( const QString & cfgFileName )
{
	ApplicationCfgTag tag( d->m_appCfg );

	try {
		QtConfFile::writeQtConfFile( tag, cfgFileName,
			QTextCodec::codecForName( "UTF-8" ) );
	}
	catch( const QtConfFile::Exception & x )
	{
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

	MainWindowCfgTag tag( mainWindowCfg );

	try {
		QtConfFile::writeQtConfFile( tag, cfgFileName,
			QTextCodec::codecForName( "UTF-8" ) );
	}
	catch( const QtConfFile::Exception & x )
	{
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

	AvailableChannelsCfgTag tag( channelsCfg );

	try {
		QtConfFile::writeQtConfFile( tag, cfgFileName,
			QTextCodec::codecForName( "UTF-8" ) );
	}
	catch( const QtConfFile::Exception & x )
	{
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

} /* namespace Globe */

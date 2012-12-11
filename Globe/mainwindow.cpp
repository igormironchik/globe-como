
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
#include <Globe/channels.hpp>
#include <Globe/db.hpp>
#include <Globe/channels_list.hpp>
#include <Globe/application_cfg.hpp>
#include <Globe/channels_cfg.hpp>
#include <Globe/mainwindow_cfg.hpp>
#include <Globe/utils.hpp>
#include <Globe/window_state_cfg.hpp>
#include <Globe/properties.hpp>

// QtConfFile include.
#include <QtConfFile/Utils>
#include <QtConfFile/Exceptions>

// Qt include.
#include <QtGui/QApplication>
#include <QtGui/QMessageBox>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QAction>


namespace Globe {

static const QString defaultAppCfgFileName =
	QLatin1String( "./etc/Globe.cfg" );
static const QString defaultMainWindowCfgFileName =
	QLatin1String( "./etc/MainWindow.cfg" );
static const QString defaultChannelsCfgFileName =
	QLatin1String( "./etc/Channels.cfg" );
static const QString defaultPropertiesCfgFileName =
	QLatin1String( "./etc/Properties.cfg" );

//
// MainWindowPrivate
//

class MainWindowPrivate {
public:
	MainWindowPrivate( const QString & cfgFileName,
		ChannelsManager * channelsManager, DB * db,
		PropertiesManager * propertiesManager )
		:	m_cfgFileName( cfgFileName )
		,	m_channelsManager( channelsManager )
		,	m_db( db )
		,	m_list( 0 )
		,	m_appCfgWasLoaded( false )
		,	m_propertiesManager( propertiesManager )
	{
	}

	//! Configuration's file name.
	QString m_cfgFileName;
	//! Channels manager.
	ChannelsManager * m_channelsManager;
	//! Database.
	DB * m_db;
	//! Application's configuration.
	ApplicationCfg m_appCfg;
	//! List with channels.
	ChannelsList * m_list;
	//! Main window's configuration.
	MainWindowCfg m_mainWindowCfg;
	//! Was application's configuration loaded?
	bool m_appCfgWasLoaded;
	//! Properties manager.
	PropertiesManager * m_propertiesManager;
}; // class MainWindowPrivate


//
// MainWindow
//

MainWindow::MainWindow( const QString & cfgFileName,
	ChannelsManager * channelsManager, DB * db,
	PropertiesManager * propertiesManager,
	QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new MainWindowPrivate( cfgFileName, channelsManager, db,
			propertiesManager ) )
{
}

MainWindow::~MainWindow()
{
}

void
MainWindow::init()
{
	connect( qApp, SIGNAL( aboutToQuit() ),
		this, SLOT( aboutToQuit() ) );

	QMenu * fileMenu = menuBar()->addMenu( tr( "&File" ) );
	fileMenu->addAction( QIcon( ":/img/exit_22x22.png" ),
		tr( "E&xit" ), qApp, SLOT( quit() ), QKeySequence( tr( "Ctrl+Q" ) ) );

	readAppCfg( d->m_cfgFileName );

	readMainWindowCfg( d->m_appCfg.mainWindowCfgFile() );

	readChannelsCfg( d->m_appCfg.channelsCfgFile() );

	readPropertiesCfg( d->m_appCfg.propertiesCfgFile() );

	show();
}

void
MainWindow::aboutToQuit()
{
	savePropertiesCfg( d->m_appCfg.propertiesCfgFile() );

	saveChannelsCfg( d->m_appCfg.channelsCfgFile() );

	saveMainWindowCfg( d->m_appCfg.mainWindowCfgFile() );

	saveAppCfg( d->m_cfgFileName );
}

void
MainWindow::readAppCfg( const QString & cfgFileName )
{
	if( cfgFileName.isEmpty() )
		d->m_cfgFileName = defaultAppCfgFileName;

	try {
		ApplicationCfgTag appCfgTag;

		QtConfFile::readQtConfFile( appCfgTag,
			d->m_cfgFileName, QTextCodec::codecForName( "UTF-8" ) );

		d->m_appCfg = appCfgTag.cfg();

		d->m_appCfgWasLoaded = true;
	}
	catch( const QtConfFile::Exception & x )
	{
		QMessageBox::critical( this,
			tr( "Unable to load Globe's configuration file..." ),
			x.whatAsQString() );
	}
}

void
MainWindow::readMainWindowCfg( const QString & cfgFileName )
{
	try {
		if( !cfgFileName.isEmpty() )
		{
			MainWindowCfgTag tag;

			QtConfFile::readQtConfFile( tag, cfgFileName,
				QTextCodec::codecForName( "UTF-8" ) );

			d->m_mainWindowCfg = tag.cfg();
		}
		else
		{
			d->m_appCfg.setMainWindowCfgFile( defaultMainWindowCfgFileName );

			if( d->m_appCfgWasLoaded )
				QMessageBox::warning( this,
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
		QMessageBox::critical( this,
			tr( "Unable to load main window's configuration..." ),
			x.whatAsQString() );
	}

	d->m_list = new ChannelsList( d->m_channelsManager,
		d->m_mainWindowCfg.shownChannels(), Qt::AscendingOrder, this );

	setCentralWidget( d->m_list );

	restoreWindowState( d->m_mainWindowCfg.windowState(), this );
}

void
MainWindow::readChannelsCfg( const QString & cfgFileName )
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
				QMessageBox::warning( this,
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
		QMessageBox::critical( this,
			tr( "Unable to load channels configuration..." ),
			x.whatAsQString() );
	}

	foreach( const ChannelCfg & channelCfg, cfg )
	{
		Channel * channel = d->m_channelsManager->createChannel( channelCfg.name(),
			channelCfg.address(), channelCfg.port() );

		if( channel )
		{
			d->m_list->addChannel( channel );

			if( channelCfg.timeout() )
				channel->updateTimeout( channelCfg.timeout() );

			if( channelCfg.isMustBeConnected() )
				channel->connectToHost();
		}
		else if( !d->m_channelsManager->isNameUnique( channelCfg.name() ) )
			QMessageBox::critical( this, tr( "Unable to create new channel..." ),
				tr( "Channel with name \"%1\" already exists." )
					.arg( channelCfg.name() ) );
		else if( !d->m_channelsManager->isAddressAndPortUnique(
			channelCfg.address(), channelCfg.port() ) )
				QMessageBox::critical( this, tr( "Unable to create new channel..." ),
					tr( "Channel with address \"%1\" and port %2 already exists." )
						.arg( channelCfg.address().toString() )
						.arg( QString::number( channelCfg.port() ) ) );
	}
}

void
MainWindow::readPropertiesCfg( const QString & cfgFileName )
{
	if( !cfgFileName.isEmpty() )
		d->m_propertiesManager->readConfiguration( cfgFileName );
	else
	{
		d->m_appCfg.setPropertiesCfgFile( defaultPropertiesCfgFileName );

		if( d->m_appCfgWasLoaded )
			QMessageBox::warning( this,
				tr( "Error in application's configuration..." ),
				tr( "Not specified properties configuration file.\n"
					"Properties configuration will not be loaded.\n"
					"At exit properties configuration will be saved\n"
					"in \"%1\" file." )
						.arg( defaultPropertiesCfgFileName ) );
	}
}

void
MainWindow::saveAppCfg( const QString & cfgFileName )
{
	ApplicationCfg appCfg;

	appCfg.setMainWindowCfgFile( relativeFilePath(
		d->m_appCfg.mainWindowCfgFile() ) );
	appCfg.setChannelsCfgFile( relativeFilePath(
		d->m_appCfg.channelsCfgFile() ) );
	appCfg.setPropertiesCfgFile( relativeFilePath(
		d->m_appCfg.propertiesCfgFile() ) );

	ApplicationCfgTag tag( appCfg );

	try {
		QtConfFile::writeQtConfFile( tag, cfgFileName,
			QTextCodec::codecForName( "UTF-8" ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		QMessageBox::critical( this,
			tr( "Unable to save application's configuration..." ),
			x.whatAsQString() );
	}
}

void
MainWindow::saveMainWindowCfg( const QString & cfgFileName )
{
	ShownChannels shownChannels = d->m_list->shownChannelsMode();

	MainWindowCfg mainWindowCfg( windowStateCfg( this ), shownChannels );

	MainWindowCfgTag tag( mainWindowCfg );

	try {
		QtConfFile::writeQtConfFile( tag, cfgFileName,
			QTextCodec::codecForName( "UTF-8" ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		QMessageBox::critical( this,
			tr( "Unable to save main window's configuration..." ),
			x.whatAsQString() );
	}
}

void
MainWindow::saveChannelsCfg( const QString & cfgFileName )
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
		QMessageBox::critical( this,
			tr( "Unable to save channels configuration..." ),
			x.whatAsQString() );
	}
}

void
MainWindow::savePropertiesCfg( const QString & cfgFileName )
{
	d->m_propertiesManager->saveConfiguration( cfgFileName );
}

} /* namespace Globe */


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
#include <Core/sounds.hpp>
#include <Core/globe_menu.hpp>
#include <Core/tool_window_object.hpp>
#include <Core/sounds_disabled.hpp>
#include <Core/sounds_cfg.hpp>
#include <Core/log.hpp>
#include <Core/utils.hpp>
#include <Core/sounds_played_view.hpp>
#include <Core/sounds_played_model.hpp>
#include <Core/sounds_disabled_view.hpp>

// Qt include.
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTabWidget>
#include <QCoreApplication>
#include <QTextCodec>
#include <QFile>

// cfgfile include.
#include <cfgfile/all.hpp>


namespace Globe {

//
// SoundsPrivate
//

class SoundsPrivate {
public:
	SoundsPrivate()
		:	m_toolWindowObject( 0 )
		,	m_level( None )
		,	m_player( 0 )
		,	m_tabs( 0 )
		,	m_playedSoundsView( 0 )
		,	m_disabledSoundsView( 0 )
	{
	}

	//! Tool window object.
	ToolWindowObject * m_toolWindowObject;
	//! Level of the current sound.
	Level m_level;
	//! Configuration.
	SoundsCfg m_cfg;
	//! Player.
	QMediaPlayer * m_player;
	//! Tab widget.
	QTabWidget * m_tabs;
	//! Played sounds widget.
	PlayedSoundsView * m_playedSoundsView;
	//! Disabled sounds view.
	DisabledSoundsView * m_disabledSoundsView;
}; // class SoundsPrivate


//
// Sounds
//

Sounds::Sounds( QWidget * parent, Qt::WindowFlags f )
	:	QMainWindow( parent, f )
	,	d( new SoundsPrivate )
{
	init();
}

Sounds::~Sounds()
{
}

static Sounds * soundsInstancePointer = 0;

void
Sounds::cleanup()
{
	delete soundsInstancePointer;

	soundsInstancePointer = 0;
}

Sounds &
Sounds::instance()
{
	if( !soundsInstancePointer )
	{
		soundsInstancePointer = new Sounds;

		qAddPostRoutine( &Sounds::cleanup );
	}

	return *soundsInstancePointer;
}

ToolWindowObject *
Sounds::toolWindowObject()
{
	return d->m_toolWindowObject;
}

void
Sounds::initMenu( const Menu & menu )
{
	menuBar()->addMenu( menu.fileMenu() );

	QMenu * toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );

	foreach( ToolWindowObject * obj, menu.toolWindows() )
		if( obj != d->m_toolWindowObject )
			toolsMenu->addAction( obj->menuEntity() );

	menuBar()->addMenu( menu.settingsMenu() );
}

void
Sounds::readCfg( const QString & fileName )
{
	SoundsCfgTag tag;

	QFile file( fileName );

	if( file.open( QIODevice::ReadOnly ) )
	{
		try {
			QTextStream stream( &file );
			stream.setCodec( QTextCodec::codecForName( "UTF-8" ) );

			cfgfile::read_cfgfile( tag, stream, fileName );

			file.close();

			Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
				"Sounds configuration read from file \"%1\"." )
					.arg( fileName ) );
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			Log::instance().writeMsgToEventLog( LogLevelError, QString(
				"Unable to read sounds configuration from file \"%1\".\n"
				"%2" )
					.arg( fileName )
					.arg( x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to read sounds configuration..." ),
				tr( "Unable to read sounds configuration...\n\n%1" )
					.arg( x.desc() ) );

			return;
		}
	}
	else
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to read sounds configuration from file \"%1\".\n"
			"Unable to open file." )
				.arg( fileName ) );

		QMessageBox::critical( 0,
			tr( "Unable to read sounds configuration..." ),
			tr( "Unable to read sounds configuration...\n\n"
				"Unable to open file." ) );

		return;
	}

	d->m_cfg = tag.cfg();

	restoreWindowState( d->m_cfg.windowState(), this );
}

void
Sounds::saveCfg( const QString & fileName )
{
	QFile file( fileName );

	if( file.open( QIODevice::WriteOnly ) )
	{
		try {
			d->m_cfg.setWindowState( windowStateCfg( this ) );

			SoundsCfgTag tag( d->m_cfg );

			QTextStream stream( &file );
			stream.setCodec( QTextCodec::codecForName( "UTF-8" ) );

			cfgfile::write_cfgfile( tag, stream );

			file.close();

			Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
				"Sounds configuration saved to file \"%1\"." )
					.arg( fileName ) );
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			Log::instance().writeMsgToEventLog( LogLevelError, QString(
				"Unable to save sounds configuration to file \"%1\".\n"
				"%2" )
					.arg( fileName )
					.arg( x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to save sounds configuration..." ),
				tr( "Unable to save sounds configuration...\n\n%1" )
					.arg( x.desc() ) );
		}
	}
	else
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to save sounds configuration to file \"%1\".\n"
			"Unable to open file." )
				.arg( fileName ) );

		QMessageBox::critical( 0,
			tr( "Unable to save sounds configuration..." ),
			tr( "Unable to save sounds configuration...\n\n"
				"Unable to open file." ) );
	}
}

const SoundsCfg &
Sounds::cfg() const
{
	return d->m_cfg;
}

void
Sounds::setCfg( const SoundsCfg & c )
{
	d->m_cfg = c;
}

bool
Sounds::isSoundEnabled( Level level )
{
	switch( level )
	{
		case Critical : return d->m_cfg.isCriticalSoundEnabled();
		case Error : return d->m_cfg.isErrorSoundEnabled();
		case Warning : return d->m_cfg.isWarningSoundEnabled();
		case Debug : return d->m_cfg.isDebugSoundEnabled();
		case Info : return d->m_cfg.isInfoSoundEnabled();
		default : return false;
	}
}

const QString &
Sounds::soundFileName( Level level )
{
	static QString dummy = QString();

	switch( level )
	{
		case Critical : return d->m_cfg.criticalSoundFile();
		case Error : return d->m_cfg.errorSoundFile();
		case Warning : return d->m_cfg.warningSoundFile();
		case Debug : return d->m_cfg.debugSoundFile();
		case Info : return d->m_cfg.infoSoundFile();
		default : return dummy;
	}
}

void
Sounds::playSound( Level level, const Como::Source & source,
	const QString & channelName )
{
	if( level <= d->m_level && isSoundEnabled( level ) )
	{
		if( DisabledSounds::instance().isSoundsEnabled( source, channelName ) )
		{
			d->m_player->stop();
			d->m_player->setMedia( QUrl::fromLocalFile( soundFileName( level ) ) );
			d->m_player->play();

			d->m_level = level;

			d->m_playedSoundsView->model()->addRecord(
				PlayedSoundsModelRecord( QDateTime::currentDateTime(),
					level, channelName, source ) );
		}
	}
}

void
Sounds::playerStateChanged( QMediaPlayer::State state )
{
	if( state == QMediaPlayer::StoppedState )
		d->m_level = None;
}

void
Sounds::closeEvent( QCloseEvent * event )
{
	hide();

	event->accept();
}

void
Sounds::init()
{
	checkDirAndCreateIfNotExists( QLatin1String( "./etc" ),
		QLatin1String( "sounds" ) );

	setWindowTitle( tr( "Sounds" ) );

	QAction * showAction = new QAction( tr( "S&ounds" ), this );
	showAction->setShortcut( QKeySequence( tr( "Alt+D" ) ) );
	d->m_toolWindowObject = new ToolWindowObject( showAction, this, this );

	d->m_player = new QMediaPlayer( this );

	connect( d->m_player, &QMediaPlayer::stateChanged,
		this, &Sounds::playerStateChanged );

	d->m_tabs = new QTabWidget( this );

	setCentralWidget( d->m_tabs );

	d->m_playedSoundsView = new PlayedSoundsView( this );

	d->m_tabs->addTab( d->m_playedSoundsView, tr( "Played Sounds" ) );

	d->m_disabledSoundsView = new DisabledSoundsView( this );

	d->m_tabs->addTab( d->m_disabledSoundsView, tr( "Disabled Sounds" ) );
}

} /* namespace Globe */

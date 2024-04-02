
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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
#include <Core/configuration.hpp>

// Qt include.
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTabWidget>
#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>

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
					.arg( fileName, x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to read sounds configuration..." ),
				x.desc() );

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
			tr( "Unable to open file \"%1\"." ).arg( fileName ) );

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
					.arg( fileName, x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to save sounds configuration..." ),
				x.desc() );
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
			tr( "Unable to open file \"%1\"." ).arg( fileName ) );
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
Sounds::playSound( Globe::Level level, const Como::Source & source,
	const QString & channelName )
{
	if( level <= d->m_level && isSoundEnabled( level ) )
	{
		if( DisabledSounds::instance().isSoundsEnabled( source, channelName ) )
		{
			d->m_player->stop();
			d->m_player->setSource( QUrl::fromLocalFile(
				QFileInfo( Configuration::instance().path() + soundFileName( level ) )
					.absoluteFilePath() ) );
			d->m_player->play();

			d->m_level = level;

			d->m_playedSoundsView->model()->addRecord(
				PlayedSoundsModelRecord( QDateTime::currentDateTime(),
					level, channelName, source ) );
		}
	}
}

void
Sounds::playerStateChanged( QMediaPlayer::PlaybackState state )
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
	setWindowTitle( tr( "Sounds" ) );

	QAction * showAction = new QAction( tr( "S&ounds" ), this );
	showAction->setShortcut( QKeySequence( tr( "Alt+D" ) ) );
	d->m_toolWindowObject = new ToolWindowObject( showAction, this, this );

	d->m_player = new QMediaPlayer( this );

	connect( d->m_player, &QMediaPlayer::playbackStateChanged,
		this, &Sounds::playerStateChanged );

	d->m_tabs = new QTabWidget( this );

	setCentralWidget( d->m_tabs );

	d->m_playedSoundsView = new PlayedSoundsView( this );

	d->m_tabs->addTab( d->m_playedSoundsView, tr( "Played Sounds" ) );

	d->m_disabledSoundsView = new DisabledSoundsView( this );

	d->m_tabs->addTab( d->m_disabledSoundsView, tr( "Disabled Sounds" ) );
}

} /* namespace Globe */

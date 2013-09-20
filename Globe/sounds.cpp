
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
#include <Globe/sounds.hpp>
#include <Globe/globe_menu.hpp>
#include <Globe/tool_window_object.hpp>
#include <Globe/sounds_disabled.hpp>
#include <Globe/sounds_cfg.hpp>
#include <Globe/log.hpp>
#include <Globe/utils.hpp>

// Qt include.
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QCloseEvent>
#include <QMessageBox>

// QtConfFile include.
#include <QtConfFile/Utils>


namespace Globe {

//
// SoundsPrivate
//

class SoundsPrivate {
public:
	SoundsPrivate()
		:	m_toolWindowObject( 0 )
		,	m_level( None )
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

Sounds &
Sounds::instance()
{
	static Sounds inst;

	return inst;
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

	try {
		QtConfFile::readQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
			"Sounds configuration read from file \"%1\"." )
				.arg( fileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to read sounds configuration from file \"%1\".\n"
			"%2" )
				.arg( fileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( 0,
			tr( "Unable to read sounds configuration..." ),
			x.whatAsQString() );

		return;
	}

	d->m_cfg = tag.cfg();
}

void
Sounds::saveCfg( const QString & fileName )
{
	try {
		SoundsCfgTag tag( d->m_cfg );

		QtConfFile::writeQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo, QString(
			"Sounds configuration saved to file \"%1\"." )
				.arg( fileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError, QString(
			"Unable to save sounds configuration to file \"%1\".\n"
			"%2" )
				.arg( fileName )
				.arg( x.whatAsQString() ) );

		QMessageBox::critical( 0,
			tr( "Unable to save sounds configuration..." ),
			x.whatAsQString() );
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
	checkDirAndCreateIfNotExists( QLatin1String( "./" ),
		QLatin1String( "sounds" ) );

	QAction * showAction = new QAction( tr( "S&ounds" ), this );
	d->m_toolWindowObject = new ToolWindowObject( showAction, this, this );

	d->m_player = new QMediaPlayer( this );

	connect( d->m_player, SIGNAL( stateChanged( QMediaPlayer::State ) ),
		this, SLOT( playerStateChanged( QMediaPlayer::State ) ) );
}

} /* namespace Globe */

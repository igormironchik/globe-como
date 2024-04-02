
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/sounds_cfg.hpp>


namespace Globe {

//
// SoundsCfg
//

SoundsCfg::SoundsCfg()
	:	m_isCriticalSoundEnabled( false )
	,	m_isErrorSoundEnabled( false )
	,	m_isWarningSoundEnabled( false )
	,	m_isDebugSoundEnabled( false )
	,	m_isInfoSoundEnabled( false )
{
}

SoundsCfg::SoundsCfg( const SoundsCfg & other )
	:	m_isCriticalSoundEnabled( other.isCriticalSoundEnabled() )
	,	m_criticalSoundFile( other.criticalSoundFile() )
	,	m_isErrorSoundEnabled( other.isErrorSoundEnabled() )
	,	m_errorSoundFile( other.errorSoundFile() )
	,	m_isWarningSoundEnabled( other.isWarningSoundEnabled() )
	,	m_warningSoundFile( other.warningSoundFile() )
	,	m_isDebugSoundEnabled( other.isDebugSoundEnabled() )
	,	m_debugSoundFile( other.debugSoundFile() )
	,	m_isInfoSoundEnabled( other.isInfoSoundEnabled() )
	,	m_infoSoundFile( other.infoSoundFile() )
	,	m_windowState( other.windowState() )
{
}

SoundsCfg &
SoundsCfg::operator = ( const SoundsCfg & other )
{
	if( this != &other )
	{
		m_isCriticalSoundEnabled = other.isCriticalSoundEnabled();
		m_criticalSoundFile = other.criticalSoundFile();
		m_isErrorSoundEnabled = other.isErrorSoundEnabled();
		m_errorSoundFile = other.errorSoundFile();
		m_isWarningSoundEnabled = other.isWarningSoundEnabled();
		m_warningSoundFile = other.warningSoundFile();
		m_isDebugSoundEnabled = other.isDebugSoundEnabled();
		m_debugSoundFile = other.debugSoundFile();
		m_isInfoSoundEnabled = other.isInfoSoundEnabled();
		m_infoSoundFile = other.infoSoundFile();
		m_windowState = other.windowState();
	}

	return *this;
}

bool
SoundsCfg::isCriticalSoundEnabled() const
{
	return m_isCriticalSoundEnabled;
}

void
SoundsCfg::setCriticalSoundEnabled( bool on )
{
	m_isCriticalSoundEnabled = on;

	if( !m_isCriticalSoundEnabled )
		m_criticalSoundFile.clear();
}

const QString &
SoundsCfg::criticalSoundFile() const
{
	return m_criticalSoundFile;
}

void
SoundsCfg::setCriticalSoundFile( const QString & fileName )
{
	if( !fileName.isEmpty() )
	{
		m_criticalSoundFile = fileName;

		setCriticalSoundEnabled( true );
	}
}

bool
SoundsCfg::isErrorSoundEnabled() const
{
	return m_isErrorSoundEnabled;
}

void
SoundsCfg::setErrorSoundEnabled( bool on )
{
	m_isErrorSoundEnabled = on;

	if( !m_isErrorSoundEnabled )
		m_errorSoundFile.clear();
}

const QString &
SoundsCfg::errorSoundFile() const
{
	return m_errorSoundFile;
}

void
SoundsCfg::setErrorSoundFile( const QString & fileName )
{
	if( !fileName.isEmpty() )
	{
		m_errorSoundFile = fileName;

		setErrorSoundEnabled( true );
	}
}

bool
SoundsCfg::isWarningSoundEnabled() const
{
	return m_isWarningSoundEnabled;
}

void
SoundsCfg::setWarningSoundEnabled( bool on )
{
	m_isWarningSoundEnabled = on;

	if( !m_isWarningSoundEnabled )
		m_warningSoundFile.clear();
}

const QString &
SoundsCfg::warningSoundFile() const
{
	return m_warningSoundFile;
}

void
SoundsCfg::setWarningSoundFile( const QString & fileName )
{
	if( !fileName.isEmpty() )
	{
		m_warningSoundFile = fileName;

		setWarningSoundEnabled( true );
	}
}

bool
SoundsCfg::isDebugSoundEnabled() const
{
	return m_isDebugSoundEnabled;
}

void
SoundsCfg::setDebugSoundEnabled( bool on )
{
	m_isDebugSoundEnabled = on;

	if( !m_isDebugSoundEnabled )
		m_debugSoundFile.clear();
}

const QString &
SoundsCfg::debugSoundFile() const
{
	return m_debugSoundFile;
}

void
SoundsCfg::setDebugSoundFile( const QString & fileName )
{
	if( !fileName.isEmpty() )
	{
		m_debugSoundFile = fileName;

		setDebugSoundEnabled( true );
	}
}

bool
SoundsCfg::isInfoSoundEnabled() const
{
	return m_isInfoSoundEnabled;
}

void
SoundsCfg::setInfoSoundEnabled( bool on )
{
	m_isInfoSoundEnabled = on;

	if( !m_isInfoSoundEnabled )
		m_infoSoundFile.clear();
}

const QString &
SoundsCfg::infoSoundFile() const
{
	return m_infoSoundFile;
}

void
SoundsCfg::setInfoSoundFile( const QString & fileName )
{
	if( !fileName.isEmpty() )
	{
		m_infoSoundFile = fileName;

		setInfoSoundEnabled( true );
	}
}

const WindowStateCfg &
SoundsCfg::windowState() const
{
	return m_windowState;
}

void
SoundsCfg::setWindowState( const WindowStateCfg & state )
{
	m_windowState = state;
}


//
// SoundsCfgTag
//

SoundsCfgTag::SoundsCfgTag()
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "soundsCfg" ), true )
	,	m_criticalSoundFile( *this, QLatin1String( "criticalSoundFile" ), false )
	,	m_errorSoundFile( *this, QLatin1String( "errorSoundFile" ), false )
	,	m_warningSoundFile( *this, QLatin1String( "warningSoundFile" ), false )
	,	m_debugSoundFile( *this, QLatin1String( "debugSoundFile" ), false )
	,	m_infoSoundFile( *this, QLatin1String( "infoSoundFile" ), false )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
{
}

SoundsCfgTag::SoundsCfgTag( const SoundsCfg & cfg )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "soundsCfg" ), true )
	,	m_criticalSoundFile( *this, QLatin1String( "criticalSoundFile" ), false )
	,	m_errorSoundFile( *this, QLatin1String( "errorSoundFile" ), false )
	,	m_warningSoundFile( *this, QLatin1String( "warningSoundFile" ), false )
	,	m_debugSoundFile( *this, QLatin1String( "debugSoundFile" ), false )
	,	m_infoSoundFile( *this, QLatin1String( "infoSoundFile" ), false )
	,	m_windowState( cfg.windowState(), *this,
			QLatin1String( "windowState" ), true )
{
	if( cfg.isCriticalSoundEnabled() && !cfg.criticalSoundFile().isEmpty() )
		m_criticalSoundFile.set_value( cfg.criticalSoundFile() );

	if( cfg.isErrorSoundEnabled() && !cfg.errorSoundFile().isEmpty() )
		m_errorSoundFile.set_value( cfg.errorSoundFile() );

	if( cfg.isWarningSoundEnabled() && !cfg.warningSoundFile().isEmpty() )
		m_warningSoundFile.set_value( cfg.warningSoundFile() );

	if( cfg.isDebugSoundEnabled() && !cfg.debugSoundFile().isEmpty() )
		m_debugSoundFile.set_value( cfg.debugSoundFile() );

	if( cfg.isInfoSoundEnabled() && !cfg.infoSoundFile().isEmpty() )
		m_infoSoundFile.set_value( cfg.infoSoundFile() );

	set_defined();
}

SoundsCfg
SoundsCfgTag::cfg() const
{
	SoundsCfg c;

	if( m_criticalSoundFile.is_defined() )
		c.setCriticalSoundFile( m_criticalSoundFile.value() );

	if( m_errorSoundFile.is_defined() )
		c.setErrorSoundFile( m_errorSoundFile.value() );

	if( m_warningSoundFile.is_defined() )
		c.setWarningSoundFile( m_warningSoundFile.value() );

	if( m_debugSoundFile.is_defined() )
		c.setDebugSoundFile( m_debugSoundFile.value() );

	if( m_infoSoundFile.is_defined() )
		c.setInfoSoundFile( m_infoSoundFile.value() );

	c.setWindowState( m_windowState.cfg() );

	return c;
}

} /* namespace Globe */

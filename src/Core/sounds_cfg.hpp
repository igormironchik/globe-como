
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SOUNDS_CFG_HPP__INCLUDED
#define GLOBE__SOUNDS_CFG_HPP__INCLUDED

// Qt include.
#include <QString>

// cfgfile include.
#include <cfgfile/all.hpp>

// Globe include.
#include <Core/window_state_cfg.hpp>


namespace Globe {

//
// SoundsCfg
//

//! Configuration of the sounds.
class SoundsCfg {
public:
	SoundsCfg();

	SoundsCfg( const SoundsCfg & other );

	SoundsCfg & operator = ( const SoundsCfg & other );

	//! \return Is critical sound enabled.
	bool isCriticalSoundEnabled() const;
	//! Enable/disable critical sound.
	void setCriticalSoundEnabled( bool on = true );
	//! \return Critical sound file.
	const QString & criticalSoundFile() const;
	//! Set critical sound file.
	void setCriticalSoundFile( const QString & fileName );

	//! \return Is error sound enabled.
	bool isErrorSoundEnabled() const;
	//! Enable/disable error sound.
	void setErrorSoundEnabled( bool on = true );
	//! \return Error sound file.
	const QString & errorSoundFile() const;
	//! Set error sound file.
	void setErrorSoundFile( const QString & fileName );

	//! \return Is warning sound enabled.
	bool isWarningSoundEnabled() const;
	//! Enable/disable warning sound.
	void setWarningSoundEnabled( bool on = true );
	//! \return Warning sound file.
	const QString & warningSoundFile() const;
	//! Set warning sound file.
	void setWarningSoundFile( const QString & fileName );

	//! \return Is debug sound enabled.
	bool isDebugSoundEnabled() const;
	//! Enable/disable debug sound.
	void setDebugSoundEnabled( bool on = true );
	//! \return Debug sound file.
	const QString & debugSoundFile() const;
	//! Set debug sound file.
	void setDebugSoundFile( const QString & fileName );

	//! \return Is info sound enabled.
	bool isInfoSoundEnabled() const;
	//! Enable/disable info sound.
	void setInfoSoundEnabled( bool on = true );
	//! \return Info sound file.
	const QString & infoSoundFile() const;
	//! Set info sound file.
	void setInfoSoundFile( const QString & fileName );

	//! \return Window state configuration.
	const WindowStateCfg & windowState() const;
	//! Set window state configuration.
	void setWindowState( const WindowStateCfg & state );

private:
	//! Is critical sound enabled?
	bool m_isCriticalSoundEnabled;
	//! Critical sound file.
	QString m_criticalSoundFile;
	//! Is error sound enabled?
	bool m_isErrorSoundEnabled;
	//! Error sound file.
	QString m_errorSoundFile;
	//! Is warning sound enabled?
	bool m_isWarningSoundEnabled;
	//! Warning sound file.
	QString m_warningSoundFile;
	//! Is debug sound enabled?
	bool m_isDebugSoundEnabled;
	//! Debug sound file.
	QString m_debugSoundFile;
	//! Is info sound enabled?
	bool m_isInfoSoundEnabled;
	//! Info sound file.
	QString m_infoSoundFile;
	//! Window state configuration.
	WindowStateCfg m_windowState;
}; // class SoundsCfg


//
// SoundsCfgTag
//

//! Tag with sounds configuration.
class SoundsCfgTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	SoundsCfgTag();

	explicit SoundsCfgTag( const SoundsCfg & cfg );

	//! \return Configuration.
	SoundsCfg cfg() const;

private:
	//! Critical sound file.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_criticalSoundFile;
	//! Error sound file.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_errorSoundFile;
	//! Warning sound file.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_warningSoundFile;
	//! Debug sound file.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_debugSoundFile;
	//! Info sound file.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_infoSoundFile;
	//! Window state configuration.
	WindowStateCfgTag m_windowState;
}; // class SoundsCfgTag


} /* namespace Globe */

#endif // GLOBE__SOUNDS_CFG_HPP__INCLUDED

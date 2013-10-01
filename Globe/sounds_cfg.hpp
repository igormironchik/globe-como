
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

#ifndef GLOBE__SOUNDS_CFG_HPP__INCLUDED
#define GLOBE__SOUNDS_CFG_HPP__INCLUDED

// Qt include.
#include <QString>

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>

// Globe include.
#include <Globe/window_state_cfg.hpp>


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
	:	public QtConfFile::TagNoValue
{
public:
	SoundsCfgTag();

	explicit SoundsCfgTag( const SoundsCfg & cfg );

	//! \return Configuration.
	SoundsCfg cfg() const;

private:
	//! Critical sound file.
	QtConfFile::TagScalar< QString > m_criticalSoundFile;
	//! Error sound file.
	QtConfFile::TagScalar< QString > m_errorSoundFile;
	//! Warning sound file.
	QtConfFile::TagScalar< QString > m_warningSoundFile;
	//! Debug sound file.
	QtConfFile::TagScalar< QString > m_debugSoundFile;
	//! Info sound file.
	QtConfFile::TagScalar< QString > m_infoSoundFile;
	//! Window state configuration.
	WindowStateCfgTag m_windowState;
}; // class SoundsCfgTag


} /* namespace Globe */

#endif // GLOBE__SOUNDS_CFG_HPP__INCLUDED

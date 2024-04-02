
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SOUNDS_DISABLED_HPP__INCLUDED
#define GLOBE__SOUNDS_DISABLED_HPP__INCLUDED

// Qt include.
#include <QObject>
#include <QScopedPointer>

// Como include.
#include <Como/Source>

QT_BEGIN_NAMESPACE
class QDateTime;
QT_END_NAMESPACE


namespace Globe {

//
// DisabledSounds
//

class DisabledSoundsPrivate;

//! Disabled sounds manager.
class DisabledSounds
	:	public QObject
{
	Q_OBJECT

signals:
	//! Sounds disabled.
	void soundsDisabled( const Como::Source & source,
		const QString & channelName,
		const QDateTime & to );

	//! Sounds enabled.
	void soundsEnabled( const Como::Source & source,
		const QString & channelName );

private:
	DisabledSounds( QObject * parent = 0 );

	~DisabledSounds();

	static void cleanup();

public:
	//! \return Instance.
	static DisabledSounds & instance();

	//! \return Is sounds enabled for the given source.
	bool isSoundsEnabled( const Como::Source & source,
		const QString & channelName );

	//! Disable sound for the give source.
	void disableSounds( const Como::Source & source,
		const QString & channelName,
		const QDateTime & to );

	//! Enable sounds for the given source.
	void enableSounds( const Como::Source & source,
		const QString & channelName );

	//! Read configuration.
	void readCfg( const QString & fileName );

	//! Save configuration.
	void saveCfg( const QString & fileName );

private slots:
	//! Check if there are sounds that should be enabled.
	void checkAndEnableIf();
	//! Init timer.
	void initTimer();

private:
	//! Init.
	void init();
	//! Notify about all disabled sounds.
	void notifyAboutDisabledSounds();

private:
	Q_DISABLE_COPY( DisabledSounds )

	QScopedPointer< DisabledSoundsPrivate > d;
}; // class DisabledSounds

} /* namespace Globe */

#endif // GLOBE__SOUNDS_DISABLED_HPP__INCLUDED

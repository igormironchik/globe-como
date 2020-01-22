
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

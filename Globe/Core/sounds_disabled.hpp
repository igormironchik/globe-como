
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

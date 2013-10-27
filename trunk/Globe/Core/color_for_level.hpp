
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

#ifndef GLOBE__COLOR_FOR_LEVEL_HPP__INCLUDED
#define GLOBE__COLOR_FOR_LEVEL_HPP__INCLUDED

// Globe include.
#include <Globe/Core/condition.hpp>

// Qt include.
#include <QObject>
#include <QColor>
#include <QScopedPointer>


namespace Globe {

class MainWindow;


static const QColor defaultNoneColor = Qt::white;
static const QColor defaultCriticalColor = Qt::red;
static const QColor defaultErrorColor = Qt::magenta;
static const QColor defaultWarningColor = Qt::yellow;
static const QColor defaultDebugColor = Qt::cyan;
static const QColor defaultInfoColor = Qt::green;
static const QColor defaultDeregisteredColor = Qt::lightGray;
static const QColor defaultDisconnectedColor = Qt::lightGray;


//
// ColorForLevel
//

class ColorForLevelPrivate;

//! Correspondence between level and color.
class ColorForLevel
	:	public QObject
{
	Q_OBJECT

signals:
	//! Changed.
	void changed();

private:
	ColorForLevel( QObject * parent = 0 );

	~ColorForLevel();

public:
	//! \return Instance.
	static ColorForLevel & instance();

	//! \return Color for the given \arg level level.
	const QColor & color( Level level ) const;

	//! \return Color for deregistered sources.
	const QColor & deregisteredColor() const;

	//! \return Color for disconnected sources.
	const QColor & disconnectedColor() const;

	//! Set colors.
	void setColors( const QColor & none,
		const QColor & critical,
		const QColor & error,
		const QColor & warning,
		const QColor & debug,
		const QColor & info,
		const QColor & deregistered,
		const QColor & disconnected );

	//! Save configuration.
	void saveCfg( const QString & fileName );
	//! Read configuration.
	void readCfg( const QString & fileName );

private:
	Q_DISABLE_COPY( ColorForLevel )

	QScopedPointer< ColorForLevelPrivate > d;
}; // class ColorForLevel

} /* namespace Globe */

#endif // GLOBE__COLOR_FOR_LEVEL_HPP__INCLUDED

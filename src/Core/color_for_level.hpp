
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__COLOR_FOR_LEVEL_HPP__INCLUDED
#define GLOBE__COLOR_FOR_LEVEL_HPP__INCLUDED

// Globe include.
#include <Core/condition.hpp>

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

	static void cleanup();

public:
	//! \return Instance.
	static ColorForLevel & instance();

	//! \return Color for the given level.
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

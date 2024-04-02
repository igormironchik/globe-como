
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Scheme/mm_pixels.hpp>

// Qt include.
#include <QPaintDevice>
#include <QApplication>
#include <QScreen>


namespace Globe {

namespace Scheme {

static const qreal inchInMm = 0.0393700787;


//
// pointToMm
//

QPointF pointToMm( const QPointF & p )
{
	const qreal dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
	const qreal dpiY = QApplication::primaryScreen()->physicalDotsPerInchY();

	const qreal x = p.x() / dpiX / inchInMm;
	const qreal y = p.y() / dpiY / inchInMm;

	return QPointF( x, y );
}


//
// pointFromMm
//

QPointF pointFromMm( const QPointF & p )
{
	const qreal dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
	const qreal dpiY = QApplication::primaryScreen()->physicalDotsPerInchY();

	const qreal x = p.x() * dpiX * inchInMm;
	const qreal y = p.y() * dpiY * inchInMm;

	return QPointF( qRound64( x ), qRound64( y ) );
}


//
// sizeToMm
//

QSizeF sizeToMm( const QSizeF & s )
{
	const qreal dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
	const qreal dpiY = QApplication::primaryScreen()->physicalDotsPerInchY();

	const qreal width = s.width() / dpiX / inchInMm;
	const qreal height = s.height() / dpiY / inchInMm;

	return QSizeF( width, height );
}


//
// sizeFromMm
//

QSizeF sizeFromMm( const QSizeF & s )
{
	const qreal dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
	const qreal dpiY = QApplication::primaryScreen()->physicalDotsPerInchY();

	const qreal width = s.width() * dpiX * inchInMm;
	const qreal height = s.height() * dpiY * inchInMm;

	return QSizeF( qRound64( width ), qRound64( height ) );
}

} /* namespace Scheme */

} /* namespace Globe */

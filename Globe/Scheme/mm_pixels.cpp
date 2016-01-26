
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

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

// Globe include.
#include <Globe/Scheme/mm_pixels.hpp>

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

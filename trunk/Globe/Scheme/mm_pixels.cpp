
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

// Globe include.
#include <Globe/Scheme/mm_pixels.hpp>

// Qt include.
#include <QPaintDevice>
#include <QApplication>
#include <QDesktopWidget>


namespace Globe {

namespace Scheme {

static const qreal inchInMm = 0.0393700787;


//
// pointToMm
//

QPointF pointToMm( const QPointF & p )
{
	const qreal dpiX = QApplication::desktop()->physicalDpiX();
	const qreal dpiY = QApplication::desktop()->physicalDpiY();

	const qreal x = p.x() / dpiX / inchInMm;
	const qreal y = p.y() / dpiY / inchInMm;

	return QPointF( x, y );
}


//
// pointFromMm
//

QPointF pointFromMm( const QPointF & p )
{
	const qreal dpiX = QApplication::desktop()->physicalDpiX();
	const qreal dpiY = QApplication::desktop()->physicalDpiY();

	const qreal x = p.x() * dpiX * inchInMm;
	const qreal y = p.y() * dpiY * inchInMm;

	return QPointF( qRound64( x ), qRound64( y ) );
}


//
// sizeToMm
//

QSizeF sizeToMm( const QSizeF & s )
{
	const qreal dpiX = QApplication::desktop()->physicalDpiX();
	const qreal dpiY = QApplication::desktop()->physicalDpiY();

	const qreal width = s.width() / dpiX / inchInMm;
	const qreal height = s.height() / dpiY / inchInMm;

	return QSizeF( width, height );
}


//
// sizeFromMm
//

QSizeF sizeFromMm( const QSizeF & s )
{
	const qreal dpiX = QApplication::desktop()->physicalDpiX();
	const qreal dpiY = QApplication::desktop()->physicalDpiY();

	const qreal width = s.width() * dpiX * inchInMm;
	const qreal height = s.height() * dpiY * inchInMm;

	return QSizeF( qRound64( width ), qRound64( height ) );
}

} /* namespace Scheme */

} /* namespace Globe */

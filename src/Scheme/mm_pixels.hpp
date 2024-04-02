
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SCHEME__MM_PIXELS_HPP__INCLUDED
#define GLOBE__SCHEME__MM_PIXELS_HPP__INCLUDED

// Qt include.
#include <QPointF>
#include <QSizeF>


namespace Globe {

namespace Scheme {

//
// pointToMm
//

//! Convert pixels to mm.
QPointF pointToMm( const QPointF & p );


//
// pointFromMm
//

//! Convert mm to pixels.
QPointF pointFromMm( const QPointF & p );


//
// sizeToMm
//

//! Convert pixels to mm.
QSizeF sizeToMm( const QSizeF & s );


//
// sizeFromMm
//

//! Convert mm to pixels.
QSizeF sizeFromMm( const QSizeF & s );

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__MM_PIXELS_HPP__INCLUDED

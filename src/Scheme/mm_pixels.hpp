
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

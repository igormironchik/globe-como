
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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

#ifndef GLOBE__SCHEME__SELECTABLE_HPP__INCLUDED
#define GLOBE__SCHEME__SELECTABLE_HPP__INCLUDED

// Globe include.
#include <Globe/Scheme/enums.hpp>


namespace Globe {

namespace Scheme {

//
// Selectable
//

//! Interface for selectable item on the scheme.
class Selectable {
public:
	virtual ~Selectable()
	{
	}

	//! Set item state.
	virtual void setItemState( ItemState st ) = 0;

	//! Move up.
	virtual void moveUp( int delta ) = 0;

	//! Move down.
	virtual void moveDown( int delta ) = 0;

	//! Move left.
	virtual void moveLeft( int delta ) = 0;

	//! Move right.
	virtual void moveRight( int delta ) = 0;

	//! Delete item.
	virtual void deleteItem() = 0;
}; // class Selectable

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__SELECTABLE_HPP__INCLUDED

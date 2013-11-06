
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
	virtual void moveUp() = 0;

	//! Move down.
	virtual void moveDown() = 0;

	//! Move left.
	virtual void moveLeft() = 0;

	//! Move right.
	virtual void moveRight() = 0;
}; // class Selectable

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__SELECTABLE_HPP__INCLUDED

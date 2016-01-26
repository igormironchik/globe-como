
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

#ifndef GLOBE__SCHEME__SELECTION_HPP__INCLUDED
#define GLOBE__SCHEME__SELECTION_HPP__INCLUDED

// Qt include.
#include <QScopedPointer>

// Globe include.
#include <Globe/Scheme/selectable.hpp>


namespace Globe {

namespace Scheme {

//
// Selection
//

class SelectionPrivate;

//! Selection on the scheme.
class Selection {
public:
	Selection();

	~Selection();

	//! Add item to the selection.
	void addItem( Selectable * item );

	//! Remove item.
	void removeItem( Selectable * item );

	//! Clear selection.
	void clear();

	//! \return Is selection empty?
	bool isEmpty() const;

	//! Move selection up.
	void moveUp( int delta );

	//! Move selection down.
	void moveDown( int delta );

	//! Move selection left.
	void moveLeft( int delta );

	//! Move selection right.
	void moveRight( int delta );

	//! Delete selected items.
	void deleteItems();

private:
	Q_DISABLE_COPY( Selection )

	QScopedPointer< SelectionPrivate > d;
}; // class Selection

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__SELECTION_HPP__INCLUDED

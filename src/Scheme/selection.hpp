
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SCHEME__SELECTION_HPP__INCLUDED
#define GLOBE__SCHEME__SELECTION_HPP__INCLUDED

// Qt include.
#include <QScopedPointer>

// Globe include.
#include <Scheme/selectable.hpp>


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

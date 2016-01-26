
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
#include <Globe/Scheme/selection.hpp>

// Qt include.
#include <QList>


namespace Globe {

namespace Scheme {

//
// SelectionPrivate
//

class SelectionPrivate {
public:
	SelectionPrivate()
	{
	}

	//! Items.
	QList< Selectable* > m_items;
}; // class SelectionPrivate;


//
// Selection
//

Selection::Selection()
	:	d( new SelectionPrivate )
{
}

Selection::~Selection()
{
}

void
Selection::addItem( Selectable * item )
{
	if( !d->m_items.contains( item ) )
	{
		item->setItemState( ItemSelected );
		d->m_items.append( item );
	}
}

void
Selection::removeItem( Selectable * item )
{
	d->m_items.removeOne( item );
}

void
Selection::clear()
{
	foreach( Selectable * item, d->m_items )
		item->setItemState( ItemNotSelected );

	d->m_items.clear();
}

bool
Selection::isEmpty() const
{
	return d->m_items.isEmpty();
}

void
Selection::moveUp( int delta )
{
	foreach( Selectable * item, d->m_items )
		item->moveUp( delta );
}

void
Selection::moveDown( int delta )
{
	foreach( Selectable * item, d->m_items )
		item->moveDown( delta );
}

void
Selection::moveLeft( int delta )
{
	foreach( Selectable * item, d->m_items )
		item->moveLeft( delta );
}

void
Selection::moveRight( int delta )
{
	foreach( Selectable * item, d->m_items )
		item->moveRight( delta );
}

void
Selection::deleteItems()
{
	QList< Selectable* > items = d->m_items;

	foreach( Selectable * item, items )
		item->deleteItem();
}

} /* namespace Scheme */

} /* namespace Globe */

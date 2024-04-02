
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Scheme/selection.hpp>

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


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
Selection::moveUp()
{
	foreach( Selectable * item, d->m_items )
		item->moveUp();
}

void
Selection::moveDown()
{
	foreach( Selectable * item, d->m_items )
		item->moveDown();
}

void
Selection::moveLeft()
{
	foreach( Selectable * item, d->m_items )
		item->moveLeft();
}

void
Selection::moveRight()
{
	foreach( Selectable * item, d->m_items )
		item->moveRight();
}

} /* namespace Scheme */

} /* namespace Globe */

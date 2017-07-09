
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

// Globe include.
#include <Globe/Scheme/aggregate.hpp>


namespace Globe {

namespace Scheme {

//
// AggregatePrivate
//

class AggregatePrivate
	:	public SelectablePrivate
{
public:
	AggregatePrivate( Selection * selection, Scene * scene )
		:	SelectablePrivate( selection, scene )
	{
	}

	~AggregatePrivate()
	{
	}
}; // class AggregatePrivate;


//
// Aggregate
//

Aggregate::Aggregate( Selection * selection, Scene * scene )
	:	BaseItem( new AggregatePrivate( selection, scene ) )
{

}

Aggregate::~Aggregate()
{
}

void
Aggregate::deleteItem()
{
//	d_ptr()->m_scene->removeSource( this );

//	deleteLater();
}

SchemeCfg
Aggregate::cfg() const
{
	SchemeCfg cfg;

	return cfg;
}

void
Aggregate::setCfg( const SchemeCfg & cfg )
{

}

void
Aggregate::paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
	QWidget * widget )
{

}

void
Aggregate::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{

}

AggregatePrivate *
Aggregate::d_ptr()
{
	return static_cast< AggregatePrivate* > ( d.data() );
}

const AggregatePrivate *
Aggregate::d_ptr() const
{
	return static_cast< const AggregatePrivate* > ( d.data() );
}

} /* namespace Scheme */

} /* namespace Globe */

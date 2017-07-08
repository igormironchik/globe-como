
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
	:	Selectable( new AggregatePrivate( selection, scene ) )
{

}

Aggregate::~Aggregate()
{
}

void
Aggregate::setMode( SceneMode mode )
{

}

void
Aggregate::setEditMode( EditSceneMode mode )
{

}

void
Aggregate::setItemState( ItemState st )
{

}

void
Aggregate::moveUp( int delta )
{

}

void
Aggregate::moveDown( int delta )
{

}

void
Aggregate::moveLeft( int delta )
{

}

void
Aggregate::moveRight( int delta )
{

}

void
Aggregate::deleteItem()
{

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

QRectF
Aggregate::boundingRect() const
{
	return QRectF();
}

void
Aggregate::paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
	QWidget * widget )
{

}

void
Aggregate::mouseMoveEvent( QGraphicsSceneMouseEvent * event )
{

}

void
Aggregate::mousePressEvent( QGraphicsSceneMouseEvent * event )
{

}

void
Aggregate::mouseReleaseEvent( QGraphicsSceneMouseEvent * event )
{

}

void
Aggregate::hoverEnterEvent( QGraphicsSceneHoverEvent * event )
{

}

void
Aggregate::hoverLeaveEvent( QGraphicsSceneHoverEvent * event )
{

}

void
Aggregate::hoverMoveEvent( QGraphicsSceneHoverEvent * event )
{

}

void
Aggregate::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{

}

void
Aggregate::detectResizeMode( const QPointF & pos )
{

}

} /* namespace Scheme */

} /* namespace Globe */

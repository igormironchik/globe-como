
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

#ifndef GLOBE__SCHEME__TEXT_HPP__INCLUDED
#define GLOBE__SCHEME__TEXT_HPP__INCLUDED

// Qt include.
#include <QGraphicsObject>
#include <QScopedPointer>

// Globe include.
#include <Globe/Scheme/enums.hpp>
#include <Globe/Scheme/selectable.hpp>
#include <Globe/Scheme/text_cfg.hpp>


namespace Globe {

namespace Scheme {

class Selection;
class Scene;


//
// Text
//

class TextPrivate;

//! Graphics item that will display text on scheme.
class Text
	:	public QGraphicsObject
	,	public Selectable
{
	Q_OBJECT

public:
	Text( const QString & text,
		Selection * selection, Scene * scene );
	~Text();

	//! Set scene mode.
	void setMode( SceneMode mode );

	//! Set edit scene mode.
	void setEditMode( EditSceneMode mode );

	//! Set item state.
	void setItemState( ItemState st );

	//! Move up.
	void moveUp( int delta );

	//! Move down.
	void moveDown( int delta );

	//! Move left.
	void moveLeft( int delta );

	//! Move right.
	void moveRight( int delta );

	//! Delete item.
	void deleteItem();

	//! \return Configuration.
	TextCfg cfg() const;
	//! Set configuration.
	void setCfg( const TextCfg & cfg );

	//! \return Bounding rectangle.
	QRectF boundingRect() const;

	//! Paint item.
	void paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
		QWidget * widget );

protected:
	void mouseMoveEvent( QGraphicsSceneMouseEvent * event );
	void mousePressEvent( QGraphicsSceneMouseEvent * event );
	void mouseReleaseEvent( QGraphicsSceneMouseEvent * event );
	void hoverEnterEvent( QGraphicsSceneHoverEvent * event );
	void hoverLeaveEvent( QGraphicsSceneHoverEvent * event );
	void hoverMoveEvent( QGraphicsSceneHoverEvent * event );
	void contextMenuEvent( QGraphicsSceneContextMenuEvent * event );

private:
	//! Detect resize mode and change cursor.
	void detectResizeMode( const QPointF & pos );

private slots:
	//! Remove this item from scene.
	void removeItemFromScene();
	//! Change font.
	void changeFont();
	//! Change size.
	void changeSize();
	//! Change text.
	void changeText();

private:
	Q_DISABLE_COPY( Text )

	QScopedPointer< TextPrivate > d;
}; // class Text

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__TEXT_HPP__INCLUDED

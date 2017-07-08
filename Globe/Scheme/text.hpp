
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
	void setMode( SceneMode mode ) Q_DECL_OVERRIDE;

	//! Set edit scene mode.
	void setEditMode( EditSceneMode mode ) Q_DECL_OVERRIDE;

	//! Set item state.
	void setItemState( ItemState st ) Q_DECL_OVERRIDE;

	//! Move up.
	void moveUp( int delta ) Q_DECL_OVERRIDE;

	//! Move down.
	void moveDown( int delta ) Q_DECL_OVERRIDE;

	//! Move left.
	void moveLeft( int delta ) Q_DECL_OVERRIDE;

	//! Move right.
	void moveRight( int delta ) Q_DECL_OVERRIDE;

	//! Delete item.
	void deleteItem() Q_DECL_OVERRIDE;

	//! \return Configuration.
	TextCfg cfg() const;
	//! Set configuration.
	void setCfg( const TextCfg & cfg );

	//! \return Bounding rectangle.
	QRectF boundingRect() const Q_DECL_OVERRIDE;

	//! Paint item.
	void paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
		QWidget * widget ) Q_DECL_OVERRIDE;

protected:
	void mouseMoveEvent( QGraphicsSceneMouseEvent * event ) Q_DECL_OVERRIDE;
	void mousePressEvent( QGraphicsSceneMouseEvent * event ) Q_DECL_OVERRIDE;
	void mouseReleaseEvent( QGraphicsSceneMouseEvent * event ) Q_DECL_OVERRIDE;
	void hoverEnterEvent( QGraphicsSceneHoverEvent * event ) Q_DECL_OVERRIDE;
	void hoverLeaveEvent( QGraphicsSceneHoverEvent * event ) Q_DECL_OVERRIDE;
	void hoverMoveEvent( QGraphicsSceneHoverEvent * event ) Q_DECL_OVERRIDE;
	void contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
		Q_DECL_OVERRIDE;

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
	TextPrivate * d_ptr();
	const TextPrivate * d_ptr() const;

private:
	Q_DISABLE_COPY( Text )
}; // class Text

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__TEXT_HPP__INCLUDED

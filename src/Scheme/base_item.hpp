
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SCHEME__BASE_ITEM_HPP__INCLUDED
#define GLOBE__SCHEME__BASE_ITEM_HPP__INCLUDED

// Qt include.
#include <QGraphicsObject>
#include <QScopedPointer>

// Globe include.
#include <Scheme/enums.hpp>
#include <Scheme/selectable.hpp>
#include <Scheme/scheme_cfg.hpp>


namespace Globe {

namespace Scheme {

class Selection;
class Scene;


//
// BaseItem
//

//! Base class for graphic item on the scheme.
class BaseItem
	:	public QGraphicsObject
	,	public Selectable
{
	Q_OBJECT

protected:
	BaseItem( SelectablePrivate * dd );

public:
	~BaseItem();

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

	//! \return Bounding rectangle.
	QRectF boundingRect() const Q_DECL_OVERRIDE;

protected:
	void mouseMoveEvent( QGraphicsSceneMouseEvent * event ) Q_DECL_OVERRIDE;
	void mousePressEvent( QGraphicsSceneMouseEvent * event ) Q_DECL_OVERRIDE;
	void mouseReleaseEvent( QGraphicsSceneMouseEvent * event ) Q_DECL_OVERRIDE;
	void hoverEnterEvent( QGraphicsSceneHoverEvent * event ) Q_DECL_OVERRIDE;
	void hoverLeaveEvent( QGraphicsSceneHoverEvent * event ) Q_DECL_OVERRIDE;
	void hoverMoveEvent( QGraphicsSceneHoverEvent * event ) Q_DECL_OVERRIDE;

private slots:
	//! Remove this item from scene.
	void removeItemFromScene();
	//! Change font.
	void changeFont();
	//! Change size.
	void changeSize();

private:
	//! Detect resize mode and change cursor.
	void detectResizeMode( const QPointF & pos );

private:
	Q_DISABLE_COPY( BaseItem )
}; // class BaseItem

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__BASE_ITEM_HPP__INCLUDED

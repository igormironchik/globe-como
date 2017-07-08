
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

#ifndef GLOBE__SCHEME__SELECTABLE_HPP__INCLUDED
#define GLOBE__SCHEME__SELECTABLE_HPP__INCLUDED

// Qt include.
#include <QScopedPointer>

// Globe include.
#include <Globe/Scheme/enums.hpp>


QT_BEGIN_NAMESPACE

class QPointF;
class QRectF;

QT_END_NAMESPACE


namespace Globe {

namespace Scheme {

class Selection;
class Scene;


//
// SelectablePrivate
//

class SelectablePrivate {
public:
	SelectablePrivate( Selection * selection, Scene * scene );

	virtual ~SelectablePrivate();

	//! Resize mode.
	ResizeMode m_resizeMode;
	//! Mode of the scene.
	SceneMode m_mode;
	//! Edit mode of the scene.
	EditSceneMode m_editMode;
	//! Selection.
	Selection * m_selection;
	//! Scene.
	Scene * m_scene;
	//! Item state.
	ItemState m_state;
	//! Left mouse button was pressed.
	bool m_leftButtonPressed;
	//! Width.
	qreal m_width;
	//! Height.
	qreal m_height;
}; // class SelectablePrivate;


//
// Selectable
//

//! Interface for selectable item on the scheme.
class Selectable {
public:
	virtual ~Selectable();

	//! Set scene mode.
	virtual void setMode( SceneMode mode ) = 0 ;

	//! Set edit scene mode.
	virtual void setEditMode( EditSceneMode mode ) = 0;

	//! Set item state.
	virtual void setItemState( ItemState st ) = 0;

	//! Move up.
	virtual void moveUp( int delta ) = 0;

	//! Move down.
	virtual void moveDown( int delta ) = 0;

	//! Move left.
	virtual void moveLeft( int delta ) = 0;

	//! Move right.
	virtual void moveRight( int delta ) = 0;

	//! Delete item.
	virtual void deleteItem() = 0;

protected:
	Selectable( SelectablePrivate * dd );

	//! Detect resize mode and change cursor.
	void detectResizeMode( const QPointF & pos, const QRectF & boundingRect );

	QScopedPointer< SelectablePrivate > d;

private:
	Q_DISABLE_COPY( Selectable )
}; // class Selectable

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__SELECTABLE_HPP__INCLUDED

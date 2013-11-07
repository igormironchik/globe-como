
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

#ifndef GLOBE__SCHEME__SOURCE_HPP__INCLUDED
#define GLOBE__SCHEME__SOURCE_HPP__INCLUDED

// Qt include.
#include <QGraphicsObject>
#include <QScopedPointer>

// Como include.
#include <Como/Source>

// Globe include.
#include <Globe/Scheme/enums.hpp>
#include <Globe/Scheme/selectable.hpp>


namespace Globe {

namespace Scheme {

class Selection;
class Scene;


//
// Source
//

class SourcePrivate;

//! Graphics item that will display Como source on scheme.
class Source
	:	public QGraphicsObject
	,	public Selectable
{
	Q_OBJECT

public:
	Source( const Como::Source & source, const QString & channelName,
		Selection * selection, Scene * scene );

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

	//! \return Channel name.
	const QString & channelName() const;

	//! \return Source.
	const Como::Source & source() const;
	//! Set source.
	void setSource( const Como::Source & source );

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

private:
	Q_DISABLE_COPY( Source )

	QScopedPointer< SourcePrivate > d;
}; // class Source

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__SOURCE_HPP__INCLUDED


/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2020 Igor Mironchik

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
#include <Scheme/base_item.hpp>
#include <Scheme/size_dialog.hpp>
#include <Scheme/selection.hpp>

// Qt include.
#include <QFontDialog>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>
#include <QApplication>
#include <QCursor>


namespace Globe {

namespace Scheme {

//
// BaseItem
//

BaseItem::BaseItem( SelectablePrivate * dd )
	:	Selectable( dd )
{

}

BaseItem::~BaseItem()
{
}

void
BaseItem::setMode( SceneMode mode )
{
	d->m_mode = mode;

	if( d->m_mode == EditScene )
		setFlags( QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable |
			QGraphicsItem::ItemIsFocusable );
	else
	{
		setFlags( GraphicsItemFlags() );
		setItemState( ItemNotSelected );
	}
}

void
BaseItem::setEditMode( EditSceneMode mode )
{
	d->m_editMode = mode;
}

void
BaseItem::setItemState( ItemState st )
{
	d->m_state = st;

	if( st == ItemSelected )
		setAcceptHoverEvents( true );
	else
		setAcceptHoverEvents( false );

	update();
}

void
BaseItem::moveUp( int delta )
{
	setPos( pos().x(), pos().y() - delta );
}

void
BaseItem::moveDown( int delta )
{
	setPos( pos().x(), pos().y() + delta );
}

void
BaseItem::moveLeft( int delta )
{
	setPos( pos().x() - delta, pos().y() );
}

void
BaseItem::moveRight( int delta )
{
	setPos( pos().x() + delta, pos().y() );
}

QRectF
BaseItem::boundingRect() const
{
	return QRectF( 0, 0, d->m_width, d->m_height );
}

void
BaseItem::mouseMoveEvent( QGraphicsSceneMouseEvent * event )
{
	if( d->m_leftButtonPressed && d->m_editMode == EditSceneSelect &&
		( d->m_resizeMode & YesResize ) )
	{
		qreal x = pos().x();
		qreal y = pos().y();
		qreal width = boundingRect().width();
		qreal height = boundingRect().height();

		switch( d->m_resizeMode )
		{
			case ResizeTopLeft :
				{
					const qreal dx = event->pos().x();
					const qreal dy = event->pos().y();
					width -= dx;
					height -= dy;
					x += dx;
					y += dy;
				}
			break;

			case ResizeTopRight :
				{
					const qreal dx = event->pos().x() - boundingRect().width();
					const qreal dy = event->pos().y();
					width += dx;
					height -= dy;
					y += dy;
				}
			break;

			case ResizeBottomRight :
				{
					const qreal dx = event->pos().x() - boundingRect().width();
					const qreal dy = event->pos().y() - boundingRect().height();
					width += dx;
					height += dy;
				}

			break;

			case ResizeBottomLeft :
				{
					const qreal dx = event->pos().x();
					const qreal dy = event->pos().y() - boundingRect().height();
					width -= dx;
					height += dy;
					x += dx;
				}
			break;

			default:
				break;
		}

		if( qAbs( x - pos().x() ) > 0.001 || qAbs( y - pos().y() ) > 0.001 )
			setPos( x, y );

		if( width != d->m_width || height != d->m_height )
		{
			d->m_width = width;
			d->m_height = height;
			update();
		}
	}
	else
		QGraphicsObject::mouseMoveEvent( event );
}

void
BaseItem::mousePressEvent( QGraphicsSceneMouseEvent * event )
{
	if( d->m_mode == EditScene )
	{
		if( d->m_editMode == EditSceneSelect &&
			event->button() == Qt::LeftButton )
				d->m_leftButtonPressed = true;
	}

	QGraphicsObject::mousePressEvent( event );
}

void
BaseItem::mouseReleaseEvent( QGraphicsSceneMouseEvent * event )
{
	if( d->m_mode == EditScene )
	{
		if( d->m_editMode == EditSceneSelect &&
			event->button() == Qt::LeftButton )
		{
			d->m_leftButtonPressed = false;

			if( event->modifiers() == Qt::NoModifier )
				d->m_selection->clear();

			d->m_selection->addItem( this );

			event->accept();
		}
		else
			QGraphicsObject::mouseReleaseEvent( event );
	}
	else
		QGraphicsObject::mouseReleaseEvent( event );
}

void
BaseItem::hoverEnterEvent( QGraphicsSceneHoverEvent * event )
{
	if( d->m_mode == EditScene && d->m_editMode == EditSceneSelect &&
		d->m_state == ItemSelected )
			detectResizeMode( event->pos() );
	else
		QGraphicsObject::hoverEnterEvent( event );
}

void
BaseItem::hoverLeaveEvent( QGraphicsSceneHoverEvent * event )
{
	if( d->m_mode == EditScene && d->m_editMode == EditSceneSelect &&
		d->m_state == ItemSelected )
	{
		d->m_resizeMode = NoResize;
		QApplication::setOverrideCursor( QCursor( Qt::ArrowCursor ) );
	}
	else
		QGraphicsObject::hoverLeaveEvent( event );
}

void
BaseItem::hoverMoveEvent( QGraphicsSceneHoverEvent * event )
{
	if( d->m_mode == EditScene && d->m_editMode == EditSceneSelect &&
		d->m_state == ItemSelected )
			detectResizeMode( event->pos() );
	else
		QGraphicsObject::hoverMoveEvent( event );
}

void
BaseItem::detectResizeMode( const QPointF & pos )
{
	Selectable::detectResizeMode( pos, boundingRect() );
}

void
BaseItem::removeItemFromScene()
{
	deleteItem();
}

void
BaseItem::changeFont()
{
	QFontDialog dlg( d->m_font );

	if( dlg.exec() == QDialog::Accepted )
	{
		d->m_font = dlg.selectedFont();
		update();
	}
}

void
BaseItem::changeSize()
{
	int width = d->m_width;
	int height = d->m_height;

	SizeDialog dlg( width, height );

	if( dlg.exec() == QDialog::Accepted )
	{
		d->m_width = width;
		d->m_height = height;

		update();
	}
}

} /* namespace Scheme */

} /* namespace Globe */


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
#include <Globe/Scheme/text.hpp>
#include <Globe/Scheme/selection.hpp>
#include <Globe/Scheme/scene.hpp>
#include <Globe/Scheme/size_dialog.hpp>
#include <Globe/Scheme/text_dialog.hpp>

// Qt include.
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QFont>
#include <QFontDialog>
#include <QApplication>


namespace Globe {

namespace Scheme {

//
// TextPrivate
//

class TextPrivate
	:	public SelectablePrivate
{
public:
	TextPrivate( const QString & text, Selection * selection, Scene * scene )
		:	SelectablePrivate( selection, scene )
		,	m_text( text )
	{
	}

	~TextPrivate()
	{
	}

	//! Text.
	QString m_text;
	//! Font.
	QFont m_font;
}; // class TextPrivate


//
// Text
//

Text::Text( const QString & text, Selection * selection, Scene * scene )
	:	Selectable( new TextPrivate( text, selection, scene ) )
{
}

Text::~Text()
{
}

void
Text::setMode( SceneMode mode )
{
	auto dd = d_ptr();

	dd->m_mode = mode;

	if( dd->m_mode == EditScene )
	{
		setFlags( QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable |
			QGraphicsItem::ItemIsFocusable );
	}
	else
	{
		setFlags( 0 );
		setItemState( ItemNotSelected );
	}
}

void
Text::setEditMode( EditSceneMode mode )
{
	d_ptr()->m_editMode = mode;
}

void
Text::setItemState( ItemState st )
{
	d_ptr()->m_state = st;

	if( st == ItemSelected )
		setAcceptHoverEvents( true );
	else
		setAcceptHoverEvents( false );

	update();
}

void
Text::moveUp( int delta )
{
	setPos( pos().x(), pos().y() - delta );
}

void
Text::moveDown( int delta )
{
	setPos( pos().x(), pos().y() + delta );
}

void
Text::moveLeft( int delta )
{
	setPos( pos().x() - delta, pos().y() );
}

void
Text::moveRight( int delta )
{
	setPos( pos().x() + delta, pos().y() );
}

void
Text::deleteItem()
{
	d_ptr()->m_scene->removeText( this );

	deleteLater();
}

TextCfg
Text::cfg() const
{
	TextCfg cfg;

	auto dd = d_ptr();

	cfg.setText( dd->m_text );
	cfg.setPos( pos() );
	cfg.setSize( QSizeF( dd->m_width, dd->m_height ) );

	if( QApplication::font() != dd->m_font )
		cfg.setFont( dd->m_font );

	return cfg;
}

void
Text::setCfg( const TextCfg & cfg )
{
	auto dd = d_ptr();

	if( cfg.isFontSet() )
		dd->m_font = cfg.font();

	setPos( cfg.pos() );

	dd->m_width = cfg.size().width();
	dd->m_height = cfg.size().height();

	update();
}

QRectF
Text::boundingRect() const
{
	auto dd = d_ptr();

	return QRectF( 0, 0, dd->m_width, dd->m_height );
}

void
Text::paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
	QWidget * widget )
{
	Q_UNUSED( option )
	Q_UNUSED( widget )

	auto dd = d_ptr();

	if( dd->m_state == ItemSelected )
	{
		painter->setPen( Qt::blue );
		painter->drawRect( boundingRect() );

		painter->setBrush( Qt::blue );
		painter->drawRect( 0, 0, 3, 3 );
		painter->drawRect( boundingRect().width() - 3, 0, 3, 3 );
		painter->drawRect( 0, boundingRect().height() - 3, 3, 3 );
		painter->drawRect( boundingRect().width() - 3,
			boundingRect().height() - 3, 3, 3 );
	}

	painter->setPen( Qt::black );

	painter->setFont( dd->m_font );

	painter->drawText( boundingRect(), Qt::AlignCenter | Qt::TextWordWrap,
		dd->m_text );
}

void
Text::mouseMoveEvent( QGraphicsSceneMouseEvent * event )
{
	auto dd = d_ptr();

	if( dd->m_leftButtonPressed && dd->m_editMode == EditSceneSelect &&
		( dd->m_resizeMode & YesResize ) )
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

		if( width != dd->m_width || height != dd->m_height )
		{
			dd->m_width = width;
			dd->m_height = height;
			update();
		}
	}
	else
		QGraphicsObject::mouseMoveEvent( event );
}

void
Text::mousePressEvent( QGraphicsSceneMouseEvent * event )
{
	auto dd = d_ptr();

	if( dd->m_mode == EditScene )
	{
		if( dd->m_editMode == EditSceneSelect &&
			event->button() == Qt::LeftButton )
				dd->m_leftButtonPressed = true;
	}

	QGraphicsObject::mousePressEvent( event );
}

void
Text::mouseReleaseEvent( QGraphicsSceneMouseEvent * event )
{
	auto dd = d_ptr();

	if( dd->m_mode == EditScene )
	{
		if( dd->m_editMode == EditSceneSelect &&
			event->button() == Qt::LeftButton )
		{
			dd->m_leftButtonPressed = false;

			if( event->modifiers() == Qt::NoModifier )
				dd->m_selection->clear();

			dd->m_selection->addItem( this );

			event->accept();
		}
		else
			QGraphicsObject::mouseReleaseEvent( event );
	}
	else
		QGraphicsObject::mouseReleaseEvent( event );
}

void
Text::hoverEnterEvent( QGraphicsSceneHoverEvent * event )
{
	auto dd = d_ptr();

	if( dd->m_mode == EditScene && dd->m_editMode == EditSceneSelect &&
		dd->m_state == ItemSelected )
			detectResizeMode( event->pos() );
	else
		QGraphicsObject::hoverEnterEvent( event );
}

void
Text::hoverLeaveEvent( QGraphicsSceneHoverEvent * event )
{
	auto dd = d_ptr();

	if( dd->m_mode == EditScene && dd->m_editMode == EditSceneSelect &&
		dd->m_state == ItemSelected )
	{
		d->m_resizeMode = NoResize;
		QApplication::setOverrideCursor( QCursor( Qt::ArrowCursor ) );
	}
	else
		QGraphicsObject::hoverLeaveEvent( event );
}

void
Text::hoverMoveEvent( QGraphicsSceneHoverEvent * event )
{
	auto dd = d_ptr();

	if( dd->m_mode == EditScene && dd->m_editMode == EditSceneSelect &&
		dd->m_state == ItemSelected )
			detectResizeMode( event->pos() );
	else
		QGraphicsObject::hoverMoveEvent( event );
}

void
Text::detectResizeMode( const QPointF & pos )
{
	Selectable::detectResizeMode( pos, boundingRect() );
}

void
Text::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{
	auto dd = d_ptr();

	if( dd->m_mode == EditScene && dd->m_editMode == EditSceneSelect )
	{
		event->accept();

		QMenu menu;

		menu.addAction( QIcon( ":/img/add_text_22x22.png" ),
			tr( "Change Text" ), this, SLOT( changeText() ) );
		menu.addAction( QIcon( ":/img/character_set_22x22.png" ),
			tr( "Change Font" ), this, SLOT( changeFont() ) );
		menu.addAction( QIcon( ":/img/transform_scale_22x22.png" ),
			tr( "Change Size" ), this, SLOT( changeSize() ) );
		menu.addAction( QIcon( ":/img/remove_22x22.png" ),
			tr( "Delete Text" ), this, SLOT( removeItemFromScene() ) );

		menu.exec( event->screenPos() );
	}
}

void
Text::removeItemFromScene()
{
	deleteItem();
}

void
Text::changeFont()
{
	auto dd = d_ptr();

	QFontDialog dlg( dd->m_font );

	if( dlg.exec() == QDialog::Accepted )
	{
		dd->m_font = dlg.selectedFont();
		update();
	}
}

void
Text::changeSize()
{
	auto dd = d_ptr();

	int width = dd->m_width;
	int height = dd->m_height;

	SizeDialog dlg( width, height );

	if( dlg.exec() == QDialog::Accepted )
	{
		dd->m_width = width;
		dd->m_height = height;

		update();
	}
}

void
Text::changeText()
{
	auto dd = d_ptr();

	QString text = dd->m_text;

	TextDialog dlg( text );

	if( dlg.exec() == QDialog::Accepted )
	{
		dd->m_text = text;
		update();
	}
}

TextPrivate *
Text::d_ptr()
{
	return static_cast< TextPrivate* > ( d.data() );
}

const TextPrivate *
Text::d_ptr() const
{
	return static_cast< TextPrivate* > ( d.data() );
}

} /* namespace Scheme */

} /* namespace Globe */

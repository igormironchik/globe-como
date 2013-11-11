
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

class TextPrivate {
public:
	TextPrivate( const QString & text, Selection * selection, Scene * scene )
		:	m_mode( ViewScene )
		,	m_editMode( EditSceneSelect )
		,	m_state( ItemNotSelected )
		,	m_resizeMode( NoResize )
		,	m_leftButtonPressed( false )
		,	m_width( 50 )
		,	m_height( 25 )
		,	m_selection( selection )
		,	m_scene( scene )
		,	m_text( text )
	{
	}

	//! Mode of the scene.
	SceneMode m_mode;
	//! Edit mode of the scene.
	EditSceneMode m_editMode;
	//! Item state.
	ItemState m_state;
	//! Resize mode.
	ResizeMode m_resizeMode;
	//! Left mouse button was pressed.
	bool m_leftButtonPressed;
	//! Width.
	qreal m_width;
	//! Height.
	qreal m_height;
	//! Selection.
	Selection * m_selection;
	//! Scene.
	Scene * m_scene;
	//! Text.
	QString m_text;
	//! Font.
	QFont m_font;
}; // class TextPrivate


//
// Text
//

Text::Text( const QString & text, Selection * selection, Scene * scene )
	:	d( new TextPrivate( text, selection, scene ) )
{
}

void
Text::setMode( SceneMode mode )
{
	d->m_mode = mode;

	if( d->m_mode == EditScene )
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
	d->m_editMode = mode;
}

void
Text::setItemState( ItemState st )
{
	d->m_state = st;

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
	d->m_scene->removeText( this );

	deleteLater();
}

TextCfg
Text::cfg() const
{
	TextCfg cfg;

	cfg.setText( d->m_text );
	cfg.setPos( pos() );
	cfg.setSize( QSizeF( d->m_width, d->m_height ) );

	if( QApplication::font() != d->m_font )
		cfg.setFont( d->m_font );

	return cfg;
}

void
Text::setCfg( const TextCfg & cfg )
{
	if( cfg.isFontSet() )
		d->m_font = cfg.font();

	setPos( cfg.pos() );

	d->m_width = cfg.size().width();
	d->m_height = cfg.size().height();

	update();
}

QRectF
Text::boundingRect() const
{
	return QRectF( 0, 0, d->m_width, d->m_height );
}

void
Text::paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
	QWidget * widget )
{
	Q_UNUSED( option )
	Q_UNUSED( widget )

	if( d->m_state == ItemSelected )
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

	painter->setFont( d->m_font );

	painter->drawText( boundingRect(), Qt::AlignCenter | Qt::TextWordWrap,
		d->m_text );
}

void
Text::mouseMoveEvent( QGraphicsSceneMouseEvent * event )
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
		}

		if( x != pos().x() || y != pos().y() )
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
Text::mousePressEvent( QGraphicsSceneMouseEvent * event )
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
Text::mouseReleaseEvent( QGraphicsSceneMouseEvent * event )
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
Text::hoverEnterEvent( QGraphicsSceneHoverEvent * event )
{
	if( d->m_mode == EditScene && d->m_editMode == EditSceneSelect &&
		d->m_state == ItemSelected )
			detectResizeMode( event->pos() );
	else
		QGraphicsObject::hoverEnterEvent( event );
}

void
Text::hoverLeaveEvent( QGraphicsSceneHoverEvent * event )
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
Text::hoverMoveEvent( QGraphicsSceneHoverEvent * event )
{
	if( d->m_mode == EditScene && d->m_editMode == EditSceneSelect &&
		d->m_state == ItemSelected )
			detectResizeMode( event->pos() );
	else
		QGraphicsObject::hoverMoveEvent( event );
}

void
Text::detectResizeMode( const QPointF & pos )
{
	const QRectF topLeftRect( 0, 0, 3, 3 );
	const QRectF topRightRect( boundingRect().width() - 3, 0, 3, 3 );
	const QRectF bottomLeftRect( 0, boundingRect().height() - 3, 3, 3 );
	const QRectF bottomRightRect( boundingRect().width() - 3,
		boundingRect().height() - 3, 3, 3 );

	if( topLeftRect.contains( pos ) )
	{
		d->m_resizeMode = ResizeTopLeft;
		QApplication::setOverrideCursor( QCursor( Qt::SizeFDiagCursor ) );
	}
	else if( topRightRect.contains( pos ) )
	{
		d->m_resizeMode = ResizeTopRight;
		QApplication::setOverrideCursor( QCursor( Qt::SizeBDiagCursor ) );
	}
	else if( bottomLeftRect.contains( pos ) )
	{
		d->m_resizeMode = ResizeBottomLeft;
		QApplication::setOverrideCursor( QCursor( Qt::SizeBDiagCursor ) );
	}
	else if( bottomRightRect.contains( pos ) )
	{
		d->m_resizeMode = ResizeBottomRight;
		QApplication::setOverrideCursor( QCursor( Qt::SizeFDiagCursor ) );
	}
	else
	{
		d->m_resizeMode = NoResize;
		QApplication::setOverrideCursor( QCursor( Qt::ArrowCursor ) );
	}
}

void
Text::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{
	if( d->m_mode == EditScene && d->m_editMode == EditSceneSelect )
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
	QFontDialog dlg( d->m_font );

	if( dlg.exec() == QDialog::Accepted )
	{
		d->m_font = dlg.selectedFont();
		update();
	}
}

void
Text::changeSize()
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

void
Text::changeText()
{
	QString text = d->m_text;

	TextDialog dlg( text );

	if( dlg.exec() == QDialog::Accepted )
	{
		d->m_text = text;
		update();
	}
}

} /* namespace Scheme */

} /* namespace Globe */

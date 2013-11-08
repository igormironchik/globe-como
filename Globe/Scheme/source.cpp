
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
#include <Globe/Scheme/source.hpp>
#include <Globe/Scheme/selection.hpp>
#include <Globe/Scheme/scene.hpp>
#include <Globe/Scheme/size_dialog.hpp>

#include <Globe/Core/properties_manager.hpp>
#include <Globe/Core/color_for_level.hpp>

// Qt include.
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QApplication>
#include <QCursor>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QFont>
#include <QFontDialog>
#include <QApplication>


namespace Globe {

namespace Scheme {

//
// SourcePrivate
//

class SourcePrivate {
public:
	SourcePrivate( const Como::Source & source, const QString & channelName,
		Selection * selection, Scene * scene )
		:	m_source( source )
		,	m_channelName( channelName )
		,	m_mode( ViewScene )
		,	m_editMode( EditSceneSelect )
		,	m_state( ItemNotSelected )
		,	m_resizeMode( NoResize )
		,	m_leftButtonPressed( false )
		,	m_width( 50 )
		,	m_height( 25 )
		,	m_selection( selection )
		,	m_scene( scene )
	{
	}

	//! Source.
	Como::Source m_source;
	//! Channel name.
	QString m_channelName;
	//! Mode of the scene.
	SceneMode m_mode;
	//! Edit mode of the scene.
	EditSceneMode m_editMode;
	//! Item state.
	ItemState m_state;
	//! Color for painting.
	QColor m_fillColor;
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
	//! Font.
	QFont m_font;
	//! Scene.
	Scene * m_scene;
}; // class SourcePrivate


//
// Source
//

Source::Source( const Como::Source & source, const QString & channelName,
	Selection * selection, Scene * scene )
	:	d( new SourcePrivate( source, channelName, selection,
			scene ) )
{
	setSource( source );
}

void
Source::setMode( SceneMode mode )
{
	d->m_mode = mode;

	if( d->m_mode == EditScene )
		setFlags( QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable |
			QGraphicsItem::ItemIsFocusable );
	else
	{
		setFlags( 0 );
		setItemState( ItemNotSelected );
	}
}

void
Source::setEditMode( EditSceneMode mode )
{
	d->m_editMode = mode;
}

void
Source::setItemState( ItemState st )
{
	d->m_state = st;

	if( st == ItemSelected )
		setAcceptHoverEvents( true );
	else
		setAcceptHoverEvents( false );

	update();
}

void
Source::moveUp( int delta )
{
	setPos( pos().x(), pos().y() - delta );
}

void
Source::moveDown( int delta )
{
	setPos( pos().x(), pos().y() + delta );
}

void
Source::moveLeft( int delta )
{
	setPos( pos().x() - delta, pos().y() );
}

void
Source::moveRight( int delta )
{
	setPos( pos().x() + delta, pos().y() );
}

void
Source::deleteItem()
{
	d->m_scene->removeSource( this );

	deleteLater();
}

const QString &
Source::channelName() const
{
	return d->m_channelName;
}

const Como::Source &
Source::source() const
{
	return d->m_source;
}

void
Source::setSource( const Como::Source & source )
{
	d->m_source = source;

	const Properties * props = PropertiesManager::instance().findProperties(
		d->m_source, d->m_channelName, 0 );

	Level level = None;

	if( props )
	{
		level = props->checkConditions( d->m_source.value(),
			d->m_source.type() ).level();
	}

	d->m_fillColor = ColorForLevel::instance().color( level );

	update();
}

SourceCfg
Source::cfg() const
{
	SourceCfg cfg;

	cfg.setChannelName( d->m_channelName );
	cfg.setType( d->m_source.type() );
	cfg.setTypeName( d->m_source.typeName() );
	cfg.setSourceName( d->m_source.name() );
	cfg.setPos( pos() );
	cfg.setSize( QSizeF( d->m_width, d->m_height ) );

	if( QApplication::font() != d->m_font )
		cfg.setFont( d->m_font );

	return cfg;
}

void
Source::setCfg( const SourceCfg & cfg )
{
	if( cfg.isFontSet() )
		d->m_font = cfg.font();

	setPos( cfg.pos() );

	d->m_width = cfg.size().width();
	d->m_height = cfg.size().height();
}

void
Source::disconnected()
{
	d->m_fillColor = ColorForLevel::instance().disconnectedColor();

	update();
}

void
Source::deregistered()
{
	d->m_fillColor = ColorForLevel::instance().deregisteredColor();

	update();
}

QRectF
Source::boundingRect() const
{
	return QRectF( 0, 0, d->m_width, d->m_height );
}

void
Source::paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
	QWidget * widget )
{
	Q_UNUSED( option )
	Q_UNUSED( widget )

	if( d->m_state == ItemNotSelected )
		painter->setPen( Qt::black );
	else
		painter->setPen( Qt::blue );

	painter->setBrush( d->m_fillColor );

	painter->drawRect( boundingRect() );

	if( d->m_state == ItemSelected )
	{
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
		d->m_source.value().toString() );
}

void
Source::mouseMoveEvent( QGraphicsSceneMouseEvent * event )
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
Source::mousePressEvent( QGraphicsSceneMouseEvent * event )
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
Source::mouseReleaseEvent( QGraphicsSceneMouseEvent * event )
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
Source::hoverEnterEvent( QGraphicsSceneHoverEvent * event )
{
	if( d->m_mode == EditScene && d->m_editMode == EditSceneSelect &&
		d->m_state == ItemSelected )
			detectResizeMode( event->pos() );
	else
		QGraphicsObject::hoverEnterEvent( event );
}

void
Source::hoverLeaveEvent( QGraphicsSceneHoverEvent * event )
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
Source::hoverMoveEvent( QGraphicsSceneHoverEvent * event )
{
	if( d->m_mode == EditScene && d->m_editMode == EditSceneSelect &&
		d->m_state == ItemSelected )
			detectResizeMode( event->pos() );
	else
		QGraphicsObject::hoverMoveEvent( event );
}

void
Source::detectResizeMode( const QPointF & pos )
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
Source::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{
	if( d->m_mode == EditScene && d->m_editMode == EditSceneSelect )
	{
		event->accept();

		QMenu menu;

		menu.addAction( QIcon( ":/img/character_set_22x22.png" ),
			tr( "Change Font" ), this, SLOT( changeFont() ) );
		menu.addAction( QIcon( ":/img/transform_scale_22x22.png" ),
			tr( "Change Size" ), this, SLOT( changeSize() ) );
		menu.addAction( QIcon( ":/img/remove_22x22.png" ),
			tr( "Delete Source" ), this, SLOT( removeItemFromScene() ) );

		menu.exec( event->screenPos() );
	}
}

void
Source::removeItemFromScene()
{
	deleteItem();
}

void
Source::changeFont()
{
	QFontDialog dlg( d->m_font );

	if( dlg.exec() == QDialog::Accepted )
	{
		d->m_font = dlg.selectedFont();
		update();
	}
}

void
Source::changeSize()
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

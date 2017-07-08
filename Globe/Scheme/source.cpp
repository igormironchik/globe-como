
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
#include <QCursor>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QFont>
#include <QFontDialog>
#include <QApplication>
#include <QGraphicsView>


namespace Globe {

namespace Scheme {

//
// SourcePrivate
//

class SourcePrivate
	:	public SelectablePrivate
{
public:
	SourcePrivate( const Como::Source & source, const QString & channelName,
		Selection * selection, Scene * scene )
		:	SelectablePrivate( selection, scene )
		,	m_source( source )
		,	m_channelName( channelName )
	{
	}

	~SourcePrivate()
	{
	}

	//! Source.
	Como::Source m_source;
	//! Channel name.
	QString m_channelName;
	//! Color for painting.
	QColor m_fillColor;
	//! Font.
	QFont m_font;
	//! Current properties key.
	PropertiesKey m_currentKey;
}; // class SourcePrivate


//
// Source
//

Source::Source( const Como::Source & source, const QString & channelName,
	Selection * selection, Scene * scene )
	:	Selectable( new SourcePrivate( source, channelName, selection,
			scene ) )
{
	setSource( source );
}

Source::~Source()
{
}

void
Source::setMode( SceneMode mode )
{
	auto dd = d_ptr();

	dd->m_mode = mode;

	if( dd->m_mode == EditScene )
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
	d_ptr()->m_editMode = mode;
}

void
Source::setItemState( ItemState st )
{
	d_ptr()->m_state = st;

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
	d_ptr()->m_scene->removeSource( this );

	deleteLater();
}

const QString &
Source::channelName() const
{
	return d_ptr()->m_channelName;
}

const Como::Source &
Source::source() const
{
	return d_ptr()->m_source;
}

static inline QString createToolTip( const QString & channelName,
	const Como::Source & s )
{
	QString res;

	res.append( QLatin1String( "<b>Channel:</b> " ) );
	res.append( channelName );
	res.append( QLatin1String( "<br><b>Type:</b> " ) );
	res.append( s.typeName() );
	res.append( QLatin1String( "<br><b>Name:</b> " ) );
	res.append( s.name() );

	if( !s.description().isEmpty() )
	{
		res.append( QLatin1String( "<br><b>Description:</b> " ) );
		res.append( s.description() );
	}

	return res;
}

void
Source::setSource( const Como::Source & source )
{
	auto dd = d_ptr();

	dd->m_source = source;

	const Properties * props = PropertiesManager::instance().findProperties(
		dd->m_source, dd->m_channelName, 0 );

	Level level = None;

	if( props )
	{
		level = props->checkConditions( dd->m_source.value(),
			dd->m_source.type() ).level();
	}

	dd->m_fillColor = ColorForLevel::instance().color( level );

	setToolTip( createToolTip( dd->m_channelName, source ) );

	update();
}

SourceCfg
Source::cfg() const
{
	SourceCfg cfg;

	auto dd = d_ptr();

	cfg.setChannelName( dd->m_channelName );
	cfg.setType( dd->m_source.type() );
	cfg.setTypeName( dd->m_source.typeName() );
	cfg.setSourceName( dd->m_source.name() );
	cfg.setPos( pos() );
	cfg.setSize( QSizeF( dd->m_width, dd->m_height ) );

	if( QApplication::font() != dd->m_font )
		cfg.setFont( dd->m_font );

	return cfg;
}

void
Source::setCfg( const SourceCfg & cfg )
{
	auto dd = d_ptr();

	if( cfg.isFontSet() )
		dd->m_font = cfg.font();

	setPos( cfg.pos() );

	dd->m_width = cfg.size().width();
	dd->m_height = cfg.size().height();
}

void
Source::disconnected()
{
	d_ptr()->m_fillColor = ColorForLevel::instance().disconnectedColor();

	update();
}

void
Source::deregistered()
{
	d_ptr()->m_fillColor = ColorForLevel::instance().deregisteredColor();

	update();
}

void
Source::propertiesChanged()
{
	auto dd = d_ptr();

	const Properties * props = PropertiesManager::instance().findProperties(
		dd->m_source, dd->m_channelName, 0 );

	Level level = None;

	if( props )
	{
		level = props->checkConditions( dd->m_source.value(),
			dd->m_source.type() ).level();
	}

	const QColor newColor = ColorForLevel::instance().color( level );

	if( dd->m_fillColor != newColor )
	{
		dd->m_fillColor = newColor;

		update();
	}
}

QRectF
Source::boundingRect() const
{
	auto dd = d_ptr();

	return QRectF( 0, 0, dd->m_width, dd->m_height );
}

void
Source::paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
	QWidget * widget )
{
	Q_UNUSED( option )
	Q_UNUSED( widget )

	auto dd = d_ptr();

	if( dd->m_state == ItemNotSelected )
		painter->setPen( Qt::black );
	else
		painter->setPen( Qt::blue );

	painter->setBrush( dd->m_fillColor );

	painter->drawRect( boundingRect() );

	if( dd->m_state == ItemSelected )
	{
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
		dd->m_source.value().toString() );
}

void
Source::mouseMoveEvent( QGraphicsSceneMouseEvent * event )
{
	auto dd = d_ptr();

	if( dd->m_leftButtonPressed && dd->m_editMode == EditSceneSelect &&
		( dd->m_resizeMode & YesResize ) )
	{
		qreal x = pos().x();
		qreal y = pos().y();
		qreal width = boundingRect().width();
		qreal height = boundingRect().height();

		switch( dd->m_resizeMode )
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
Source::mousePressEvent( QGraphicsSceneMouseEvent * event )
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
Source::mouseReleaseEvent( QGraphicsSceneMouseEvent * event )
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
Source::hoverEnterEvent( QGraphicsSceneHoverEvent * event )
{
	auto dd = d_ptr();

	if( dd->m_mode == EditScene && dd->m_editMode == EditSceneSelect &&
		dd->m_state == ItemSelected )
			detectResizeMode( event->pos() );
	else
		QGraphicsObject::hoverEnterEvent( event );
}

void
Source::hoverLeaveEvent( QGraphicsSceneHoverEvent * event )
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
Source::hoverMoveEvent( QGraphicsSceneHoverEvent * event )
{
	auto dd = d_ptr();

	if( dd->m_mode == EditScene && dd->m_editMode == EditSceneSelect &&
		dd->m_state == ItemSelected )
			detectResizeMode( event->pos() );
	else
		QGraphicsObject::hoverMoveEvent( event );
}

void
Source::detectResizeMode( const QPointF & pos )
{
	Selectable::detectResizeMode( pos, boundingRect() );
}

void
Source::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{
	QMenu menu;

	auto dd = d_ptr();

	if( dd->m_mode == EditScene && dd->m_editMode == EditSceneSelect )
	{
		menu.addAction( QIcon( ":/img/character_set_22x22.png" ),
			tr( "Change Font" ), this, SLOT( changeFont() ) );
		menu.addAction( QIcon( ":/img/transform_scale_22x22.png" ),
			tr( "Change Size" ), this, SLOT( changeSize() ) );
		menu.addAction( QIcon( ":/img/remove_22x22.png" ),
			tr( "Delete Source" ), this, SLOT( removeItemFromScene() ) );
	}
	else
	{
		const Properties * p = PropertiesManager::instance().findProperties(
			source(), channelName(), &dd->m_currentKey );

		if( p )
		{
			menu.addAction( QIcon( ":/img/edit_22x22.png" ),
				tr( "Edit Properties" ), this, SLOT( editProperties() ) );
			menu.addAction( QIcon( ":/img/export_22x22.png" ),
				tr( "Promote Properties To" ), this, SLOT( promoteProperties() ) );
			menu.addAction( QIcon( ":/img/remove_22x22.png" ),
				tr( "Delete Properties" ), this, SLOT( deleteProperties() ) );
		}
		else
			menu.addAction( QIcon( ":/img/add_22x22.png" ),
				tr( "Add Properties" ), this, SLOT( addProperties() ) );
	}

	menu.exec( event->screenPos() );

	event->accept();
}

void
Source::removeItemFromScene()
{
	deleteItem();
}

void
Source::changeFont()
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
Source::changeSize()
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
Source::addProperties()
{
	PropertiesManager::instance().addProperties( source(), channelName(),
		d_ptr()->m_scene->views().first() );
}

void
Source::editProperties()
{
	auto dd = d_ptr();

	PropertiesManager::instance().editProperties( dd->m_currentKey,
		dd->m_scene->views().first() );
}

void
Source::deleteProperties()
{
	auto dd = d_ptr();

	PropertiesManager::instance().removeProperties( dd->m_currentKey,
		dd->m_scene->views().first() );
}

void
Source::promoteProperties()
{
	auto dd = d_ptr();

	PropertiesManager::instance().promoteProperties( dd->m_currentKey,
		dd->m_scene->views().first() );
}

SourcePrivate *
Source::d_ptr()
{
	return static_cast< SourcePrivate* > ( d.data() );
}

const SourcePrivate *
Source::d_ptr() const
{
	return static_cast< SourcePrivate* > ( d.data() );
}

} /* namespace Scheme */

} /* namespace Globe */

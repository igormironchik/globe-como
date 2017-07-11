
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
#include <Globe/Scheme/scene.hpp>
#include <Globe/Scheme/scheme_utils.hpp>

#include <Globe/Core/properties_manager.hpp>
#include <Globe/Core/color_for_level.hpp>

// Qt include.
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
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
	//! Current properties key.
	PropertiesKey m_currentKey;
}; // class SourcePrivate


//
// Source
//

Source::Source( const Como::Source & source, const QString & channelName,
	Selection * selection, Scene * scene )
	:	BaseItem( new SourcePrivate( source, channelName, selection,
			scene ) )
{
	setSource( source );
}

Source::~Source()
{
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

void
Source::setSource( const Como::Source & source )
{
	auto * dd = d_ptr();

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

	auto * dd = d_ptr();

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
	auto * dd = d_ptr();

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
	auto * dd = d_ptr();

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

void
Source::paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
	QWidget * widget )
{
	Q_UNUSED( option )
	Q_UNUSED( widget )

	auto * dd = d_ptr();

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
Source::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{
	QMenu menu;

	auto * dd = d_ptr();

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
Source::addProperties()
{
	PropertiesManager::instance().addProperties( source(), channelName(),
		d_ptr()->m_scene->views().first() );
}

void
Source::editProperties()
{
	auto * dd = d_ptr();

	PropertiesManager::instance().editProperties( dd->m_currentKey,
		dd->m_scene->views().first() );
}

void
Source::deleteProperties()
{
	auto * dd = d_ptr();

	PropertiesManager::instance().removeProperties( dd->m_currentKey,
		dd->m_scene->views().first() );
}

void
Source::promoteProperties()
{
	auto * dd = d_ptr();

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
	return static_cast< const SourcePrivate* > ( d.data() );
}

} /* namespace Scheme */

} /* namespace Globe */

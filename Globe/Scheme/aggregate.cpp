
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
#include <Globe/Scheme/aggregate.hpp>
#include <Globe/Scheme/source.hpp>
#include <Globe/Scheme/text.hpp>
#include <Globe/Scheme/scene.hpp>
#include <Globe/Scheme/scheme_utils.hpp>

#include <Globe/Core/properties_manager.hpp>
#include <Globe/Core/color_for_level.hpp>
#include <Globe/Core/sources.hpp>

// Qt include.
#include <QPainter>
#include <QMenu>
#include <QIcon>
#include <QGraphicsSceneContextMenuEvent>
#include <QMap>


namespace Globe {

namespace Scheme {

namespace /* anonymous */ {

//
// Key
//

//! Key of the source.
class Key {
public:
	Key( const QString & name, const QString & type )
		:	m_key( type + QLatin1String( "::" ) + name )
	{
	}

	~Key()
	{
	}

	bool operator < ( const Key & other ) const
	{
		return ( m_key < other.m_key );
	}

private:
	//! Key.
	QString m_key;
}; // class Key


//
// SourceProps
//

//! Additional properties of the source.
struct SourceProps {
	SourceProps()
		:	m_registered( false )
		,	m_level( None )
		,	m_connected( false )
	{
	}

	//! Registered?
	bool m_registered;
	//! Level.
	Level m_level;
	//! Connected?
	bool m_connected;
}; // struct SourceProps

} /* namespace anonymous */


//
// AggregatePrivate
//

class AggregatePrivate
	:	public SelectablePrivate
{
public:
	AggregatePrivate( Selection * selection, Scene * scene )
		:	SelectablePrivate( selection, scene )
		,	m_level( None )
	{
	}

	~AggregatePrivate()
	{
	}

	//! Sources.
	QMap< QString, QMap< Key, QPair< Como::Source, SourceProps > > > m_sources;
	//! Configuration.
	SchemeCfg m_cfg;
	//! Current color.
	QColor m_fillColor;
	//! Level.
	Level m_level;
	//! Current source.
	Como::Source m_current;
	//! Current channel.
	QString m_channel;
	//! Channels.
	QStringList m_channels;
}; // class AggregatePrivate;


//
// Aggregate
//

Aggregate::Aggregate( Selection * selection, Scene * scene )
	:	BaseItem( new AggregatePrivate( selection, scene ) )
{

}

Aggregate::~Aggregate()
{
}

void
Aggregate::deleteItem()
{
	d_ptr()->m_scene->removeAggregate( this );

	deleteLater();
}

SchemeCfg
Aggregate::cfg() const
{
	return d_ptr()->m_cfg;
}

void
Aggregate::setCfg( const SchemeCfg & cfg )
{
	auto * dd = d_ptr();

	dd->m_cfg = cfg;

	dd->m_channels.clear();

	dd->m_sources.clear();

	for( const auto & p : sources() )
	{
		if( !dd->m_channels.contains( p.second ) )
			dd->m_channels.append( p.second );

		const Key key( p.first.name(), p.first.typeName() );

		if( !dd->m_sources[ p.second ].contains( key ) )
			dd->m_sources[ p.second ].insert( key,
				qMakePair( p.first, SourceProps() ) );
	}
}

const QStringList &
Aggregate::listOfChannels() const
{
	return d_ptr()->m_channels;
}

QList< QPair< Como::Source, QString > >
Aggregate::sources() const
{
	return d_ptr()->m_cfg.availableSources();
}

void
Aggregate::syncSource( const Como::Source & source,
	const QString & channel, bool isRegistered )
{
	auto * dd = d_ptr();

	const Key key( source.name(), source.typeName() );

	if( dd->m_sources.contains( channel ) &&
		dd->m_sources[ channel ].contains( key ) )
	{
		dd->m_sources[ channel ][ key ].first = source;

		dd->m_sources[ channel ][ key ].second.m_registered = isRegistered;

		const Properties * props = PropertiesManager::instance()
			.findProperties( source, channel, 0 );

		Level level = None;

		if( props )
		{
			level = props->checkConditions( source.value(),
				source.type() ).level();
		}

		dd->m_sources[ channel ][ key ].second.m_level = level;

		if( isRegistered && level < dd->m_level )
		{
			dd->m_current = source;

			dd->m_fillColor = ColorForLevel::instance().color( level );

			update();
		}
		else if( source == dd->m_current )
		{
			Level level = None;

			bool found = false;

			dd->m_fillColor = ColorForLevel::instance().color( level );

			QMapIterator< QString,
				QMap< Key, QPair< Como::Source, SourceProps > > >
					it( dd->m_sources );

			bool connected = false;

			while( it.hasNext() )
			{
				it.next();

				for( const auto & s : qAsConst( it.value() ) )
				{
					if( s.second.m_connected )
						connected = true;

					if( s.second.m_registered &&
						s.second.m_connected &&
						s.second.m_level < level )
					{
						level = s.second.m_level;

						dd->m_channel = it.key();

						dd->m_current = s.first;

						dd->m_fillColor =
							ColorForLevel::instance().color( level );

						found = true;
					}
				}
			}

			if( found )
				setToolTip( createToolTip( dd->m_channel, dd->m_current ) );
			else if( connected )
			{
				dd->m_fillColor = ColorForLevel::instance().deregisteredColor();

				setToolTip( QString() );
			}
			else
			{
				dd->m_fillColor = ColorForLevel::instance().disconnectedColor();

				setToolTip( QString() );
			}

			update();
		}
	}
}

void
Aggregate::paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
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
}

void
Aggregate::propertiesChanged()
{
	auto * dd = d_ptr();

	bool registered = false;

	SourcesManager::instance().syncSource( dd->m_channel,
		dd->m_current, registered );

	syncSource( dd->m_current, dd->m_channel, registered );
}

void
Aggregate::channelDisconnected( const QString & name )
{
	auto * dd = d_ptr();

	if( dd->m_sources.contains( name ) )
	{
		QMutableMapIterator< Key, QPair< Como::Source, SourceProps > > it(
			dd->m_sources[ name ] );

		while( it.hasNext() )
		{
			it.next();

			it.value().second.m_connected = false;
			it.value().second.m_registered = false;
		}
	}

	if( dd->m_channel == name )
		syncSource( dd->m_current, dd->m_channel, false );
}

void
Aggregate::channelDeregistered( const QString & name )
{
	auto * dd = d_ptr();

	if( dd->m_channel == name )
		syncSource( dd->m_current, dd->m_channel, false );
}

void
Aggregate::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{
	auto * dd = d_ptr();

	if( dd->m_mode == EditScene && dd->m_editMode == EditSceneSelect )
	{
		QMenu menu;

		menu.addAction( QIcon( ":/img/transform_scale_22x22.png" ),
			tr( "Change Size" ), this, SLOT( changeSize() ) );
		menu.addAction( QIcon( ":/img/remove_22x22.png" ),
			tr( "Delete Source" ), this, SLOT( removeItemFromScene() ) );

		menu.exec( event->screenPos() );
	}

	event->accept();
}

AggregatePrivate *
Aggregate::d_ptr()
{
	return static_cast< AggregatePrivate* > ( d.data() );
}

const AggregatePrivate *
Aggregate::d_ptr() const
{
	return static_cast< const AggregatePrivate* > ( d.data() );
}

} /* namespace Scheme */

} /* namespace Globe */
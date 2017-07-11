
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
	{
	}

	~AggregatePrivate()
	{
	}

	//! Sources.
	QMap< QString, QMap< Key, QPair< Como::Source, bool > > > m_sources;
	//! Configuration.
	SchemeCfg m_cfg;
	//! Current color.
	QColor m_fillColor;
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
	auto dd = d_ptr();

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
				qMakePair( p.first, false ) );
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
	auto dd = d_ptr();

	const Key key( source.name(), source.typeName() );

	if( dd->m_sources.contains( channel ) &&
		dd->m_sources[ channel ].contains( key ) )
	{
		dd->m_sources[ channel ][ key ].first = source;

		dd->m_sources[ channel ][ key ].second = isRegistered;
	}
}

void
Aggregate::paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
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
}

void
Aggregate::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{
	auto dd = d_ptr();

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

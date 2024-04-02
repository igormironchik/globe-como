
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Scheme/aggregate.hpp>
#include <Scheme/source.hpp>
#include <Scheme/text.hpp>
#include <Scheme/scene.hpp>
#include <Scheme/scheme_utils.hpp>
#include <Scheme/window.hpp>

#include <Core/properties_manager.hpp>
#include <Core/color_for_level.hpp>
#include <Core/sources.hpp>
#include <Core/mainwindow.hpp>
#include <Core/channels.hpp>

// Qt include.
#include <QPainter>
#include <QMenu>
#include <QIcon>
#include <QGraphicsSceneContextMenuEvent>
#include <QMap>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>


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

	friend bool operator < ( const Key & k1, const Key & k2 )
	{
		return ( k1.m_key < k2.m_key );
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
		,	m_level( Uninitialized )
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
	AggregatePrivate( Selection * selection, Scene * scene,
		Aggregate * parent )
		:	SelectablePrivate( selection, scene )
		,	m_fillColor( ColorForLevel::instance().disconnectedColor() )
		,	m_level( Uninitialized )
		,	q( parent )
	{
	}

	~AggregatePrivate()
	{
	}

	//! Calculate current value.
	void calcCurrentValue();

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
	//! Parent.
	Aggregate * q;
}; // class AggregatePrivate;

void
AggregatePrivate::calcCurrentValue()
{
	Level level = Uninitialized;

	bool found = false;

	m_fillColor = ColorForLevel::instance().color( None );

	QMapIterator< QString,
		QMap< Key, QPair< Como::Source, SourceProps > > >
			it( m_sources );

	bool connected = false;
	bool disconnected = false;

	while( it.hasNext() )
	{
		it.next();

		for( const auto & s : std::as_const( it.value() ) )
		{
			if( s.second.m_connected )
				connected = true;
			else
				disconnected = true;

			if( s.second.m_registered &&
				s.second.m_connected &&
				s.second.m_level < level )
			{
				level = s.second.m_level;

				m_channel = it.key();

				m_current = s.first;

				m_fillColor =
					ColorForLevel::instance().color( level );

				m_level = level;

				found = true;
			}
		}
	}

	if( !disconnected && found )
		q->setToolTip( createToolTip( m_channel, m_current ) );
	else if( disconnected )
	{
		m_fillColor = ColorForLevel::instance().disconnectedColor();

		q->setToolTip( QString() );
	}
	else if( connected )
	{
		m_fillColor = ColorForLevel::instance().deregisteredColor();

		q->setToolTip( QString() );
	}

	q->update();
}


//
// Aggregate
//

Aggregate::Aggregate( Selection * selection, Scene * scene )
	:	BaseItem( new AggregatePrivate( selection, scene, this ) )
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
	auto * dd = d_ptr();

	SchemeCfg cfg = dd->m_cfg;

	cfg.setPos( pos() );
	cfg.setSize( QSizeF( dd->m_width, dd->m_height ) );

	return cfg;
}

void
Aggregate::setCfg( const SchemeCfg & cfg )
{
	auto * dd = d_ptr();

	dd->m_cfg = cfg;

	dd->m_channels.clear();

	dd->m_sources.clear();

	const auto s = sources();

	for( const auto & p : s )
	{
		if( !dd->m_channels.contains( p.second ) )
			dd->m_channels.append( p.second );

		const Key key( p.first.name(), p.first.typeName() );

		if( !dd->m_sources[ p.second ].contains( key ) )
			dd->m_sources[ p.second ].insert( key,
				qMakePair( p.first, SourceProps() ) );
	}

	setPos( cfg.pos() );

	dd->m_width = cfg.size().width();
	dd->m_height = cfg.size().height();

	dd->calcCurrentValue();
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

		dd->m_sources[ channel ][ key ].second.m_connected = true;

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

			dd->m_channel = channel;

			dd->m_level = level;

			dd->m_fillColor = ColorForLevel::instance().color( level );

			setToolTip( createToolTip( dd->m_channel, dd->m_current ) );

			update();
		}
		else if( source == dd->m_current )
			dd->calcCurrentValue();
		else if( dd->m_level == Uninitialized )
			dd->calcCurrentValue();
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
	d_ptr()->calcCurrentValue();
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

	dd->calcCurrentValue();
}

void
Aggregate::channelDeregistered( const QString & name )
{
	channelDisconnected( name );
}

void
Aggregate::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{
	auto * dd = d_ptr();

	if( dd->m_mode == EditScene && dd->m_editMode == EditSceneSelect )
	{
		QMenu menu;

		menu.addAction( QIcon( ":/img/document_edit_22x22.png" ),
			tr( "Show Aggregate" ), this, &Aggregate::showScheme );
		menu.addAction( QIcon( ":/img/transform_scale_22x22.png" ),
			tr( "Change Size" ), this, SLOT( changeSize() ) );
		menu.addAction( QIcon( ":/img/remove_22x22.png" ),
			tr( "Delete Aggregate" ), this, SLOT( removeItemFromScene() ) );

		menu.exec( event->screenPos() );
	}
	else if( dd->m_mode == ViewScene )
	{
		QMenu menu;

		menu.addAction( tr( "Show Aggregate" ), this, &Aggregate::showScheme );

		menu.exec( event->screenPos() );
	}

	event->accept();
}

void
Aggregate::mouseDoubleClickEvent( QGraphicsSceneMouseEvent * event )
{
	showScheme();

	event->accept();
}

void
Aggregate::showScheme()
{
	auto * dd = d_ptr();

	Window * w = MainWindow::instance().findAggregate( dd->m_cfg.name() );

	if( !w )
	{
		w = new Window;
		w->initMenu( MainWindow::instance().menu() );
		w->loadScheme( dd->m_cfg, dd->m_mode == EditScene );

		auto * v = scene()->views().first();
		w->move( v->mapToGlobal( v->mapFromScene( scenePos() ) ) );

		connect( w, &Window::schemePossiblyChanged, this, &Aggregate::schemeChanged );
	}

	w->show();
}

void
Aggregate::schemeChanged()
{
	Window * w = static_cast< Window* > ( sender() );

	SchemeCfg cfg = w->schemeCfg();
	cfg.setPos( pos() );
	cfg.setSize( boundingRect().size() );

	setCfg( cfg );

	auto * dd = d_ptr();

	for( const auto & ch : std::as_const( listOfChannels() ) )
		dd->m_scene->addChannel( ch );

	QMutableMapIterator< QString,
		QMap< Key, QPair< Como::Source, SourceProps > > >
			it( dd->m_sources );

	while( it.hasNext() )
	{
		it.next();

		QMutableMapIterator< Key, QPair< Como::Source, SourceProps > > sit( it.value() );

		while( sit.hasNext() )
		{
			sit.next();

			SourcesManager::instance().syncSource( it.key(), sit.value().first,
				sit.value().second.m_registered );

			const Properties * props = PropertiesManager::instance()
				.findProperties( sit.value().first, it.key(), 0 );

			if( props )
			{
				sit.value().second.m_level = props->checkConditions( sit.value().first.value(),
					sit.value().first.type() ).level();
			}

			auto * ch = ChannelsManager::instance().channelByName( it.key() );

			if( ch )
				sit.value().second.m_connected = ch->isConnected();
		}
	}

	dd->calcCurrentValue();
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

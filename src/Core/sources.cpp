
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
#include <Core/sources.hpp>
#include <Core/channels.hpp>
#include <Core/log.hpp>
#include <Core/properties_manager.hpp>
#include <Core/sounds.hpp>

// Qt include.
#include <QMap>
#include <QList>
#include <QCoreApplication>


namespace Globe {

//
// MapValue.
//

//! Value in the map of sources.
class MapValue {
public:
	MapValue()
		:	m_registered( false )
	{
	}

	explicit MapValue( const Como::Source & source, bool registered = true )
		:	m_source( source )
		,	m_registered( registered )
	{
	}

	MapValue( const MapValue & other )
		:	m_source( other.source() )
		,	m_registered( other.isRegistered() )
	{
	}

	MapValue & operator = ( const MapValue & other )
	{
		if( this != &other )
		{
			m_source = other.source();
			m_registered = other.isRegistered();
		}

		return *this;
	}

	//! \return Source.
	Como::Source & source()
	{
		return m_source;
	}

	//! \return Source.
	const Como::Source & source() const
	{
		return m_source;
	}

	//! \return Is registered?
	bool isRegistered() const
	{
		return m_registered;
	}
	//! Set "is registered".
	void setRegistered( bool on = true )
	{
		m_registered = on;
	}

private:
	//! Source.
	Como::Source m_source;
	//! Is registered?
	bool m_registered;
}; // class MapValue

bool operator == ( const MapValue & v1, const MapValue & v2 )
{
	return v1.source() == v2.source();
}


//
// SourcesManagerPrivate
//

class SourcesManagerPrivate {
public:
	SourcesManagerPrivate( )
	{
	}

	//! \return Registered sources.
	QList< Como::Source > registeredSources( const QString & channelName )
	{
		QList< Como::Source > result;

		QMap< QString, QList< MapValue > >::ConstIterator it =
			m_map.find( channelName );

		if( it != m_map.cend() )
		{
			foreach( const MapValue & value, it.value() )
				if( value.isRegistered() )
					result.append( value.source() );
		}

		return result;
	}

	//! \return Deregistered sources.
	QList< Como::Source > deregisteredSources( const QString & channelName )
	{
		QList< Como::Source > result;

		QMap< QString, QList< MapValue > >::ConstIterator it =
			m_map.find( channelName );

		if( it != m_map.cend() )
		{
			foreach( const MapValue & value, it.value() )
				if( !value.isRegistered() )
					result.append( value.source() );
		}

		return result;
	}

	//! \return All sources.
	QList< Como::Source > allSources( const QString & channelName )
	{
		QList< Como::Source > result;

		QMap< QString, QList< MapValue > >::ConstIterator it =
			m_map.find( channelName );

		if( it != m_map.cend() )
		{
			foreach( const MapValue & value, it.value() )
				result.append( value.source() );
		}

		return result;
	}

	//! Map of registered sources.
	QMap< QString, QList< MapValue > > m_map;
}; // class SourcesManagerPrivate


//
// SourcesManager.
//

SourcesManager::SourcesManager( QObject * parent )
	:	QObject( parent )
	,	d( new SourcesManagerPrivate )
{
	connect( &ChannelsManager::instance(), &ChannelsManager::channelCreated,
		this, &SourcesManager::channelCreated );

	connect( &ChannelsManager::instance(), &ChannelsManager::channelRemoved,
		this, &SourcesManager::channelRemoved );
}

SourcesManager::~SourcesManager()
{
}

static SourcesManager * sourcesManagerInstancePointer = 0;

void
SourcesManager::cleanup()
{
	delete sourcesManagerInstancePointer;

	sourcesManagerInstancePointer = 0;
}

SourcesManager &
SourcesManager::instance()
{
	if( !sourcesManagerInstancePointer )
	{
		sourcesManagerInstancePointer = new SourcesManager;

		qAddPostRoutine( &SourcesManager::cleanup );
	}

	return *sourcesManagerInstancePointer;
}

QList< QString >
SourcesManager::channelsNames() const
{
	return d->m_map.keys();
}

QList< Como::Source >
SourcesManager::sources( const QString & channelName ) const
{
	return d->allSources( channelName );
}

QList< Como::Source >
SourcesManager::registeredSources( const QString & channelName ) const
{
	return d->registeredSources( channelName );
}

QList< Como::Source >
SourcesManager::deregisteredSources( const QString & channelName ) const
{
	return d->deregisteredSources( channelName );
}

bool
SourcesManager::syncSource( const QString & channelName,
	Como::Source & s, bool & isRegistered )
{
	if( d->m_map.contains( channelName ) )
	{
		foreach( const MapValue & v, d->m_map[ channelName ] )
		{
			if( v.source() == s )
			{
				s = v.source();
				isRegistered = v.isRegistered();

				return true;
			}
		}
	}

	return false;
}

void
SourcesManager::sourceUpdated( const Como::Source & source )
{
	Channel * channel = static_cast< Channel* > ( sender() );

	QMap< QString, QList< MapValue > >::Iterator it =
		d->m_map.find( channel->name() );

	Log::instance().writeMsgToSourcesLog( source.dateTime(),
		channel->name(), source.type(), source.name(),
		source.typeName(), source.value(), source.description() );

	if( it != d->m_map.end() )
	{
		const int index = it.value().indexOf( MapValue( source ) );

		if( index != -1 )
			it.value()[ index ] = MapValue( source );
		else
		{
			it.value().append( MapValue( source ) );

			emit newSource( source, channel->name() );
		}
	}
	else
	{
		QMap< QString, QList< MapValue > >::Iterator it =
			d->m_map.insert( channel->name(), QList< MapValue > () );

		it.value().append( MapValue( source ) );
	}

	const QString channelName = channel->name();

	const Properties * props = PropertiesManager::instance().findProperties(
		source, channelName, 0 );

	if( props )
	{
		Level level = props->checkConditions( source.value(),
			source.type() ).level();

		Sounds::instance().playSound( level, source, channelName );
	}
}

void
SourcesManager::sourceDeregistered( const Como::Source & source )
{
	Channel * channel = static_cast< Channel* > ( sender() );

	QMap< QString, QList< MapValue > >::Iterator it =
		d->m_map.find( channel->name() );

	if( it != d->m_map.end() )
	{
		const int index = it.value().indexOf( MapValue( source ) );

		if( index != -1 )
			it.value()[ index ].setRegistered( false );
		else
		{
			it.value().append( MapValue( source, false ) );

			emit newSource( source, channel->name() );
		}
	}
	else
	{
		QMap< QString, QList< MapValue > >::Iterator it =
			d->m_map.insert( channel->name(), QList< MapValue > () );

		it.value().append( MapValue( source, false ) );
	}
}

void
SourcesManager::channelCreated( Globe::Channel * channel )
{
	if( d->m_map.find( channel->name() ) == d->m_map.end() )
		d->m_map.insert( channel->name(), QList< MapValue > () );

	connect( channel, &Channel::sourceUpdated,
		this, &SourcesManager::sourceUpdated );

	connect( channel, &Channel::sourceDeregistered,
		this, &SourcesManager::sourceDeregistered );

	connect( channel, &Channel::disconnected,
		this, &SourcesManager::channelDisconnected );
}

void
SourcesManager::channelRemoved( Globe::Channel * channel )
{
	d->m_map.remove( channel->name() );

	disconnect( channel, 0, 0, 0 );
}

void
SourcesManager::channelDisconnected()
{
	Channel * channel = static_cast< Channel* > ( sender() );

	QList< MapValue > & sources = d->m_map[ channel->name() ];

	for( QList< MapValue >::Iterator it = sources.begin(),
		last = sources.end(); it != last; ++it )
			it->setRegistered( false );
}

} /* namespace Globe */


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
#include <Globe/sources.hpp>
#include <Globe/channels.hpp>

// Qt include.
#include <QtCore/QMap>
#include <QtCore/QList>


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
	SourcesManagerPrivate( ChannelsManager * channelsManager )
		:	m_channelsManager( channelsManager )
	{
	}

	//! \return Registered sources.
	QList< Como::Source > registeredSources( const QString & channelName )
	{
		QList< Como::Source > result;

		QMap< QString, QList< MapValue > >::ConstIterator it =
			m_map.find( channelName );

		if( it != m_map.end() )
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

		if( it != m_map.end() )
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

		if( it != m_map.end() )
		{
			foreach( const MapValue & value, it.value() )
				result.append( value.source() );
		}

		return result;
	}

	//! Channels manager.
	ChannelsManager * m_channelsManager;
	//! Map of registered sources.
	QMap< QString, QList< MapValue > > m_map;
}; // class SourcesManagerPrivate


//
// SourcesManager.
//

SourcesManager::SourcesManager( ChannelsManager * channelsManager,
	QObject * parent )
	:	QObject( parent )
	,	d( new SourcesManagerPrivate( channelsManager ) )
{
	connect( channelsManager, SIGNAL( channelCreated( Channel * ) ),
		this, SLOT( channelCreated( Channel * ) ) );
	connect( channelsManager, SIGNAL( channelRemoved( Channel * ) ),
		this, SLOT( channelRemoved( Channel * ) ) );
}

SourcesManager::~SourcesManager()
{
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

void
SourcesManager::sourceUpdated( const Como::Source & source )
{
	Channel * channel = qobject_cast< Channel* > ( sender() );

	QMap< QString, QList< MapValue > >::Iterator it =
		d->m_map.find( channel->name() );

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
}

void
SourcesManager::sourceDeregistered( const Como::Source & source )
{
	Channel * channel = qobject_cast< Channel* > ( sender() );

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
SourcesManager::channelCreated( Channel * channel )
{
	if( d->m_map.find( channel->name() ) == d->m_map.end() )
		d->m_map.insert( channel->name(), QList< MapValue > () );

	connect( channel, SIGNAL( sourceUpdated( const Como::Source & ) ),
		this, SLOT( sourceUpdated( const Como::Source & ) ) );

	connect( channel, SIGNAL( sourceDeregistered( const Como::Source & ) ),
		this, SLOT( sourceDeregistered( const Como::Source & ) ) );
}

void
SourcesManager::channelRemoved( Channel * channel )
{
	d->m_map.remove( channel->name() );

	disconnect( channel, 0, 0, 0 );
}

} /* namespace Globe */

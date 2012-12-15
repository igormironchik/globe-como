
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 Igor Mironchik

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
// SourcesManagerPrivate
//

class SourcesManagerPrivate {
public:
	SourcesManagerPrivate( ChannelsManager * channelsManager )
		:	m_channelsManager( channelsManager )
	{
	}

	//! Channels manager.
	ChannelsManager * m_channelsManager;
	//! Map of sources.
	QMap< QString, QList< Como::Source > > m_map;
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

QList< QString >
SourcesManager::channelsNames() const
{
	return d->m_map.keys();
}

const QList< Como::Source > &
SourcesManager::sources( const QString & channelName ) const
{
	return d->m_map[ channelName ];
}

void
SourcesManager::sourceUpdated( const Como::Source & source )
{
	Channel * channel = qobject_cast< Channel* > ( sender() );

	QMap< QString, QList< Como::Source > >::Iterator it =
		d->m_map.find( channel->name() );

	const int index = it.value().indexOf( source );

	if( index == -1 )
	{
		it.value().push_back( source );

		emit newSource( source, channel->name() );
	}
	else
	{
		it.value()[ index ].setValue( source.value() );
		it.value()[ index ].setDateTime( source.dateTime() );
	}
}

void
SourcesManager::channelCreated( Channel * channel )
{
	if( d->m_map.find( channel->name() ) == d->m_map.end() )
		d->m_map.insert( channel->name(), QList< Como::Source > () );

	connect( channel, SIGNAL( sourceUpdated( const Como::Source & ) ),
		this, SLOT( sourceUpdated( const Como::Source & ) ) );
}

void
SourcesManager::channelRemoved( Channel * channel )
{
	QMap< QString, QList< Como::Source > >::ConstIterator it =
		d->m_map.find( channel->name() );

	if( it != d->m_map.end() )
	{
		d->m_map.remove( it.key() );

		disconnect( channel, 0, 0, 0 );
	}
}

} /* namespace Globe */

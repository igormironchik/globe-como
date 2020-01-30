
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
#include <Core/channels.hpp>
#include <Core/log.hpp>

// Qt include.
#include <QTimer>
#include <QList>
#include <QThread>
#include <QMap>
#include <QMetaObject>
#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>


namespace Globe {

//
// ChannelPrivate
//

ChannelPrivate::ChannelPrivate( Channel * parent,
	const QString & name,
	const QString & address,
	quint16 port )
	:	q( parent )
	,	m_name( name )
	,	m_address( address )
	,	m_port( port )
{
}

ChannelPrivate::~ChannelPrivate()
{
}


//
// Channel
//

Channel::Channel( const QString & name,
	const QString & address, quint16 port )
	:	d( new ChannelPrivate( this, name, address, port ) )
{
	setObjectName( QString( "Channel" ) );
}

Channel::Channel( ChannelPrivate * dd )
	:	d( dd )
{
	setObjectName( QString( "Channel" ) );
}

Channel::~Channel()
{
}

const QString &
Channel::name() const
{
	return d->m_name;
}

const QString &
Channel::hostAddress() const
{
	return d->m_address;
}

quint16
Channel::portNumber() const
{
	return d->m_port;
}

void
Channel::connectToHost()
{
	connectToHostImplementation();
}

void
Channel::disconnectFromHost()
{
	disconnectFromHostImplementation();
}

void
Channel::reconnectToHost()
{
	reconnectToHostImplementation();
}

void
Channel::updateTimeout( int msecs )
{
	updateTimeoutImplementation( msecs );
}


//
// ChannelsManagerPrivate
//

class ChannelsManagerPrivate {
public:
	ChannelsManagerPrivate()
	{
	}

	//! Init.
	void init();
	//! \return All plugins.
	QStringList plugins( const QString & path ) const;

	//! Channels.
	QMap< QString, Channel* > m_channels;
	//! Plugins.
	QMap< QString, ChannelPluginInterface* > m_plugins;
}; // class ChannelsManager::ChannelsManagerPrivate

void
ChannelsManagerPrivate::init()
{
	for( const auto & path : plugins( qApp->applicationDirPath() +
		QStringLiteral( "/plugins" ) ) )
	{
		QPluginLoader loader( path );

		QObject * plugin = loader.instance();

		if( plugin )
		{
			ChannelPluginInterface * iface =
				qobject_cast< ChannelPluginInterface* > ( plugin );

			if( iface )
			{
				if( !m_plugins.contains( iface->channelType() ) )
				{
					m_plugins[ iface->channelType() ] = iface;

					Log::instance().writeMsgToEventLog( LogLevelInfo,
						QString( "Channel plugin \"%1\" loaded." )
							.arg( iface->channelType() ) );
				}
				else
				{
					Log::instance().writeMsgToEventLog( LogLevelError,
						QString( "Channel plugin \"%1\" already exists. "
							"It will be unloded." )
								.arg( iface->channelType() ) );

					loader.unload();
				}
			}
			else
				loader.unload();
		}
		else
			Log::instance().writeMsgToEventLog( LogLevelError,
				QString( "Channel plugin wasn't loaded. Error: \"%1\"" )
					.arg( loader.errorString() ) );
	}
}

QStringList
ChannelsManagerPrivate::plugins( const QString & path ) const
{
	QStringList res;

	QDir dir( path );

	const QFileInfoList files = dir.entryInfoList(
		QDir::NoDotAndDotDot | QDir::Files );

	const QFileInfoList dirs = dir.entryInfoList(
		QDir::NoDotAndDotDot | QDir::Dirs );

	foreach( const QFileInfo & i, files )
		res.append( i.absoluteFilePath() );

	foreach( const QFileInfo & i, dirs )
		res.append( plugins( i.absoluteFilePath() ) );

	return res;
}


//
// ChannelsManager
//

ChannelsManager::ChannelsManager()
	:	d( new ChannelsManagerPrivate )
{
	d->init();
}

ChannelsManager::~ChannelsManager()
{
}

static ChannelsManager * channelsManagerInstancePointer = 0;

void
ChannelsManager::cleanup()
{
	delete channelsManagerInstancePointer;

	channelsManagerInstancePointer = 0;
}

ChannelsManager &
ChannelsManager::instance()
{
	if( !channelsManagerInstancePointer )
	{
		channelsManagerInstancePointer = new ChannelsManager;

		qAddPostRoutine( &ChannelsManager::cleanup );
	}

	return *channelsManagerInstancePointer;
}

Channel *
ChannelsManager::channelByName( const QString & name ) const
{
	if( d->m_channels.contains( name ) )
		return d->m_channels[ name ];
	else
		return 0;
}


Channel *
ChannelsManager::createChannel(	const QString & name,
	const QString & hostAddress, quint16 port,
	const QString & type )
{
	Channel * ch = channelByName( name );

	if( ch )
	{
		if( ch->hostAddress() == hostAddress &&
			ch->portNumber() == port )
				return ch;
		else
			return 0;
	}

	if( d->m_plugins.contains( type ) )
	{
		if( isAddressAndPortUnique( hostAddress, port ) )
		{
			ch = d->m_plugins[ type ]->createChannel(
				name, hostAddress, port );

			d->m_channels.insert( name, ch );

			ch->activate();

			Log::instance().writeMsgToEventLog( LogLevelInfo,
				QString( "Channel created. Name \"%1\", ip \"%2\", "
						"port %3 and type \"%4\"." )
					.arg( name )
					.arg( hostAddress )
					.arg( QString::number( port ) )
					.arg( type ) );

			emit channelCreated( ch );

			return ch;
		}
		else
			return 0;
	}
	else
		return 0;
}

void
ChannelsManager::removeChannel( const QString & name )
{
	if( d->m_channels.contains( name ) )
	{
		Channel * ch = d->m_channels[ name ];

		d->m_channels.remove( name );

		ch->deactivate();

		Log::instance().writeMsgToEventLog( LogLevelInfo,
			QString( "Channel removed. Name \"%1\", ip \"%2\" and port %3." )
				.arg( name )
				.arg( ch->hostAddress() )
				.arg( QString::number( ch->portNumber() ) ) );

		emit channelRemoved( ch );

		ch->deleteLater();
	}
}

bool
ChannelsManager::isNameUnique( const QString & name )
{
	return ( !d->m_channels.contains( name ) );
}

bool
ChannelsManager::isAddressAndPortUnique( const QString & hostAddress,
	quint16 port )
{
	for( QMap< QString, Channel* >::ConstIterator it = d->m_channels.begin(),
		last = d->m_channels.end(); it != last; ++it )
	{
		if( it.value()->hostAddress() == hostAddress &&
			it.value()->portNumber() == port )
				return false;
	}

	return true;
}

QList< Channel* >
ChannelsManager::channels() const
{
	QList< Channel* > channels;

	for( QMap< QString, Channel* >::ConstIterator it = d->m_channels.begin(),
		last = d->m_channels.end(); it != last; ++it )
	{
		channels.append( it.value() );
	}

	return channels;
}

QStringList
ChannelsManager::supportedChannels() const
{
	return d->m_plugins.keys();
}

void
ChannelsManager::shutdown()
{
	for( QMap< QString, Channel* >::ConstIterator it = d->m_channels.begin(),
		last = d->m_channels.end(); it != last; ++it )
	{
		it.value()->deactivate();
		it.value()->deleteLater();
	}
}

} /* namespace Globe */

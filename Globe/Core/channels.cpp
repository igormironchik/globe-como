
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
#include <Globe/Core/channels.hpp>
#include <Globe/Core/log.hpp>

// Como include.
#include <Como/ClientSocket>

// Qt include.
#include <QTimer>
#include <QList>
#include <QThread>
#include <QMap>


namespace Globe {

//
// ChannelPrivate
//

class ChannelPrivate {
public:
	ChannelPrivate( Channel * parent,
		const QString & name,
		const QHostAddress & address,
		quint16 port )
		:	q( parent )
		,	m_name( name )
		,	m_address( address )
		,	m_port( port )
	{}

	virtual ~ChannelPrivate()
	{}

	//! Parent.
	Channel * q;
	//! Name of the channel.
	QString m_name;
	//! Host address.
	QHostAddress m_address;
	//! Port.
	quint16 m_port;
}; // class ChannelPrivate


//
// Channel
//

Channel::Channel( const QString & name,
	const QHostAddress & address, quint16 port )
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

const QHostAddress &
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
// ChannelAndThreadDeleter
//

class ChannelAndThreadDeleter
	:	public QObject
{
	Q_OBJECT

public:
	ChannelAndThreadDeleter( bool isConnected,
		QThread * thread, Como::ClientSocket * socket )
		:	m_thread( thread )
		,	m_socket( socket )
	{
		if( isConnected )
		{
			connect( m_socket, &Como::ClientSocket::disconnected,
				this, &ChannelAndThreadDeleter::jobDone );

			m_socket->disconnectFromHost();
		}
		else
			jobDone();
	}

public slots:
	void jobDone()
	{
		m_socket->disconnect();
		m_thread->disconnect();
		m_thread->quit();
		m_thread->wait();
		m_socket->deleteLater();
		m_thread->deleteLater();

		deleteLater();
	}

private:
	QThread * m_thread;
	Como::ClientSocket * m_socket;
}; // class ChannelAndThreadDeleter


//
// ComoChannelPrivate
//

class ComoChannelPrivate
	:	public ChannelPrivate
{
public:
	ComoChannelPrivate( ComoChannel * parent,
		const QString & name,
		const QHostAddress & address,
		quint16 port )
		:	ChannelPrivate( parent, name, address, port )
		,	m_thread( 0 )
		,	m_socket( 0 )
		,	m_rateTimer( 0 )
		,	m_updateTimeout( 0 )
		,	m_updateTimer( 0 )
		,	m_messagesCount( 0 )
		,	m_isConnected( false )
		,	m_isDisconnectedByUser( true )
	{}

	virtual ~ComoChannelPrivate()
	{
		ChannelAndThreadDeleter * deleter = new ChannelAndThreadDeleter(
			m_isConnected, m_thread, m_socket );

		Q_UNUSED( deleter )
	}

	void init()
	{
		m_thread = new QThread;
		m_socket = new Como::ClientSocket;

		ComoChannel * q = q_func();

		m_rateTimer = new QTimer( q );
		m_updateTimer = new QTimer( q );

		m_socket->moveToThread( m_thread );
		m_thread->start();
	}

	inline ComoChannel * q_func()
		{ return static_cast< ComoChannel* >( q ); }

	inline const ComoChannel * q_func() const
		{ return static_cast< const ComoChannel* >( q ); }


	//! Thread for the socket.
	QThread * m_thread;
	//! Socket implemetation.
	Como::ClientSocket * m_socket;
	//! Timer for updating messages rate per second.
	QTimer * m_rateTimer;
	//! Update of source's value timeout in ms.
	int m_updateTimeout;
	//! Timer for updating source's value.
	QTimer * m_updateTimer;
	//! Count of messages in the current second.
	int m_messagesCount;
	//! List of sources.
	QList< Como::Source > m_sources;
	//! Is channel in connected state?
	bool m_isConnected;
	//! Is channel was disconnected by user?
	bool m_isDisconnectedByUser;
}; // class ComoChannelPrivate


//
// ComoChannel
//

ComoChannel::ComoChannel( const QString & name,
	const QHostAddress & address, quint16 port )
	:	Channel( new ComoChannelPrivate( this, name, address, port ) )
{
	ComoChannelPrivate * d = d_func();

	d->init();

	connect( this, &ComoChannel::aboutToConnectToHost,
		d->m_socket, &Como::ClientSocket::connectTo,
		Qt::QueuedConnection );

	connect( this, &ComoChannel::aboutToDisconnectFromHost,
		d->m_socket, &Como::ClientSocket::disconnectFrom,
		Qt::QueuedConnection );

	connect( this, &ComoChannel::aboutToSendGetListOfSources,
		d->m_socket, &Como::ClientSocket::sendGetListOfSourcesMessage,
		Qt::QueuedConnection );

	connect( d->m_socket, &Como::ClientSocket::connected,
		this, &ComoChannel::socketConnected,
		Qt::QueuedConnection );

	connect( d->m_socket, &Como::ClientSocket::disconnected,
		this, &ComoChannel::socketDisconnected,
		Qt::QueuedConnection );

	connect( d->m_socket, &Como::ClientSocket::sourceHasUpdatedValue,
		this, &ComoChannel::sourceHasUpdatedValue,
		Qt::QueuedConnection );

	void ( Como::ClientSocket::*signal )( QAbstractSocket::SocketError ) =
		&Como::ClientSocket::error;

	connect( d->m_socket, signal,
		this, &ComoChannel::socketError,
		Qt::QueuedConnection );

	connect( d->m_socket, &Como::ClientSocket::sourceDeinitialized,
		this, &ComoChannel::sourceHasDeregistered,
		Qt::QueuedConnection );

	connect( d->m_rateTimer, &QTimer::timeout,
		this, &ComoChannel::updateMessagesRate );

	connect( d->m_updateTimer, &QTimer::timeout,
		this, &ComoChannel::updateSourcesValue );

	d->m_rateTimer->start( 1000 );
}

ComoChannel::~ComoChannel()
{
	ComoChannelPrivate * d = d_func();

	d->m_rateTimer->stop();
	d->m_updateTimer->stop();
}

int
ComoChannel::timeout() const
{
	const ComoChannelPrivate * d = d_func();

	return d->m_updateTimeout;
}

bool
ComoChannel::isConnected() const
{
	const ComoChannelPrivate * d = d_func();

	return d->m_isConnected;
}

bool
ComoChannel::isMustBeConnected() const
{
	const ComoChannelPrivate * d = d_func();

	return !d->m_isDisconnectedByUser;
}

void
ComoChannel::activate()
{
}

void
ComoChannel::deactivate()
{
}

void
ComoChannel::connectToHostImplementation()
{
	ComoChannelPrivate * d = d_func();

	d->m_isDisconnectedByUser = false;

	emit aboutToConnectToHost( d->m_address, d->m_port );
}

void
ComoChannel::disconnectFromHostImplementation()
{
	ComoChannelPrivate * d = d_func();

	d->m_isDisconnectedByUser = true;

	emit aboutToDisconnectFromHost();
}

void
ComoChannel::reconnectToHostImplementation()
{
	ComoChannelPrivate * d = d_func();

	d->m_isDisconnectedByUser = false;

	emit aboutToDisconnectFromHost();
}

void
ComoChannel::updateTimeoutImplementation( int msecs )
{
	ComoChannelPrivate * d = d_func();

	d->m_updateTimer->stop();

	d->m_updateTimeout = msecs;

	if( d->m_updateTimeout > 0 )
		d->m_updateTimer->start( d->m_updateTimeout );
	else
		updateSourcesValue();
}

void
ComoChannel::socketDisconnected()
{
	ComoChannelPrivate * d = d_func();

	d->m_isConnected = false;

	emit disconnected();

	if( !d->m_isDisconnectedByUser )
		emit aboutToConnectToHost( d->m_address, d->m_port );
}

void
ComoChannel::socketConnected()
{
	ComoChannelPrivate * d = d_func();

	d->m_isConnected = true;

	emit connected();

	emit aboutToSendGetListOfSources();
}

void
ComoChannel::socketError( QAbstractSocket::SocketError socketError )
{
	if( socketError != QAbstractSocket::RemoteHostClosedError )
	{
		ComoChannelPrivate * d = d_func();

		if( !d->m_isDisconnectedByUser )
			emit aboutToConnectToHost( d->m_address, d->m_port );
	}
}

void
ComoChannel::sourceHasUpdatedValue( const Como::Source & source )
{
	ComoChannelPrivate * d = d_func();

	++d->m_messagesCount;

	if( d->m_updateTimeout > 0 )
	{
		const int index = d->m_sources.indexOf( source );

		if( index != -1 )
			d->m_sources[ index ] = source;
		else
			d->m_sources.push_back( source );
	}
	else
		emit sourceUpdated( source );
}

void
ComoChannel::sourceHasDeregistered( const Como::Source & source )
{
	ComoChannelPrivate * d = d_func();

	++d->m_messagesCount;

	if( d->m_updateTimeout > 0 )
	{
		const int index = d->m_sources.indexOf( source );

		if( index != -1 )
			d->m_sources.removeAt( index );

		emit sourceDeregistered( source );
	}
	else
		emit sourceDeregistered( source );
}

void
ComoChannel::updateMessagesRate()
{
	ComoChannelPrivate * d = d_func();

	emit messagesRate( d->m_messagesCount );

	d->m_messagesCount = 0;
}

void
ComoChannel::updateSourcesValue()
{
	ComoChannelPrivate * d = d_func();

	foreach( const Como::Source & source, d->m_sources )
		emit sourceUpdated( source );

	d->m_sources.clear();
}


//
// ChannelsManagerPrivate
//

class ChannelsManagerPrivate {
public:
	ChannelsManagerPrivate()
	{
	}

	//! Channels.
	QMap< QString, Channel* > m_channels;
}; // class ChannelsManager::ChannelsManagerPrivate


//
// ChannelsManager
//

ChannelsManager::ChannelsManager()
	:	d( new ChannelsManagerPrivate )
{
}

ChannelsManager::~ChannelsManager()
{
}

ChannelsManager &
ChannelsManager::instance()
{
	static ChannelsManager inst;

	return inst;
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
	const QHostAddress & hostAddress, quint16 port,
	ChannelType type )
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

	switch( type )
	{
		case ComoChannelType :
			{
				if( isAddressAndPortUnique( hostAddress, port ) )
				{
					ch = new ComoChannel( name, hostAddress, port );

					d->m_channels.insert( name, ch );

					ch->activate();

					Log::instance().writeMsgToEventLog( LogLevelInfo,
						QString( "Channel created. Name \"%1\", ip \"%2\" and port %3." )
							.arg( name )
							.arg( hostAddress.toString() )
							.arg( QString::number( port ) ) );

					emit channelCreated( ch );

					return ch;
				}
				else
					return 0;
			}
		break;

		default :
			return 0;
	}
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
				.arg( ch->hostAddress().toString() )
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
ChannelsManager::isAddressAndPortUnique( const QHostAddress & hostAddress,
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

#include "channels.moc"

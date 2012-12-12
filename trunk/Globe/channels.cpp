
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
#include <Globe/channels.hpp>
#include <Globe/db.hpp>

// Como include.
#include <Como/ClientSocket>

// Qt include.
#include <QtCore/QTimer>
#include <QtCore/QList>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QThread>
#include <QtCore/QMap>
#include <QtCore/QEventLoop>


namespace Globe {

//
// ChannelPrivate
//

class ChannelPrivate {
public:
	ChannelPrivate( QObject * parent,
		const QString & name,
		const QHostAddress & address,
		quint16 port, DB * db )
		:	m_name( name )
		,	m_address( address )
		,	m_port( port )
		,	m_db( db )
		,	m_socket( new Como::ClientSocket( parent ) )
		,	m_rateTimer( new QTimer( parent ) )
		,	m_updateTimeout( 0 )
		,	m_updateTimer( new QTimer( parent ) )
		,	m_messagesCount( 0 )
		,	m_isConnected( false )
		,	m_isDisconnectedByUser( true )
	{}

	//! Name of the channel.
	QString m_name;
	//! Host address.
	QHostAddress m_address;
	//! Port.
	quint16 m_port;
	//! Database.
	DB * m_db;
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
	//! Mutex for guard m_updateTimeout.
	QMutex m_mutex;
	//! Is channel in connected state?
	bool m_isConnected;
	//! Is channel was disconnected by user?
	bool m_isDisconnectedByUser;
}; // class Channel::ChannelPrivate


//
// Channel
//

Channel::Channel( const QString & name,
	const QHostAddress & address, quint16 port, DB * db )
	:	d( new ChannelPrivate( this, name, address, port, db ) )
{
	setObjectName( QString( "Channel" ) );

	connect( this, SIGNAL( aboutToConnectToHost() ),
		this, SLOT( connectToHostImplementation() ),
		Qt::QueuedConnection );

	connect( this, SIGNAL( aboutToDisconnectFromHost() ),
		this, SLOT( disconnectFromHostImplementation() ),
		Qt::QueuedConnection );

	connect( this, SIGNAL( aboutToReconnectToHost() ),
		this, SLOT( reconnectToHostImplementation() ),
		Qt::QueuedConnection );

	connect( d->m_socket, SIGNAL( connected() ),
		this, SLOT( socketConnected() ) );

	connect( d->m_socket, SIGNAL( disconnected() ),
		this, SLOT( socketDisconnected() ) );

	connect( d->m_socket, SIGNAL( sourceHasUpdatedValue( const Como::Source & ) ),
		this, SLOT( sourceHasUpdatedValue( const Como::Source & ) ) );

	connect( d->m_socket, SIGNAL( error( QAbstractSocket::SocketError ) ),
		this, SLOT( socketError( QAbstractSocket::SocketError ) ) );

	connect( d->m_socket, SIGNAL( sourceDeinitialized( const Como::Source & ) ),
		this, SLOT( sourceHasDeregistered( const Como::Source & ) ) );

	connect( d->m_rateTimer, SIGNAL( timeout() ),
		this, SLOT( updateMessagesRate() ) );

	connect( d->m_updateTimer, SIGNAL( timeout() ),
		this, SLOT( updateSourcesValue() ) );

	d->m_rateTimer->start( 1000 );
}

Channel::~Channel()
{
	d->m_rateTimer->stop();
	d->m_updateTimer->stop();

	d->m_socket->disconnectFromHost();
	d->m_socket->waitForDisconnected();
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

int
Channel::timeout() const
{
	QMutexLocker lock( &d->m_mutex );

	return d->m_updateTimeout;
}

bool
Channel::isConnected() const
{
	QMutexLocker lock( &d->m_mutex );

	return d->m_isConnected;
}

bool
Channel::isMustBeConnected() const
{
	QMutexLocker lock( &d->m_mutex );

	return !d->m_isDisconnectedByUser;
}

void
Channel::connectToHost()
{
	emit aboutToConnectToHost();
}

void
Channel::disconnectFromHost()
{
	emit aboutToDisconnectFromHost();
}

void
Channel::reconnectToHost()
{
	emit aboutToReconnectToHost();
}

void
Channel::updateTimeout( int msecs )
{
	QMutexLocker lock( &d->m_mutex );

	d->m_updateTimeout = msecs;

	d->m_updateTimer->stop();

	if( d->m_updateTimeout > 0 )
		d->m_updateTimer->start( d->m_updateTimeout );
	else
		updateSourcesValue();
}

void
Channel::connectToHostImplementation()
{
	{
		QMutexLocker lock( &d->m_mutex );

		d->m_isDisconnectedByUser = false;
	}

	if( d->m_socket->state() == QAbstractSocket::UnconnectedState )
		d->m_socket->connectToHost( d->m_address, d->m_port );
}

void
Channel::disconnectFromHostImplementation()
{
	{
		QMutexLocker lock( &d->m_mutex );

		d->m_isDisconnectedByUser = true;
	}

	if( d->m_socket->state() != QAbstractSocket::UnconnectedState )
		d->m_socket->disconnectFromHost();
}

void
Channel::reconnectToHostImplementation()
{
	{
		QMutexLocker lock( &d->m_mutex );

		d->m_isDisconnectedByUser = false;
	}

	if( d->m_socket->state() != QAbstractSocket::UnconnectedState )
		d->m_socket->disconnectFromHost();
}

void
Channel::socketDisconnected()
{
	{
		QMutexLocker lock( &d->m_mutex );

		d->m_isConnected = false;
	}

	emit disconnected();

	{
		QMutexLocker lock( &d->m_mutex );

		if( !d->m_isDisconnectedByUser )
			d->m_socket->connectToHost( d->m_address, d->m_port );
	}
}

void
Channel::socketConnected()
{
	{
		QMutexLocker lock( &d->m_mutex );

		d->m_isConnected = true;
	}

	emit connected();

	d->m_socket->sendGetListOfSourcesMessage();
}

void
Channel::socketError( QAbstractSocket::SocketError socketError )
{
	Q_UNUSED( socketError )

	{
		QMutexLocker lock( &d->m_mutex );

		if( !d->m_isDisconnectedByUser )
			d->m_socket->connectToHost( d->m_address, d->m_port );
	}
}

void
Channel::sourceHasUpdatedValue( const Como::Source & source )
{
	++d->m_messagesCount;

	QMutexLocker lock( &d->m_mutex );

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
Channel::sourceHasDeregistered( const Como::Source & source )
{
	++d->m_messagesCount;

	QMutexLocker lock( &d->m_mutex );

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
Channel::updateMessagesRate()
{
	emit messagesRate( d->m_messagesCount );

	d->m_messagesCount = 0;
}

void
Channel::updateSourcesValue()
{
	foreach( const Como::Source & source, d->m_sources )
		emit sourceUpdated( source );

	d->m_sources.clear();
}


//
// ChannelAndThread
//

//! Thread for channel.
class ChannelAndThread
{
public:
	ChannelAndThread()
		:	m_channel( 0 )
		,	m_thread( 0 )
	{
	}

	ChannelAndThread( Channel * channel, QThread * thread )
		:	m_channel( channel )
		,	m_thread( thread )
	{
	}

	ChannelAndThread( const ChannelAndThread & other )
		:	m_channel( other.channel() )
		,	m_thread( other.thread() )
	{
	}

	ChannelAndThread & operator = ( const ChannelAndThread & other )
	{
		if( this != &other )
		{
			m_channel = other.channel();
			m_thread = other.thread();
		}

		return *this;
	}

	//! \return Channel.
	Channel * channel() const
	{
		return m_channel;
	}

	//! \return Thread.
	QThread * thread() const
	{
		return m_thread;
	}

private:
	//! Channel.
	Channel * m_channel;
	//! Thread.
	QThread * m_thread;
}; // class ChannelThread


//
// ChannelsManagerPrivate
//

class ChannelsManagerPrivate {
public:
	explicit ChannelsManagerPrivate( DB * db )
		:	m_db( db )
	{}

	//! Database.
	DB * m_db;
	//! Channels.
	QMap< QString, ChannelAndThread > m_channels;
}; // class ChannelsManager::ChannelsManagerPrivate


//
// ChannelsManager
//

ChannelsManager::ChannelsManager( DB * db )
	:	d( new ChannelsManagerPrivate( db ) )
{
}

ChannelsManager::~ChannelsManager()
{
	for( QMap< QString, ChannelAndThread >::Iterator it = d->m_channels.begin(),
		last = d->m_channels.end(); it != last; ++it )
	{
		it.value().thread()->quit();
		it.value().thread()->wait();
		it.value().channel()->deleteLater();
		it.value().thread()->deleteLater();
	}
}


Channel *
ChannelsManager::channelByName( const QString & name ) const
{
	if( d->m_channels.contains( name ) )
		return d->m_channels[ name ].channel();
	else
		return 0;
}


Channel *
ChannelsManager::createChannel(	const QString & name,
	const QHostAddress & hostAddress, quint16 port )
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
	else if( isAddressAndPortUnique( hostAddress, port ) )
	{
		ch = new Channel( name, hostAddress, port, d->m_db );

		QThread * thread = new QThread( this );
		ch->moveToThread( thread );
		d->m_channels.insert( name, ChannelAndThread( ch, thread ) );
		thread->start();

		emit channelCreated( ch );

		return ch;
	}
	else
		return 0;
}


//
// ChannelAndThreadDeleter
//

class ChannelAndThreadDeleter
	:	public QObject
{
	Q_OBJECT

public:
	ChannelAndThreadDeleter( const ChannelAndThread & channelAndThread )
		:	m_channelAndThread( channelAndThread )
	{
		if( m_channelAndThread.channel()->isConnected() )
			connect( m_channelAndThread.channel(), SIGNAL( disconnected() ),
				this, SLOT( jobDone() ) );
		else
			jobDone();
	}

public slots:
	void jobDone()
	{
		m_channelAndThread.channel()->disconnect();
		m_channelAndThread.thread()->disconnect();
		m_channelAndThread.thread()->quit();
		m_channelAndThread.thread()->wait();
		m_channelAndThread.channel()->deleteLater();
		m_channelAndThread.thread()->deleteLater();

		deleteLater();
	}

private:
	ChannelAndThread m_channelAndThread;
}; // class ChannelAndThreadDeleter

void
ChannelsManager::removeChannel( const QString & name )
{
	if( d->m_channels.contains( name ) )
	{
		ChannelAndThread channelAndThread = d->m_channels[ name ];
		d->m_channels.remove( name );

		ChannelAndThreadDeleter * deleter = new ChannelAndThreadDeleter(
			channelAndThread );

		Q_UNUSED( deleter )

		channelAndThread.channel()->disconnectFromHost();

		emit channelRemoved( channelAndThread.channel() );
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
	for( QMap< QString, ChannelAndThread >::ConstIterator it = d->m_channels.begin(),
		last = d->m_channels.end(); it != last; ++it )
	{
		if( it.value().channel()->hostAddress() == hostAddress &&
			it.value().channel()->portNumber() == port )
				return false;
	}

	return true;
}

QList< Channel* >
ChannelsManager::channels() const
{
	QList< Channel* > channels;

	for( QMap< QString, ChannelAndThread >::ConstIterator it = d->m_channels.begin(),
		last = d->m_channels.end(); it != last; ++it )
	{
		channels.append( it.value().channel() );
	}

	return channels;
}

} /* namespace Globe */

#include "channels.moc"

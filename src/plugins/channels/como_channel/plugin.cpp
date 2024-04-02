
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Core include.
#include <Core/channels.hpp>

// Como include.
#include <Como/ClientSocket>

// Qt include.
#include <QThread>
#include <QTimer>
#include <QHostAddress>


namespace Globe {

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

			QMetaObject::invokeMethod( m_socket, "disconnectFrom",
				Qt::QueuedConnection );
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


class ComoChannel;

//
// ComoChannelPrivate
//

class ComoChannelPrivate
	:	public ChannelPrivate
{
public:
	ComoChannelPrivate( ComoChannel * parent,
		const QString & name,
		const QString & address,
		quint16 port );

	~ComoChannelPrivate();

	//! Init.
	void init();

	inline ComoChannel * q_func();

	inline const ComoChannel * q_func() const;


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

/*!
	Como channel in the Globe.
*/
class ComoChannel
	:	public Channel
{
	Q_OBJECT

signals:
	//! About to connect to host.
	void aboutToConnectToHost( const QHostAddress &, quint16 );
	//! About to disconnect from host.
	void aboutToDisconnectFromHost();
	//! About to send "GetListOfSources" message.
	void aboutToSendGetListOfSources();

public:
	/*!
		New channel will not connected to the host automaticaly.
		You should call connectToHost() manually.
	*/
	ComoChannel(
		//! Name of the channel.
		const QString & name,
		//! Host address.
		const QString & address,
		//! Port.
		quint16 port );

	~ComoChannel();

	//! \return Timeout in the channel.
	int timeout() const;
	//! \return Is channel in connected state.
	bool isConnected() const;
	//! \return Whether the user wants to make this channel connected.
	bool isMustBeConnected() const;
	//! \return Type of the channel.
	const QString & channelType() const;

protected:
	//! Activate channel.
	void activate();
	//! Deactivate channel.
	void deactivate();

	//! Implementation of the "connect to host" operation.
	void connectToHostImplementation();
	//! Implementation of the "Disconnect from host" operation.
	void disconnectFromHostImplementation();
	//! Implementation of the "reconnect to host" operation.
	void reconnectToHostImplementation();
	//! Implementation of the "update timeout" operation.
	void updateTimeoutImplementation( int msecs );

private slots:
	//! Socket implementation has been disconnected.
	void socketDisconnected();
	//! Socket implementation has been connected.
	void socketConnected();
	//! Como::Source has updated his value.
	void sourceHasUpdatedValue( const Como::Source & source );
	//! Como::Source has deregistered.
	void sourceHasDeregistered( const Como::Source & source );
	//! Update messages rate timer shots.
	void updateMessagesRate();
	//! Update source's values timer shots.
	void updateSourcesValue();
	//! Socket's error.
	void socketError( QAbstractSocket::SocketError socketError );

private:
	Q_DISABLE_COPY( ComoChannel )

	friend class ComoChannelPrivate;

	inline ComoChannelPrivate * d_func()
		{ return static_cast< ComoChannelPrivate* > ( d.data() ); }
	inline const ComoChannelPrivate * d_func() const
		{ return static_cast< const ComoChannelPrivate* >( d.data() ); }
}; // class ComoChannel


//
// ComoChannelPrivate
//


ComoChannelPrivate::ComoChannelPrivate( ComoChannel * parent,
	const QString & name,
	const QString & address,
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

ComoChannelPrivate::~ComoChannelPrivate()
{
	ChannelAndThreadDeleter * deleter = new ChannelAndThreadDeleter(
		m_isConnected, m_thread, m_socket );

	Q_UNUSED( deleter )
}

void
ComoChannelPrivate::init()
{
	m_thread = new QThread;
	m_socket = new Como::ClientSocket;

	ComoChannel * q = q_func();

	m_rateTimer = new QTimer( q );
	m_updateTimer = new QTimer( q );

	m_socket->moveToThread( m_thread );
	m_thread->start();
}

inline ComoChannel *
ComoChannelPrivate::q_func()
{
	return static_cast< ComoChannel* >( q );
}

inline const ComoChannel *
ComoChannelPrivate::q_func() const
{
	return static_cast< const ComoChannel* >( q );
}


//
// ComoChannel
//

ComoChannel::ComoChannel( const QString & name,
	const QString & address, quint16 port )
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

	connect( d->m_socket, &Como::ClientSocket::errorOccurred,
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

static const QString c_comoChannelType = QStringLiteral( "como" );

const QString &
ComoChannel::channelType() const
{
	return c_comoChannelType;
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

	emit aboutToConnectToHost( QHostAddress( d->m_address ), d->m_port );
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
		emit aboutToConnectToHost( QHostAddress( d->m_address ), d->m_port );
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
			emit aboutToConnectToHost( QHostAddress( d->m_address ), d->m_port );
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
// ComoChannelPlugin
//

//! Plugin.
class ComoChannelPlugin
	:	public QObject
	,	public ChannelPluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA( IID "Globe.ChannelPluginInterface.Como" )
	Q_INTERFACES( Globe::ChannelPluginInterface )

public:
	ComoChannelPlugin()
	{
		qRegisterMetaType< QHostAddress > ( "QHostAddress" );
	}

	~ComoChannelPlugin()
	{
	}

	Channel * createChannel(
		//! Name of the channel
		const QString & name,
		//! Host address.
		const QString & hostAddress,
		//! Port.
		quint16 port ) const
	{
		QHostAddress addr( hostAddress );

		if( !addr.isNull() )
			return ( new ComoChannel( name, hostAddress, port ) );
		else
			return Q_NULLPTR;
	}

	QString channelType() const
	{
		return c_comoChannelType;
	}
}; // class ComoChannelPlugin

} /* namespace Globe */

#include "plugin.moc"

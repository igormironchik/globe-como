
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Como include.
#include <Como/ClientSocket>
#include <Como/private/Buffer>
#include <Como/private/Protocol>
#include <Como/private/Messages>


namespace Como {

//
// ClientSocket::ClientSocketPrivate
//

struct ClientSocket::ClientSocketPrivate {
	//! Buffer.
	Buffer m_buf;
}; // struct ClientSocket::ClientSocketPrivate


//
// ClientSocket
//

ClientSocket::ClientSocket( QObject * parent )
	:	QTcpSocket( parent )
	,	d( new ClientSocketPrivate )
{
	connect( this, &ClientSocket::readyRead,
		this, &ClientSocket::slotReadyRead );
}

ClientSocket::~ClientSocket()
{
}

void
ClientSocket::connectTo( const QHostAddress & address, quint16 port )
{
	if( state() == QAbstractSocket::UnconnectedState )
		connectToHost( address, port );
}

void
ClientSocket::disconnectFrom()
{
	if( state() != QAbstractSocket::UnconnectedState )
		disconnectFromHost();
}

void
ClientSocket::sendSourceMessage( const Como::Source & source )
{
	SourceMessage msg( source );

	QSharedPointer< QByteArray > data = Protocol::writeMessage( msg );

	write( *data );

	flush();
}

void
ClientSocket::sendGetListOfSourcesMessage()
{
	GetListOfSourcesMessage msg;

	QSharedPointer< QByteArray > data = Protocol::writeMessage( msg );

	write( *data );

	flush();
}

void
ClientSocket::sendDeinitSourceMessage( const Como::Source & source )
{
	DeinitSourceMessage msg( source );

	QSharedPointer< QByteArray > data = Protocol::writeMessage( msg );

	write( *data );

	flush();
}

void
ClientSocket::slotReadyRead()
{
	d->m_buf.write( readAll() );

	try {
		while( !d->m_buf.isEmpty() )
		{
			int bytesRead = 0;

			QSharedPointer< Message > msg =
				Protocol::readMessage( d->m_buf.data(), bytesRead );

			d->m_buf.remove( bytesRead );

			if( msg.data() )
			{
				switch( msg->type() )
				{
					case GetListOfSourcesMessage::messageType :
					{
						emit getListOfSourcesMessageReceived();
					} break;

					case SourceMessage::messageType :
					{
						SourceMessage * sourceMsg =
							static_cast< SourceMessage* > ( msg.data() );

						emit sourceHasUpdatedValue( sourceMsg->source() );
					} break;

					case DeinitSourceMessage::messageType :
					{
						DeinitSourceMessage * deinitMsg =
							static_cast< DeinitSourceMessage* > ( msg.data() );

						emit sourceDeinitialized( deinitMsg->source() );
					} break;
				}
			}
		}
	}
	catch( const NotEnoughDataReceivedException & )
	{
	}
	catch( const GarbageReceivedException & )
	{
		handleErrorInReadMessage();
	}
	catch( const ProtocolException & )
	{
		handleErrorInReadMessage();
	}
}

void
ClientSocket::handleErrorInReadMessage()
{
	d->m_buf.clear();
	close();
}

} /* namespace Como */

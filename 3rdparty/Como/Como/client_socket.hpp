
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef COMO__CLIENT_SOCKET_HPP__INCLUDED
#define COMO__CLIENT_SOCKET_HPP__INCLUDED

// Qt include.
#include <QTcpSocket>
#include <QScopedPointer>


namespace Como {

class Source;


//
// ClientSocket
//

/*!
	Client socket. This type of socket designed to provide
	information about Source changes on the server
	side from ServerSocket.

	Don't forget register Source meta-type information in Qt with:

	\code
	qRegisterMetaType< Como::Source > ( "Como::Source" );
	\endcode
*/
class ClientSocket
	:	public QTcpSocket
{
	Q_OBJECT

signals:
	//! Source has updated his value.
	void sourceHasUpdatedValue( const Como::Source & );
	//! GetListOfSourcesMessage request received
	void getListOfSourcesMessageReceived();
	//! De-initialization of the source.
	void sourceDeinitialized( const Como::Source & );

public:
	ClientSocket( QObject * parent = 0 );
	~ClientSocket();

public slots:
	//! Connect to host.
	void connectTo( const QHostAddress & address, quint16 port );

	//! Disconnect from host.
	void disconnectFrom();

	//! Send information about source.
	void sendSourceMessage( const Como::Source & source );

	//! Send request to receive all available sources.
	void sendGetListOfSourcesMessage();

	//! Send information about de-initialization of the source.
	void sendDeinitSourceMessage( const Como::Source & source );

private:
	//! Handle errors in read message.
	void handleErrorInReadMessage();

private slots:
	//! New data available.
	void slotReadyRead();

private:
	struct ClientSocketPrivate;
	QScopedPointer< ClientSocketPrivate > d;
}; // class ClientSocket

} /* namespace Como */

#endif // COMO__CLIENT_SOCKET_HPP__INCLUDED

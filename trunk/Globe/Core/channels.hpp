
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

#ifndef GLOBE__CHANNELS_HPP__INCLUDED
#define GLOBE__CHANNELS_HPP__INCLUDED

// Qt include.
#include <QObject>
#include <QScopedPointer>
#include <QString>
#include <QHostAddress>
#include <QList>

// Como include.
#include <Como/Source>


namespace Globe {

class ChannelPrivate;

//
// Channel
//

/*!
	Channel in the Globe.

	Channel will live in the separate thread.
*/
class Channel
	:	public QObject
{
	Q_OBJECT

signals:
	//! New source or update.
	void sourceUpdated( const Como::Source & );
	//! Source deregistered.
	void sourceDeregistered( const Como::Source & );
	//! Connected to host.
	void connected();
	//! Disconnected from host.
	void disconnected();
	//! About to connect to host.
	void aboutToConnectToHost();
	//! About to disconnect from host.
	void aboutToDisconnectFromHost();
	//! About to reconnect to host.
	void aboutToReconnectToHost();
	//! About to change update timeout.
	void aboutToChangeUpdateTimeout();
	//! Rate of the messages per second.
	void messagesRate( int );

public:
	/*!
		New channel will not connected to the host automaticaly.
		You should call connectToHost() manually.
	*/
	Channel(
		//! Name of the channel.
		const QString & name,
		//! Host address.
		const QHostAddress & address,
		//! Port.
		quint16 port );

	~Channel();

	//! \return Name of the channel.
	const QString & name() const;
	//! \return Host address.
	const QHostAddress & hostAddress() const;
	//! \return Port.
	quint16 portNumber() const;
	//! \return Timeout in the channel.
	int timeout() const;
	//! \return Is channel in connected state.
	bool isConnected() const;
	//! \return Whether the user wants to make this channel connected.
	bool isMustBeConnected() const;

public slots:
	//! Forcibly connect to host.
	void connectToHost();
	//! Disconnect from host.
	void disconnectFromHost();
	//! Reconnect to host. I.e. disconnect and then connect again.
	void reconnectToHost();
	/*!
		Set timeout between refreshing of the Como::Source values.

		It's mean that if one source will refresh his value more than
		one in the given period then only one actual refresh will be
		send out with the sourceUpdated() signal. It's very helpfull
		for decreasing load of the application.
	*/
	void updateTimeout(
		//! Timeout in milliseconds.
		int msecs );

private slots:
	//! Forcibly connect to host.
	void connectToHostImplementation();
	//! Disconnect from host.
	void disconnectFromHostImplementation();
	//! Reconnect to host. I.e. disconnect and then connect again.
	void reconnectToHostImplementation();
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
	//! Change update timeout.
	void changeUpdateTimeoutImplementation();

private:
	Q_DISABLE_COPY( Channel )

	QScopedPointer< ChannelPrivate > d;
}; // class Channel


class ChannelsManagerPrivate;

//
// ChannelsManager
//

//! Channel's manager.
class ChannelsManager
	:	public QObject
{
	Q_OBJECT

signals:
	//! New channel created.
	void channelCreated( Channel * );
	//! Channel was removed.
	void channelRemoved( Channel * );

private:
	ChannelsManager();

	~ChannelsManager();

public:
	//! \return Instance.
	static ChannelsManager & instance();

	/*!
		\return Channel by it's name.
		If there is no channel with the given \a name
		then NULL will be returned.
	*/
	Channel * channelByName( const QString & name ) const;

	/*!
		Create channel with the given parameters.

		If there is channel with the given parameters present
		then new channel will not created and return pointer
		to the exciting channel immediately.

		If there is channel with the given \a name but with
		different \a hostAddress and/or \a port then new channel
		will not created and NULL will be returned.

		\note New channel will not connected to the host.
		You should call Channel::connectToHost() manually.

		\note Channel's name must be unique.
	*/
	Channel * createChannel(
		//! Name of the channel
		const QString & name,
		//! Host address.
		const QHostAddress & hostAddress,
		//! Port.
		quint16 port );

	//! Remove channel.
	void removeChannel( const QString & name );

	//! \return Is name of the channel unique.
	bool isNameUnique( const QString & name );

	//! \return Is given \a hostAddress and \a port unique.
	bool isAddressAndPortUnique( const QHostAddress & hostAddress,
		quint16 port );

	//! \return All available channels.
	QList< Channel* > channels() const;

private:
	Q_DISABLE_COPY( ChannelsManager )

	QScopedPointer< ChannelsManagerPrivate > d;
}; // class ChannelsManager

} /* namespace Globe */

#endif // GLOBE__CHANNELS_HPP__INCLUDED

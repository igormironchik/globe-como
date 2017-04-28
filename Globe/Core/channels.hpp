
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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

#ifndef GLOBE__CHANNELS_HPP__INCLUDED
#define GLOBE__CHANNELS_HPP__INCLUDED

// Qt include.
#include <QObject>
#include <QScopedPointer>
#include <QString>
#include <QList>
#include <QtPlugin>

// Como include.
#include <Como/Source>

// Globe include.
#include <Globe/Core/export.hpp>


namespace Globe {

class Channel;


//
// ChannelPluginInterface
//

//! Interface of the channel plugin.
class CORE_EXPORT ChannelPluginInterface {
public:
	virtual ~ChannelPluginInterface() {}

	virtual Channel * createChannel(
		//! Name of the channel
		const QString & name,
		//! Host address.
		const QString & hostAddress,
		//! Port.
		quint16 port ) const = 0;

	//! \return Channel type.
	virtual QString channelType() const = 0;
}; // class ChannelPluginInterface


//
// ChannelPrivate
//

class CORE_EXPORT ChannelPrivate {
public:
	ChannelPrivate( Channel * parent,
		const QString & name,
		const QString & address,
		quint16 port );

	virtual ~ChannelPrivate();

	//! Parent.
	Channel * q;
	//! Name of the channel.
	QString m_name;
	//! Host address.
	QString m_address;
	//! Port.
	quint16 m_port;
}; // class ChannelPrivate


//
// Channel
//

/*!
	Interface of the channel in the Globe.
*/
class CORE_EXPORT Channel
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
	//! Rate of the messages per second.
	void messagesRate( int );

public:
	Channel(
		//! Name of the channel.
		const QString & name,
		//! Host address.
		const QString & address,
		//! Port.
		quint16 port );

	virtual ~Channel();

	//! \return Name of the channel.
	const QString & name() const;
	//! \return Host address.
	const QString & hostAddress() const;
	//! \return Port.
	quint16 portNumber() const;
	//! \return Timeout in the channel.
	virtual int timeout() const = 0;
	//! \return Is channel in connected state.
	virtual bool isConnected() const = 0;
	//! \return Whether the user wants to make this channel connected.
	virtual bool isMustBeConnected() const = 0;
	//! \return Type of the channel.
	virtual const QString & channelType() const = 0;

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

protected:
	friend class ChannelsManager;

	//! Activate channel.
	virtual void activate() = 0;
	//! Deactivate channel.
	virtual void deactivate() = 0;

	//! Implementation of the "connect to host" operation.
	virtual void connectToHostImplementation() = 0;
	//! Implementation of the "Disconnect from host" operation.
	virtual void disconnectFromHostImplementation() = 0;
	//! Implementation of the "reconnect to host" operation.
	virtual void reconnectToHostImplementation() = 0;
	//! Implementation of the "update timeout" operation.
	virtual void updateTimeoutImplementation( int msecs ) = 0;

	Channel(
		//! Channel private.
		ChannelPrivate * dd );

protected:
	QScopedPointer< ChannelPrivate > d;

private:
	Q_DISABLE_COPY( Channel )
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

	static void cleanup();

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
		const QString & hostAddress,
		//! Port.
		quint16 port,
		//! Type of the channel.
		const QString & channelType );

	//! Remove channel.
	void removeChannel( const QString & name );

	//! \return Is name of the channel unique.
	bool isNameUnique( const QString & name );

	//! \return Is given \a hostAddress and \a port unique.
	bool isAddressAndPortUnique( const QString & hostAddress,
		quint16 port );

	//! \return All available channels.
	QList< Channel* > channels() const;

	//! \return All supported types of channels.
	QStringList supportedChannels() const;

	//! Shutdown all channels.
	void shutdown();

private:
	Q_DISABLE_COPY( ChannelsManager )

	QScopedPointer< ChannelsManagerPrivate > d;
}; // class ChannelsManager

} /* namespace Globe */

#define ChannelPluginInterface_iid "Globe.ChannelPluginInterface"

Q_DECLARE_INTERFACE( Globe::ChannelPluginInterface, ChannelPluginInterface_iid )

#endif // GLOBE__CHANNELS_HPP__INCLUDED

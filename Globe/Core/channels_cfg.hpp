
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

#ifndef GLOBE__CHANNELS_CFG_HPP__INCLUDED
#define GLOBE__CHANNELS_CFG_HPP__INCLUDED

// QtConfFile include.
#include <QtConfFile/TagScalar>
#include <QtConfFile/TagNoValue>
#include <QtConfFile/ConstraintMinMax>
#include <QtConfFile/TagVectorOfTags>
#include <QtConfFile/ConstraintOneOf>

// Qt include.
#include <QHostAddress>
#include <QString>
#include <QList>

// Globe include.
#include <Globe/Core/channels.hpp>


namespace Globe {

//
// ChannelCfg
//

//! COnfiguration of the channel.
class ChannelCfg {
public:
	ChannelCfg();

	ChannelCfg( const QString & name, const QHostAddress & address,
		quint16 port, bool isMustBeConnected, int timeout,
		const QString & type );

	ChannelCfg( const ChannelCfg & other );

	ChannelCfg & operator = ( const ChannelCfg & other );

	//! \return Name of the channel.
	const QString & name() const;
	//! Set name of the channel.
	void setName( const QString & name );

	//! \return IP address of the channel.
	const QHostAddress & address() const;
	//! Set address of the channel.
	void setAddress( const QHostAddress & address );

	//! \return Port of the channel.
	quint16 port() const;
	//! Set port of the channel.
	void setPort( quint16 port );

	//! \return Whether the channel must be connected.
	bool isMustBeConnected() const;
	//! Set whether the channel must be connected.
	void setMustBeConnected( bool on = true );

	//! \return Timeout in the channel.
	int timeout() const;
	//! Set timeout in the channel.
	void setTimeout( int t );

	//! \return Type of the channel.
	const QString & channelType() const;
	//! Set channel's type.
	void setChannelType( const QString & type );

private:
	//! Name of the channel.
	QString m_name;
	//! Address of the channel.
	QHostAddress m_address;
	//! Port of the channel.
	quint16 m_port;
	//! Whether the channel must be connected.
	bool m_isMustBeConnected;
	//! Timeout in the channel.
	int m_timeout;
	//! Type of the channel.
	QString m_type;
}; // class ChannelCfg


//! List with all channel's configurations.
typedef QList< ChannelCfg > AvailableChannelsCfg;


//
// ChannelTag
//

//! Tag with channel in the configuration.
class ChannelTag
	:	public QtConfFile::TagScalar< QString >
{
public:
	explicit ChannelTag( const QString & name, bool isMandatory = false );

	ChannelTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	ChannelTag( const ChannelCfg & cfg, QtConfFile::Tag & owner,
		const QString & name, bool isMandatory = false );

	ChannelTag( const ChannelCfg & cfg,
		const QString & name, bool isMandatory = false );

	~ChannelTag();

	//! \return Configuration.
	ChannelCfg cfg() const;

private:
	//! Address of the channel.
	QtConfFile::TagScalar< QString > m_address;
	//! Port of the channel.
	QtConfFile::TagScalar< int > m_port;
	//! Constraint for the port's values.
	QtConfFile::ConstraintMinMax< int > m_portConstraint;
	//! Whether the channel must be connected.
	QtConfFile::TagNoValue m_isMustBeConnected;
	//! Timeout in the channel.
	QtConfFile::TagScalar< int > m_timeout;
	//! Consatrint for the timeout.
	QtConfFile::ConstraintMinMax< int > m_timeoutConstraint;
	//! Channel's type.
	QtConfFile::TagScalar< QString > m_type;
}; // class ChannelTag


//
// AvailableChannelsCfgTag
//

//! Tag with all available channel's configuration.
class AvailableChannelsCfgTag
	:	public QtConfFile::TagNoValue
{
public:
	AvailableChannelsCfgTag();

	explicit AvailableChannelsCfgTag( const AvailableChannelsCfg & cfg );

	//! \return Channel's configuration.
	AvailableChannelsCfg cfg() const;

private:
	//! Channels.
	QtConfFile::TagVectorOfTags< ChannelTag > m_channels;
}; // class AvailableChannelsCfgTag

} /* namespace Globe */

#endif // GLOBE__CHANNELS_CFG_HPP__INCLUDED

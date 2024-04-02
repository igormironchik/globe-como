
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__CHANNELS_CFG_HPP__INCLUDED
#define GLOBE__CHANNELS_CFG_HPP__INCLUDED

// cfgfile include.
#include <cfgfile/all.hpp>

// Qt include.
#include <QString>
#include <QList>

// Globe include.
#include <Core/channels.hpp>


namespace Globe {

//
// ChannelCfg
//

//! COnfiguration of the channel.
class ChannelCfg {
public:
	ChannelCfg();

	ChannelCfg( const QString & name, const QString & address,
		quint16 port, bool isMustBeConnected, int timeout,
		const QString & type );

	ChannelCfg( const ChannelCfg & other );

	ChannelCfg & operator = ( const ChannelCfg & other );

	//! \return Name of the channel.
	const QString & name() const;
	//! Set name of the channel.
	void setName( const QString & name );

	//! \return IP address of the channel.
	const QString & address() const;
	//! Set address of the channel.
	void setAddress( const QString & address );

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
	QString m_address;
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
	:	public cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t >
{
public:
	explicit ChannelTag( const QString & name, bool isMandatory = false );

	ChannelTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	ChannelTag( const ChannelCfg & cfg,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	ChannelTag( const ChannelCfg & cfg,
		const QString & name, bool isMandatory = false );

	~ChannelTag();

	//! \return Configuration.
	ChannelCfg cfg() const;

private:
	//! Address of the channel.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_address;
	//! Port of the channel.
	cfgfile::tag_scalar_t< int, cfgfile::qstring_trait_t > m_port;
	//! Constraint for the port's values.
	cfgfile::constraint_min_max_t< int > m_portConstraint;
	//! Whether the channel must be connected.
	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > m_isMustBeConnected;
	//! Timeout in the channel.
	cfgfile::tag_scalar_t< int, cfgfile::qstring_trait_t > m_timeout;
	//! Consatrint for the timeout.
	cfgfile::constraint_min_max_t< int > m_timeoutConstraint;
	//! Channel's type.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_type;
}; // class ChannelTag


//
// AvailableChannelsCfgTag
//

//! Tag with all available channel's configuration.
class AvailableChannelsCfgTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	AvailableChannelsCfgTag();

	explicit AvailableChannelsCfgTag( const AvailableChannelsCfg & cfg );

	//! \return Channel's configuration.
	AvailableChannelsCfg cfg() const;

private:
	//! Channels.
	cfgfile::tag_vector_of_tags_t< ChannelTag, cfgfile::qstring_trait_t > m_channels;
}; // class AvailableChannelsCfgTag

} /* namespace Globe */

#endif // GLOBE__CHANNELS_CFG_HPP__INCLUDED


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/channels_cfg.hpp>


namespace Globe {

//
// ChannelCfg
//

ChannelCfg::ChannelCfg()
	:	m_port( 0 )
	,	m_isMustBeConnected( false )
	,	m_timeout( 0 )
{
}

ChannelCfg::ChannelCfg( const QString & name, const QString & address,
	quint16 port, bool isMustBeConnected, int timeout,
	const QString & type )
	:	m_name( name )
	,	m_address( address )
	,	m_port( port )
	,	m_isMustBeConnected( isMustBeConnected )
	,	m_timeout( timeout )
	,	m_type( type )
{
}

ChannelCfg::ChannelCfg( const ChannelCfg & other )
	:	m_name( other.name() )
	,	m_address( other.address() )
	,	m_port( other.port() )
	,	m_isMustBeConnected( other.isMustBeConnected() )
	,	m_timeout( other.timeout() )
	,	m_type( other.channelType() )
{
}

ChannelCfg &
ChannelCfg::operator = ( const ChannelCfg & other )
{
	if( this != & other )
	{
		m_name = other.name();
		m_address = other.address();
		m_port = other.port();
		m_isMustBeConnected = other.isMustBeConnected();
		m_timeout = other.timeout();
		m_type = other.channelType();
	}

	return *this;
}


const QString &
ChannelCfg::name() const
{
	return m_name;
}

void
ChannelCfg::setName( const QString & name )
{
	m_name = name;
}

const QString &
ChannelCfg::address() const
{
	return m_address;
}

void
ChannelCfg::setAddress( const QString & address )
{
	m_address = address;
}

quint16
ChannelCfg::port() const
{
	return m_port;
}

void
ChannelCfg::setPort( quint16 port )
{
	m_port = port;
}

bool
ChannelCfg::isMustBeConnected() const
{
	return m_isMustBeConnected;
}

void
ChannelCfg::setMustBeConnected( bool on )
{
	m_isMustBeConnected = on;
}

int
ChannelCfg::timeout() const
{
	return m_timeout;
}

void
ChannelCfg::setTimeout( int t )
{
	m_timeout = t;
}

const QString &
ChannelCfg::channelType() const
{
	return m_type;
}

void
ChannelCfg::setChannelType( const QString & type )
{
	m_type = type;
}


//
// ChannelTag
//

ChannelTag::ChannelTag( const QString & name, bool isMandatory )
	:	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > ( name, isMandatory )
	,	m_address( *this, QLatin1String( "address" ), true )
	,	m_port( *this, QLatin1String( "port" ), true )
	,	m_portConstraint( 1, 65536 )
	,	m_isMustBeConnected( *this, QLatin1String( "mustBeConnected" ), false )
	,	m_timeout( *this, QLatin1String( "timeout" ), false )
	,	m_timeoutConstraint( 0, 10000 )
	,	m_type( *this, QLatin1String( "type" ), true )
{
	m_port.set_constraint( &m_portConstraint );
	m_timeout.set_constraint( &m_timeoutConstraint );
}

ChannelTag::ChannelTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
	const QString & name, bool isMandatory )
	:	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > ( owner, name, isMandatory )
	,	m_address( *this, QLatin1String( "address" ), true )
	,	m_port( *this, QLatin1String( "port" ), true )
	,	m_portConstraint( 1, 65536 )
	,	m_isMustBeConnected( *this, QLatin1String( "mustBeConnected" ), false )
	,	m_timeout( *this, QLatin1String( "timeout" ), false )
	,	m_timeoutConstraint( 0, 10000 )
	,	m_type( *this, QLatin1String( "type" ), true )
{
	m_port.set_constraint( &m_portConstraint );
	m_timeout.set_constraint( &m_timeoutConstraint );
}

ChannelTag::ChannelTag( const ChannelCfg & cfg,
	cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
	const QString & name, bool isMandatory )
	:	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > ( owner, name, isMandatory )
	,	m_address( *this, QLatin1String( "address" ), true )
	,	m_port( *this, QLatin1String( "port" ), true )
	,	m_portConstraint( 1, 65536 )
	,	m_isMustBeConnected( *this, QLatin1String( "mustBeConnected" ), false )
	,	m_timeout( *this, QLatin1String( "timeout" ), false )
	,	m_timeoutConstraint( 0, 10000 )
	,	m_type( *this, QLatin1String( "type" ), true )
{
	m_port.set_constraint( &m_portConstraint );
	m_timeout.set_constraint( &m_timeoutConstraint );

	set_value( cfg.name() );
	m_address.set_value( cfg.address() );
	m_port.set_value( cfg.port() );
	m_type.set_value( cfg.channelType() );

	if( cfg.isMustBeConnected() )
		m_isMustBeConnected.set_defined();

	if( cfg.timeout() )
		m_timeout.set_value( cfg.timeout() );
}

ChannelTag::ChannelTag( const ChannelCfg & cfg,
	const QString & name, bool isMandatory )
	:	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > ( name, isMandatory )
	,	m_address( *this, QLatin1String( "address" ), true )
	,	m_port( *this, QLatin1String( "port" ), true )
	,	m_portConstraint( 1, 65536 )
	,	m_isMustBeConnected( *this, QLatin1String( "mustBeConnected" ), false )
	,	m_timeout( *this, QLatin1String( "timeout" ), false )
	,	m_timeoutConstraint( 0, 10000 )
	,	m_type( *this, QLatin1String( "type" ), true )
{
	m_port.set_constraint( &m_portConstraint );
	m_timeout.set_constraint( &m_timeoutConstraint );

	set_value( cfg.name() );
	m_address.set_value( cfg.address() );
	m_port.set_value( cfg.port() );
	m_type.set_value( cfg.channelType() );

	if( cfg.isMustBeConnected() )
		m_isMustBeConnected.set_defined();

	if( cfg.timeout() )
		m_timeout.set_value( cfg.timeout() );
}

ChannelTag::~ChannelTag()
{
}

ChannelCfg
ChannelTag::cfg() const
{
	ChannelCfg cfg;

	cfg.setName( value() );
	cfg.setAddress( m_address.value() );
	cfg.setPort( (quint16) m_port.value() );
	cfg.setMustBeConnected( m_isMustBeConnected.is_defined() );

	if( m_timeout.is_defined() )
		cfg.setTimeout( m_timeout.value() );

	cfg.setChannelType( m_type.value() );

	return cfg;
}


//
// AvailableChannelsCfgTag
//

static const QString channelTagName = QLatin1String( "channel" );

AvailableChannelsCfgTag::AvailableChannelsCfgTag()
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "channelsCfg" ), true )
	,	m_channels( *this, channelTagName, false )
{
}

AvailableChannelsCfgTag::AvailableChannelsCfgTag( const AvailableChannelsCfg & cfg )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "channelsCfg" ), true )
	,	m_channels( *this, channelTagName, false )
{
	foreach( const ChannelCfg & ch, cfg )
	{
		cfgfile::tag_vector_of_tags_t< ChannelTag,
			cfgfile::qstring_trait_t >::ptr_to_tag_t
				t( new ChannelTag( ch, channelTagName ) );

		m_channels.set_value( t );
	}

	set_defined();
}

AvailableChannelsCfg
AvailableChannelsCfgTag::cfg() const
{
	AvailableChannelsCfg cfg;

	for( const auto & t : qAsConst( m_channels.values() ) )
		cfg.append( t->cfg() );

	return cfg;
}

} /* namespace Globe */

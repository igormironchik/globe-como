
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

// Globe include.
#include <Globe/Core/channels_cfg.hpp>


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

ChannelCfg::ChannelCfg( const QString & name, const QHostAddress & address,
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

const QHostAddress &
ChannelCfg::address() const
{
	return m_address;
}

void
ChannelCfg::setAddress( const QHostAddress & address )
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
	:	QtConfFile::TagScalar< QString > ( name, isMandatory )
	,	m_address( *this, QLatin1String( "address" ), true )
	,	m_port( *this, QLatin1String( "port" ), true )
	,	m_portConstraint( 1, 65536 )
	,	m_isMustBeConnected( *this, QLatin1String( "mustBeConnected" ), false )
	,	m_timeout( *this, QLatin1String( "timeout" ), false )
	,	m_timeoutConstraint( 0, 10000 )
	,	m_type( *this, QLatin1String( "type" ), true )
{
	m_port.setConstraint( &m_portConstraint );
	m_timeout.setConstraint( &m_timeoutConstraint );
}

ChannelTag::ChannelTag( QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagScalar< QString > ( owner, name, isMandatory )
	,	m_address( *this, QLatin1String( "address" ), true )
	,	m_port( *this, QLatin1String( "port" ), true )
	,	m_portConstraint( 1, 65536 )
	,	m_isMustBeConnected( *this, QLatin1String( "mustBeConnected" ), false )
	,	m_timeout( *this, QLatin1String( "timeout" ), false )
	,	m_timeoutConstraint( 0, 10000 )
	,	m_type( *this, QLatin1String( "type" ), true )
{
	m_port.setConstraint( &m_portConstraint );
	m_timeout.setConstraint( &m_timeoutConstraint );
}

ChannelTag::ChannelTag( const ChannelCfg & cfg, QtConfFile::Tag & owner,
	const QString & name, bool isMandatory )
	:	QtConfFile::TagScalar< QString > ( owner, name, isMandatory )
	,	m_address( *this, QLatin1String( "address" ), true )
	,	m_port( *this, QLatin1String( "port" ), true )
	,	m_portConstraint( 1, 65536 )
	,	m_isMustBeConnected( *this, QLatin1String( "mustBeConnected" ), false )
	,	m_timeout( *this, QLatin1String( "timeout" ), false )
	,	m_timeoutConstraint( 0, 10000 )
	,	m_type( *this, QLatin1String( "type" ), true )
{
	m_port.setConstraint( &m_portConstraint );
	m_timeout.setConstraint( &m_timeoutConstraint );

	setValue( cfg.name() );
	m_address.setValue( cfg.address().toString() );
	m_port.setValue( cfg.port() );
	m_type.setValue( cfg.channelType() );

	if( cfg.isMustBeConnected() )
		m_isMustBeConnected.setDefined();

	if( cfg.timeout() )
		m_timeout.setValue( cfg.timeout() );
}

ChannelTag::ChannelTag( const ChannelCfg & cfg,
	const QString & name, bool isMandatory )
	:	QtConfFile::TagScalar< QString > ( name, isMandatory )
	,	m_address( *this, QLatin1String( "address" ), true )
	,	m_port( *this, QLatin1String( "port" ), true )
	,	m_portConstraint( 1, 65536 )
	,	m_isMustBeConnected( *this, QLatin1String( "mustBeConnected" ), false )
	,	m_timeout( *this, QLatin1String( "timeout" ), false )
	,	m_timeoutConstraint( 0, 10000 )
	,	m_type( *this, QLatin1String( "type" ), true )
{
	m_port.setConstraint( &m_portConstraint );
	m_timeout.setConstraint( &m_timeoutConstraint );

	setValue( cfg.name() );
	m_address.setValue( cfg.address().toString() );
	m_port.setValue( cfg.port() );
	m_type.setValue( cfg.channelType() );

	if( cfg.isMustBeConnected() )
		m_isMustBeConnected.setDefined();

	if( cfg.timeout() )
		m_timeout.setValue( cfg.timeout() );
}

ChannelTag::~ChannelTag()
{
}

ChannelCfg
ChannelTag::cfg() const
{
	ChannelCfg cfg;

	cfg.setName( value() );
	cfg.setAddress( QHostAddress( m_address.value() ) );
	cfg.setPort( m_port.value() );
	cfg.setMustBeConnected( m_isMustBeConnected.isDefined() );

	if( m_timeout.isDefined() )
		cfg.setTimeout( m_timeout.value() );

	cfg.setChannelType( m_type.value() );

	return cfg;
}


//
// AvailableChannelsCfgTag
//

static const QString channelTagName = QLatin1String( "channel" );

AvailableChannelsCfgTag::AvailableChannelsCfgTag()
	:	QtConfFile::TagNoValue( QLatin1String( "channelsCfg" ), true )
	,	m_channels( *this, channelTagName, false )
{
}

AvailableChannelsCfgTag::AvailableChannelsCfgTag( const AvailableChannelsCfg & cfg )
	:	QtConfFile::TagNoValue( QLatin1String( "channelsCfg" ), true )
	,	m_channels( *this, channelTagName, false )
{
	foreach( const ChannelCfg & ch, cfg )
	{
		QtConfFile::TagVectorOfTags< ChannelTag >::PointerToTag
			t( new ChannelTag( ch, channelTagName ) );

		m_channels.setValue( t );
	}

	setDefined();
}

AvailableChannelsCfg
AvailableChannelsCfgTag::cfg() const
{
	AvailableChannelsCfg cfg;

	foreach( QtConfFile::TagVectorOfTags< ChannelTag >::PointerToTag t,
		m_channels.values() )
	{
		cfg.append( t->cfg() );
	}

	return cfg;
}

} /* namespace Globe */


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Scheme/source_cfg.hpp>

#include <Core/utils.hpp>


namespace Globe {

namespace Scheme {

//
// SourceCfg
//


SourceCfg::SourceCfg()
	:	m_type( Como::Source::Int )
{
}

SourceCfg::SourceCfg( Como::Source::Type type, const QString & channelName,
	const QString & typeName, const QString & sourceName,
	const QPointF & pos, const QSizeF & size,
	const QFont & font )
	:	ItemBaseCfg( pos, size, font )
	,	m_type( type )
	,	m_channelName( channelName )
	,	m_typeName( typeName )
	,	m_sourceName( sourceName )
{
}

SourceCfg::SourceCfg( const ItemBaseCfg & cfg )
	:	ItemBaseCfg( cfg )
	,	m_type( Como::Source::Int )
{
}

SourceCfg::SourceCfg( const SourceCfg & other )
	:	ItemBaseCfg( other )
	,	m_type( other.type() )
	,	m_channelName( other.channelName() )
	,	m_typeName( other.typeName() )
	,	m_sourceName( other.sourceName() )
{
}

SourceCfg &
SourceCfg::operator = ( const SourceCfg & other )
{
	if( this != &other )
	{
		ItemBaseCfg::operator = ( other );

		m_type = other.type();
		m_channelName = other.channelName();
		m_typeName = other.typeName();
		m_sourceName = other.sourceName();
	}

	return *this;
}

SourceCfg::~SourceCfg()
{
}

Como::Source::Type
SourceCfg::type() const
{
	return m_type;
}

void
SourceCfg::setType( Como::Source::Type t )
{
	m_type = t;
}

const QString &
SourceCfg::channelName() const
{
	return m_channelName;
}

void
SourceCfg::setChannelName( const QString & name )
{
	m_channelName = name;
}

const QString &
SourceCfg::typeName() const
{
	return m_typeName;
}

void
SourceCfg::setTypeName( const QString & name )
{
	m_typeName = name;
}

const QString &
SourceCfg::sourceName() const
{
	return m_sourceName;
}

void
SourceCfg::setSourceName( const QString & name )
{
	m_sourceName = name;
}


//
// SourceCfgTag
//

SourceCfgTag::SourceCfgTag( const QString & name, bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > ( name, isMandatory )
	,	m_type( *this, QLatin1String( "type" ), true )
	,	m_channelName( *this, QLatin1String( "channelName" ), true )
	,	m_typeName( *this, QLatin1String( "typeName" ), true )
	,	m_sourceName( *this, QLatin1String( "sourceName" ), true )
	,	m_baseCfg( *this, QLatin1String( "ui" ), true )
{
	m_typeConstraint.add_value( comoSourceIntType );
	m_typeConstraint.add_value( comoSourceUIntType );
	m_typeConstraint.add_value( comoSourceLongLongType );
	m_typeConstraint.add_value( comoSourceULongLongType );
	m_typeConstraint.add_value( comoSourceStringType );
	m_typeConstraint.add_value( comoSourceDoubleType );
	m_typeConstraint.add_value( comoSourceDateTimeType );
	m_typeConstraint.add_value( comoSourceTimeType );

	m_type.set_constraint( &m_typeConstraint );
}

SourceCfgTag::SourceCfgTag( const SourceCfg & cfg, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > ( name, isMandatory )
	,	m_type( *this, QLatin1String( "type" ), true )
	,	m_channelName( *this, QLatin1String( "channelName" ), true )
	,	m_typeName( *this, QLatin1String( "typeName" ), true )
	,	m_sourceName( *this, QLatin1String( "sourceName" ), true )
	,	m_baseCfg( cfg, *this, QLatin1String( "ui" ), true )
{
	m_typeConstraint.add_value( comoSourceIntType );
	m_typeConstraint.add_value( comoSourceUIntType );
	m_typeConstraint.add_value( comoSourceLongLongType );
	m_typeConstraint.add_value( comoSourceULongLongType );
	m_typeConstraint.add_value( comoSourceStringType );
	m_typeConstraint.add_value( comoSourceDoubleType );
	m_typeConstraint.add_value( comoSourceDateTimeType );
	m_typeConstraint.add_value( comoSourceTimeType );

	m_type.set_constraint( &m_typeConstraint );

	m_type.set_value( comoSourceTypeToString( cfg.type() ) );
	m_channelName.set_value( cfg.channelName() );
	m_typeName.set_value( cfg.typeName() );
	m_sourceName.set_value( cfg.sourceName() );

	set_defined();
}

SourceCfg
SourceCfgTag::sourceCfg() const
{
	SourceCfg cfg( m_baseCfg.baseCfg() );

	cfg.setType( stringToComoSourceType( m_type.value() ) );
	cfg.setChannelName( m_channelName.value() );
	cfg.setTypeName( m_typeName.value() );
	cfg.setSourceName( m_sourceName.value() );

	return cfg;
}

} /* namespace Scheme */

} /* namespace Globe */

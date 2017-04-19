
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
#include <Globe/Scheme/source_cfg.hpp>

#include <Globe/Core/utils.hpp>


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
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_type( *this, QLatin1String( "type" ), true )
	,	m_channelName( *this, QLatin1String( "channelName" ), true )
	,	m_typeName( *this, QLatin1String( "typeName" ), true )
	,	m_sourceName( *this, QLatin1String( "sourceName" ), true )
	,	m_baseCfg( *this, QLatin1String( "ui" ), true )
{
	m_typeConstraint.addValue( comoSourceIntType );
	m_typeConstraint.addValue( comoSourceUIntType );
	m_typeConstraint.addValue( comoSourceLongLongType );
	m_typeConstraint.addValue( comoSourceULongLongType );
	m_typeConstraint.addValue( comoSourceStringType );
	m_typeConstraint.addValue( comoSourceDoubleType );
	m_typeConstraint.addValue( comoSourceDateTimeType );
	m_typeConstraint.addValue( comoSourceTimeType );

	m_type.setConstraint( &m_typeConstraint );
}

SourceCfgTag::SourceCfgTag( const SourceCfg & cfg, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_type( *this, QLatin1String( "type" ), true )
	,	m_channelName( *this, QLatin1String( "channelName" ), true )
	,	m_typeName( *this, QLatin1String( "typeName" ), true )
	,	m_sourceName( *this, QLatin1String( "sourceName" ), true )
	,	m_baseCfg( cfg, *this, QLatin1String( "ui" ), true )
{
	m_typeConstraint.addValue( comoSourceIntType );
	m_typeConstraint.addValue( comoSourceUIntType );
	m_typeConstraint.addValue( comoSourceLongLongType );
	m_typeConstraint.addValue( comoSourceULongLongType );
	m_typeConstraint.addValue( comoSourceStringType );
	m_typeConstraint.addValue( comoSourceDoubleType );
	m_typeConstraint.addValue( comoSourceDateTimeType );
	m_typeConstraint.addValue( comoSourceTimeType );

	m_type.setConstraint( &m_typeConstraint );

	m_type.setValue( comoSourceTypeToString( cfg.type() ) );
	m_channelName.setValue( cfg.channelName() );
	m_typeName.setValue( cfg.typeName() );
	m_sourceName.setValue( cfg.sourceName() );

	setDefined();
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

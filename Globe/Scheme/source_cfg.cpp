
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

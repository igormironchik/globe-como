
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
#include <Globe/Scheme/scheme_cfg.hpp>


namespace Globe {

namespace Scheme {

//
// SchemeCfg
//

SchemeCfg::SchemeCfg()
{
}

SchemeCfg::SchemeCfg( const QList< SourceCfg > & sources,
	const QList< TextCfg > & texts )
	:	m_sources( sources )
	,	m_texts( texts )
{
}

SchemeCfg::SchemeCfg( const SchemeCfg & other )
	:	m_sources( other.sources() )
	,	m_texts( other.texts() )
{
}

SchemeCfg &
SchemeCfg::operator = ( const SchemeCfg & other )
{
	if( this != &other )
	{
		m_sources = other.sources();
		m_texts = other.texts();
	}

	return *this;
}

const QList< SourceCfg > &
SchemeCfg::sources() const
{
	return m_sources;
}

void
SchemeCfg::setSources( const QList< SourceCfg > & s )
{
	m_sources = s;
}

const QList< TextCfg > &
SchemeCfg::texts() const
{
	return m_texts;
}

void
SchemeCfg::setTexts( const QList< TextCfg > & t )
{
	m_texts = t;
}

const QList< SchemeCfg > &
SchemeCfg::aggregates() const
{
	return m_aggregates;
}

void
SchemeCfg::setAggregates( const QList< SchemeCfg > & a )
{
	m_aggregates = a;
}


//
// SchemeCfgTag
//


SchemeCfgTag::SchemeCfgTag()
	:	QtConfFile::TagNoValue( QLatin1String( "scheme" ), true )
	,	m_sources( *this, QLatin1String( "source" ), false )
	,	m_texts( *this, QLatin1String( "text" ), false )
	,	m_aggregates( *this, QLatin1String( "aggregate" ), false )
{
}

SchemeCfgTag::SchemeCfgTag( const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_sources( *this, QLatin1String( "source" ), false )
	,	m_texts( *this, QLatin1String( "text" ), false )
	,	m_aggregates( *this, QLatin1String( "aggregate" ), false )
{
}

SchemeCfgTag::SchemeCfgTag( const SchemeCfg & cfg, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_sources( *this, QLatin1String( "source" ), false )
	,	m_texts( *this, QLatin1String( "text" ), false )
	,	m_aggregates( *this, QLatin1String( "aggregate" ), false )
{
	initFromCfg( cfg );
}

SchemeCfgTag::SchemeCfgTag( const SchemeCfg & cfg )
	:	QtConfFile::TagNoValue( QLatin1String( "scheme" ), true )
	,	m_sources( *this, QLatin1String( "source" ), false )
	,	m_texts( *this, QLatin1String( "text" ), false )
	,	m_aggregates( *this, QLatin1String( "aggregate" ), false )
{
	initFromCfg( cfg );
}

SchemeCfg
SchemeCfgTag::cfg() const
{
	SchemeCfg cfg;

	QList< SourceCfg > sources;

	foreach( QtConfFile::TagVectorOfTags< SourceCfgTag >::PointerToTag t,
		m_sources.values() )
	{
		sources.append( t->sourceCfg() );
	}

	cfg.setSources( sources );

	QList< TextCfg > texts;

	foreach( QtConfFile::TagVectorOfTags< TextCfgTag >::PointerToTag t,
		m_texts.values() )
	{
		texts.append( t->textCfg() );
	}

	cfg.setTexts( texts );

	QList< SchemeCfg > aggregates;

	for( const auto & t : qAsConst( m_aggregates.values() ) )
	{
		aggregates.append( t->cfg() );
	}

	cfg.setAggregates( aggregates );

	return cfg;
}

void
SchemeCfgTag::initFromCfg( const SchemeCfg & cfg )
{
	foreach( const SourceCfg & s, cfg.sources() )
	{
		QtConfFile::TagVectorOfTags< SourceCfgTag >::PointerToTag
			t( new SourceCfgTag( s, QLatin1String( "source" ) ) );

		m_sources.setValue( t );
	}

	foreach( const TextCfg & c, cfg.texts() )
	{
		QtConfFile::TagVectorOfTags< TextCfgTag >::PointerToTag
			t( new TextCfgTag( c, QLatin1String( "text" ) ) );

		m_texts.setValue( t );
	}

	for( const auto & c : qAsConst( cfg.aggregates() ) )
	{
		QtConfFile::TagVectorOfTags< SchemeCfgTag >::PointerToTag
			t( new SchemeCfgTag( c, QLatin1String( "aggregate" ) ) );

		m_aggregates.setValue( t );
	}

	setDefined();
}

} /* namespace Scheme */

} /* namespace Globe */

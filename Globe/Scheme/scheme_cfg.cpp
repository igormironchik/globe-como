
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2020 Igor Mironchik

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

const QString &
SchemeCfg::name() const
{
	return m_name;
}

void
SchemeCfg::setName( const QString & n )
{
	m_name = n;
}

const QPointF &
SchemeCfg::pos() const
{
	return m_pos;
}

void
SchemeCfg::setPos( const QPointF & pos )
{
	m_pos = pos;
}

const QSizeF &
SchemeCfg::size() const
{
	return m_size;
}

void
SchemeCfg::setSize( const QSizeF & size )
{
	m_size = size;
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

QList< QPair< Como::Source, QString > >
SchemeCfg::availableSources() const
{
	QList< QPair< Como::Source, QString > > res;

	for( const auto & s : qAsConst( m_sources ) )
	{
		res.append( qMakePair( Como::Source( s.type(), s.sourceName(),
			s.typeName(), QVariant(), QString() ), s.channelName() ) );
	}

	for( const auto & a : qAsConst( m_aggregates ) )
	{
		res.append( a.availableSources() );
	}

	return res;
}


//
// SchemeCfgTag
//


SchemeCfgTag::SchemeCfgTag()
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >(
			QLatin1String( "scheme" ), true )
	,	m_sources( *this, QLatin1String( "source" ), false )
	,	m_texts( *this, QLatin1String( "text" ), false )
	,	m_aggregates( *this, QLatin1String( "aggregate" ), false )
	,	m_name( *this, QLatin1String( "name" ), false )
	,	m_pos( *this, QLatin1String( "pos" ), false )
	,	m_size( *this, QLatin1String( "size" ), false )
{
}

SchemeCfgTag::SchemeCfgTag( const QString & name, bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			name, isMandatory )
	,	m_sources( *this, QLatin1String( "source" ), false )
	,	m_texts( *this, QLatin1String( "text" ), false )
	,	m_aggregates( *this, QLatin1String( "aggregate" ), false )
	,	m_name( *this, QLatin1String( "name" ), false )
	,	m_pos( *this, QLatin1String( "pos" ), false )
	,	m_size( *this, QLatin1String( "size" ), false )
{
}

SchemeCfgTag::SchemeCfgTag( const SchemeCfg & cfg, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			name, isMandatory )
	,	m_sources( *this, QLatin1String( "source" ), false )
	,	m_texts( *this, QLatin1String( "text" ), false )
	,	m_aggregates( *this, QLatin1String( "aggregate" ), false )
	,	m_name( *this, QLatin1String( "name" ), false )
	,	m_pos( cfg.pos(), *this, QLatin1String( "pos" ), false )
	,	m_size( cfg.size(), *this, QLatin1String( "size" ), false )
{
	initFromCfg( cfg );
}

SchemeCfgTag::SchemeCfgTag( const SchemeCfg & cfg )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "scheme" ), true )
	,	m_sources( *this, QLatin1String( "source" ), false )
	,	m_texts( *this, QLatin1String( "text" ), false )
	,	m_aggregates( *this, QLatin1String( "aggregate" ), false )
	,	m_name( *this, QLatin1String( "name" ), false )
	,	m_pos( *this, QLatin1String( "pos" ), false )
	,	m_size( *this, QLatin1String( "size" ), false )
{
	initFromCfg( cfg );
}

SchemeCfg
SchemeCfgTag::cfg() const
{
	SchemeCfg cfg;

	QList< SourceCfg > sources;

	for( const auto & t : qAsConst( m_sources.values() ) )
	{
		sources.append( t->sourceCfg() );
	}

	cfg.setSources( sources );

	QList< TextCfg > texts;

	for( const auto & t : qAsConst( m_texts.values() ) )
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

	if( m_name.is_defined() )
	{
		cfg.setName( m_name.value() );
		cfg.setPos( m_pos.point() );
		cfg.setSize( m_size.size() );
	}

	return cfg;
}

void
SchemeCfgTag::initFromCfg( const SchemeCfg & cfg )
{
	for( const auto & s : qAsConst( cfg.sources() ) )
	{
		cfgfile::tag_vector_of_tags_t< SourceCfgTag,
			cfgfile::qstring_trait_t >::ptr_to_tag_t
				t( new SourceCfgTag( s, QLatin1String( "source" ) ) );

		m_sources.set_value( t );
	}

	for( const auto & c : qAsConst( cfg.texts() ) )
	{
		cfgfile::tag_vector_of_tags_t< TextCfgTag,
			cfgfile::qstring_trait_t >::ptr_to_tag_t
				t( new TextCfgTag( c, QLatin1String( "text" ) ) );

		m_texts.set_value( t );
	}

	for( const auto & c : qAsConst( cfg.aggregates() ) )
	{
		cfgfile::tag_vector_of_tags_t< SchemeCfgTag,
			cfgfile::qstring_trait_t >::ptr_to_tag_t
				t( new SchemeCfgTag( c, QLatin1String( "aggregate" ) ) );

		m_aggregates.set_value( t );
	}

	if( !cfg.name().isEmpty() )
		m_name.set_value( cfg.name() );

	set_defined();
}

} /* namespace Scheme */

} /* namespace Globe */

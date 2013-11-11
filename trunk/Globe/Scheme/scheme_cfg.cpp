
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


//
// SchemeCfgTag
//


SchemeCfgTag::SchemeCfgTag()
	:	QtConfFile::TagNoValue( QLatin1String( "scheme" ), true )
	,	m_sources( *this, QLatin1String( "source" ), false )
	,	m_texts( *this, QLatin1String( "text" ), false )
{
}

SchemeCfgTag::SchemeCfgTag( const SchemeCfg & cfg )
	:	QtConfFile::TagNoValue( QLatin1String( "scheme" ), true )
	,	m_sources( *this, QLatin1String( "source" ), false )
	,	m_texts( *this, QLatin1String( "text" ), false )
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

	setDefined();
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

	return cfg;
}

} /* namespace Scheme */

} /* namespace Globe */

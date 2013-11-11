
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
#include <Globe/Scheme/text_cfg.hpp>


namespace Globe {

namespace Scheme {

//
// TextCfg
//


TextCfg::TextCfg()
{
}

TextCfg::TextCfg( const QString & text,
	const QPointF & pos, const QSizeF & size,
	const QFont & font )
	:	ItemBaseCfg( pos, size, font )
	,	m_text( text )
{
}

TextCfg::TextCfg( const ItemBaseCfg & cfg )
	:	ItemBaseCfg( cfg )
{
}

TextCfg::TextCfg( const TextCfg & other )
	:	ItemBaseCfg( other )
	,	m_text( other.text() )
{
}

TextCfg &
TextCfg::operator = ( const TextCfg & other )
{
	if( this != &other )
	{
		ItemBaseCfg::operator = ( other );

		m_text = other.text();
	}

	return *this;
}

TextCfg::~TextCfg()
{
}

const QString &
TextCfg::text() const
{
	return m_text;
}

void
TextCfg::setText( const QString & t )
{
	m_text = t;
}


//
// TextCfgTag
//

TextCfgTag::TextCfgTag( const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_text( *this, QLatin1String( "text" ), true )
	,	m_baseCfg( *this, QLatin1String( "ui" ), true )
{
}

TextCfgTag::TextCfgTag( const TextCfg & cfg, const QString & name,
	bool isMandatory() )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_text( *this, QLatin1String( "text" ), true )
	,	m_baseCfg( cfg, *this, QLatin1String( "ui" ), true )
{
	m_text.setValue( cfg.text() );

	setDefined();
}

TextCfg
TextCfgTag::textCfg() const
{
	TextCfg cfg( m_baseCfg.baseCfg() );

	cfg.setText( m_text.value() );

	return cfg;
}

} /* namespace Scheme */

} /* namespace Globe */

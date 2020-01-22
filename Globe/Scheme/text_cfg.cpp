
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
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > ( name, isMandatory )
	,	m_text( *this, QLatin1String( "text" ), true )
	,	m_baseCfg( *this, QLatin1String( "ui" ), true )
{
}

TextCfgTag::TextCfgTag( const TextCfg & cfg, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > ( name, isMandatory )
	,	m_text( *this, QLatin1String( "text" ), true )
	,	m_baseCfg( cfg, *this, QLatin1String( "ui" ), true )
{
	m_text.set_value( cfg.text() );

	set_defined();
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

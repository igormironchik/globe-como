
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Scheme/text_cfg.hpp>


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


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SCHEME__TEXT_CFG_HPP__INCLUDED
#define GLOBE__SCHEME__TEXT_CFG_HPP__INCLUDED

// cfgfile include.
#include <cfgfile/all.hpp>

// Globe include.
#include <Scheme/item_base_cfg.hpp>


namespace Globe {

namespace Scheme {

//
// TextCfg
//

//! Configuration of the text item on the scheme.
class TextCfg
	:	public ItemBaseCfg
{
public:
	TextCfg();

	TextCfg( const QString & text,
		const QPointF & pos, const QSizeF & size,
		const QFont & font );

	explicit TextCfg( const ItemBaseCfg & cfg );

	TextCfg( const TextCfg & other );

	TextCfg & operator = ( const TextCfg & other );

	virtual ~TextCfg();

	//! \return Text.
	const QString & text() const;
	//! Set text.
	void setText( const QString & t );

private:
	//! Text.
	QString m_text;
}; // class TextCfg


//
// TextCfgTag
//

//! Tag with text item configuration.
class TextCfgTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	TextCfgTag( const QString & name, bool isMandatory = false );

	TextCfgTag( const TextCfg & cfg, const QString & name,
		bool isMandatory = false );

	//! \return Configuration.
	TextCfg textCfg() const;

private:
	//! Text.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_text;
	//! Item base cfg.
	ItemBaseCfgTag m_baseCfg;
}; // class TextCfgTag

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__TEXT_CFG_HPP__INCLUDED

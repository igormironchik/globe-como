
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

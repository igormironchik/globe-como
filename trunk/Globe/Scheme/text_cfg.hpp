
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

#ifndef GLOBE__SCHEME__TEXT_CFG_HPP__INCLUDED
#define GLOBE__SCHEME__TEXT_CFG_HPP__INCLUDED

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>

// Globe include.
#include <Globe/Scheme/item_base_cfg.hpp>


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
	:	public QtConfFile::TagNoValue
{
public:
	TextCfgTag( const QString & name, bool isMandatory = false );

	TextCfgTag( const TextCfg & cfg, const QString & name,
		bool isMandatory() = false );

	//! \return Configuration.
	TextCfg textCfg() const;

private:
	//! Text.
	QtConfFile::TagScalar< QString > m_text;
	//! Item base cfg.
	ItemBaseCfgTag m_baseCfg;
}; // class TextCfgTag

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__TEXT_CFG_HPP__INCLUDED

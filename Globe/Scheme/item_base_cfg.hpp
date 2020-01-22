
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

#ifndef GLOBE__SCHEME__ITEM_BASE_CFG_HPP__INCLUDED
#define GLOBE__SCHEME__ITEM_BASE_CFG_HPP__INCLUDED

// cfgfile include.
#include <cfgfile/all.hpp>

// Qt include.
#include <QPointF>
#include <QSizeF>
#include <QFont>


namespace Globe {

namespace Scheme {

//
// ItemBaseCfg
//

//! Base configuration for the items on the scheme.
class ItemBaseCfg {
public:
	ItemBaseCfg();

	ItemBaseCfg( const QPointF & pos, const QSizeF & size,
		const QFont & font );

	ItemBaseCfg( const ItemBaseCfg & other );

	ItemBaseCfg & operator = ( const ItemBaseCfg & other );

	virtual ~ItemBaseCfg();

	//! \return Position of the item.
	const QPointF & pos() const;
	//! Set position of the item.
	void setPos( const QPointF & pos );

	//! \return Size of the item.
	const QSizeF & size() const;
	//! Set size of the item.
	void setSize( const QSizeF & size );

	//! \return Is font set?
	bool isFontSet() const;
	//! \return Font.
	const QFont & font() const;
	//! Set font.
	void setFont( const QFont & font );

private:
	//! Position of the item.
	QPointF m_pos;
	//! Size of the item.
	QSizeF m_size;
	//! Font.
	QFont m_font;
	//! Is font set.
	bool m_isFontSet;
}; // class ItemBaseCfg


//
// QPointFTag
//

//! Tag that store QPointF.
class QPointFTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	QPointFTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	QPointFTag( const QPointF & point,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
		bool isMandatory = false );

	//! \return Point.
	QPointF point() const;

private:
	//! X.
	cfgfile::tag_scalar_t< double, cfgfile::qstring_trait_t > m_x;
	//! Y.
	cfgfile::tag_scalar_t< double, cfgfile::qstring_trait_t > m_y;
}; // class QPointFTag


//
// QSizeFTag
//

//! Tag that store QSizeF.
class QSizeFTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	QSizeFTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	QSizeFTag( const QSizeF & size,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
		bool isMandatory = false );

	//! \return Size.
	QSizeF size() const;

private:
	//! Width.
	cfgfile::tag_scalar_t< double, cfgfile::qstring_trait_t > m_width;
	//! Height.
	cfgfile::tag_scalar_t< double, cfgfile::qstring_trait_t > m_height;
	//! Constraint.
	cfgfile::constraint_min_max_t< double > m_constraint;
}; // class QSizeFTag


//
// QFontTag
//

//! Tag that store QFont.
class QFontTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	QFontTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	QFontTag( const QFont & font,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
		bool isMandatory = false );

	//! Set value.
	void setValue( const QFont & font );

	//! \return Font.
	QFont font() const;

private:
	//! Font name.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_name;
	//! Point size.
	cfgfile::tag_scalar_t< int, cfgfile::qstring_trait_t > m_pointSize;
	//! Weight.
	cfgfile::tag_scalar_t< int, cfgfile::qstring_trait_t > m_weight;
	//! Is font italic?
	cfgfile::tag_scalar_t< bool, cfgfile::qstring_trait_t > m_italic;
}; // class QFontTag


//
// ItemBaseCfgTag
//

//! Tag that store ItemBaseCfg.
class ItemBaseCfgTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	ItemBaseCfgTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	ItemBaseCfgTag( const ItemBaseCfg & cfg,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
		bool isMandatory = false );

	//! \return Cfg.
	ItemBaseCfg baseCfg() const;

private:
	//! Pos.
	QPointFTag m_pos;
	//! Size.
	QSizeFTag m_size;
	//! Font.
	QFontTag m_font;
}; // class ItemBaseCfgTag

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__ITEM_BASE_CFG_HPP__INCLUDED


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

#ifndef GLOBE__SCHEME__ITEM_BASE_CFG_HPP__INCLUDED
#define GLOBE__SCHEME__ITEM_BASE_CFG_HPP__INCLUDED

// QtConfFile include.
#include <QtConfFile/TagScalar>
#include <QtConfFile/TagNoValue>
#include <QtConfFile/ConstraintMinMax>

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
	:	public QtConfFile::TagNoValue
{
public:
	QPointFTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	QPointFTag( const QPointF & point,
		QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	//! \return Point.
	QPointF point() const;

private:
	//! X.
	QtConfFile::TagScalar< double > m_x;
	//! Y.
	QtConfFile::TagScalar< double > m_y;
}; // class QPointFTag


//
// QSizeFTag
//

//! Tag that store QSizeF.
class QSizeFTag
	:	public QtConfFile::TagNoValue
{
public:
	QSizeFTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	QSizeFTag( const QSizeF & size,
		QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	//! \return Size.
	QSizeF size() const;

private:
	//! Width.
	QtConfFile::TagScalar< double > m_width;
	//! Height.
	QtConfFile::TagScalar< double > m_height;
	//! Constraint.
	QtConfFile::ConstraintMinMax< double > m_constraint;
}; // class QSizeFTag


//
// QFontTag
//

//! Tag that store QFont.
class QFontTag
	:	public QtConfFile::TagNoValue
{
public:
	QFontTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	QFontTag( const QFont & font,
		QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	//! Set value.
	void setValue( const QFont & font );

	//! \return Font.
	QFont font() const;

private:
	//! Font name.
	QtConfFile::TagScalar< QString > m_name;
	//! Point size.
	QtConfFile::TagScalar< int > m_pointSize;
	//! Weight.
	QtConfFile::TagScalar< int > m_weight;
	//! Is font italic?
	QtConfFile::TagScalar< bool > m_italic;
}; // class QFontTag


//
// ItemBaseCfgTag
//

//! Tag that store ItemBaseCfg.
class ItemBaseCfgTag
	:	public QtConfFile::TagNoValue
{
public:
	ItemBaseCfgTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	ItemBaseCfgTag( const ItemBaseCfg & cfg,
		QtConfFile::Tag & owner, const QString & name,
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

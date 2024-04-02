
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Scheme/item_base_cfg.hpp>
#include <Scheme/mm_pixels.hpp>


namespace Globe {

namespace Scheme {

//
// ItemBaseCfg
//

ItemBaseCfg::ItemBaseCfg()
	:	m_isFontSet( false )
{
}

ItemBaseCfg::ItemBaseCfg( const QPointF & pos, const QSizeF & size,
	const QFont & font )
	:	m_pos( pos )
	,	m_size( size )
	,	m_font( font )
	,	m_isFontSet( true )
{
}

ItemBaseCfg::ItemBaseCfg( const ItemBaseCfg & other )
	:	m_pos( other.pos() )
	,	m_size( other.size() )
	,	m_font( other.font() )
	,	m_isFontSet( other.isFontSet() )
{
}

ItemBaseCfg &
ItemBaseCfg::operator = ( const ItemBaseCfg & other )
{
	if( this != &other )
	{
		m_pos = other.pos();
		m_size = other.size();
		m_font = other.font();
		m_isFontSet = other.isFontSet();
	}

	return *this;
}

ItemBaseCfg::~ItemBaseCfg()
{
}

const QPointF &
ItemBaseCfg::pos() const
{
	return m_pos;
}

void
ItemBaseCfg::setPos( const QPointF & pos )
{
	m_pos = pos;
}

const QSizeF &
ItemBaseCfg::size() const
{
	return m_size;
}

void
ItemBaseCfg::setSize( const QSizeF & size )
{
	m_size = size;
}

bool
ItemBaseCfg::isFontSet() const
{
	return m_isFontSet;
}

const QFont &
ItemBaseCfg::font() const
{
	return m_font;
}

void
ItemBaseCfg::setFont( const QFont & font )
{
	m_font = font;
	m_isFontSet = true;
}


//
// QPointFTag
//

QPointFTag::QPointFTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_x( *this, QLatin1String( "x" ), true )
	,	m_y( *this, QLatin1String( "y" ), true )
{
}

QPointFTag::QPointFTag( const QPointF & point,
	cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_x( *this, QLatin1String( "x" ), true )
	,	m_y( *this, QLatin1String( "y" ), true )
{
	const QPointF mm = pointToMm( point );

	m_x.set_value( mm.x() );
	m_y.set_value( mm.y() );

	set_defined();
}

QPointF
QPointFTag::point() const
{
	const QPointF mm( m_x.value(), m_y.value() );

	return pointFromMm( mm );
}


//
// QSizeFTag
//

QSizeFTag::QSizeFTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_width( *this, QLatin1String( "width" ), true )
	,	m_height( *this, QLatin1String( "height" ), true )
	,	m_constraint( 0, 9999 )
{
	m_width.set_constraint( &m_constraint );
	m_height.set_constraint( &m_constraint );
}

QSizeFTag::QSizeFTag( const QSizeF & size,
	cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_width( *this, QLatin1String( "width" ), true )
	,	m_height( *this, QLatin1String( "height" ), true )
	,	m_constraint( 0, 9999 )
{
	m_width.set_constraint( &m_constraint );
	m_height.set_constraint( &m_constraint );

	const QSizeF mm = sizeToMm( size );

	m_width.set_value( mm.width() );
	m_height.set_value( mm.height() );

	set_defined();
}

QSizeF
QSizeFTag::size() const
{
	const QSizeF mm( m_width.value(), m_height.value() );

	return sizeFromMm( mm );
}


//
// QFontTag
//

QFontTag::QFontTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_name( *this, QLatin1String( "name" ), true )
	,	m_pointSize( *this, QLatin1String( "pointSize" ), true )
	,	m_weight( *this, QLatin1String( "weight" ), true )
	,	m_italic( *this, QLatin1String( "isItalic" ), true )
{
}

QFontTag::QFontTag( const QFont & font,
	cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_name( *this, QLatin1String( "name" ), true )
	,	m_pointSize( *this, QLatin1String( "pointSize" ), true )
	,	m_weight( *this, QLatin1String( "weight" ), true )
	,	m_italic( *this, QLatin1String( "isItalic" ), true )
{
	setValue( font );
}

void
QFontTag::setValue( const QFont & font )
{
	m_name.set_value( font.family() );
	m_pointSize.set_value( font.pointSize() );
	m_weight.set_value( font.weight() );
	m_italic.set_value( font.italic() );

	set_defined();
}

QFont
QFontTag::font() const
{
	return QFont( m_name.value(), m_pointSize.value(),
		m_weight.value(), m_italic.value() );
}


//
// ItemBaseCfgTag
//

ItemBaseCfgTag::ItemBaseCfgTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_pos( *this, QLatin1String( "pos" ), true )
	,	m_size( *this, QLatin1String( "size" ), true )
	,	m_font( *this, QLatin1String( "font" ), false )
{
}

ItemBaseCfgTag::ItemBaseCfgTag( const ItemBaseCfg & cfg,
	cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_pos( cfg.pos(), *this, QLatin1String( "pos" ), true )
	,	m_size( cfg.size(), *this, QLatin1String( "size" ), true )
	,	m_font( *this, QLatin1String( "font" ), false )
{
	if( cfg.isFontSet() )
		m_font.setValue( cfg.font() );

	set_defined();
}

ItemBaseCfg
ItemBaseCfgTag::baseCfg() const
{
	ItemBaseCfg cfg;

	cfg.setPos( m_pos.point() );
	cfg.setSize( m_size.size() );

	if( m_font.is_defined() )
		cfg.setFont( m_font.font() );

	return cfg;
}

} /* namespace Scheme */

} /* namespace Globe */

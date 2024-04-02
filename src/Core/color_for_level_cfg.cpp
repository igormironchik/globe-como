
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/color_for_level_cfg.hpp>
#include <Core/color_for_level.hpp>


namespace Globe {

//
// ColorForLevelTag
//

ColorForLevelTag::ColorForLevelTag()
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "colors" ), true )
	,	m_noneColor( *this, QLatin1String( "noneColor" ), true )
	,	m_criticalColor( *this, QLatin1String( "criticalColor" ), true )
	,	m_errorColor( *this, QLatin1String( "errorColor" ), true )
	,	m_warningColor( *this, QLatin1String( "warningColor" ), true )
	,	m_debugColor( *this, QLatin1String( "debugColor" ), true )
	,	m_infoColor( *this, QLatin1String( "infoColor" ), true )
	,	m_deregisteredColor( *this, QLatin1String( "deregisteredColor" ), true )
	,	m_disconnectedColor( *this, QLatin1String( "disconnectedColor" ), true )
{
}

ColorForLevelTag::ColorForLevelTag( ColorForLevel * colorForLevel )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "colors" ), true )
	,	m_noneColor( *this, QLatin1String( "noneColor" ), true )
	,	m_criticalColor( *this, QLatin1String( "criticalColor" ), true )
	,	m_errorColor( *this, QLatin1String( "errorColor" ), true )
	,	m_warningColor( *this, QLatin1String( "warningColor" ), true )
	,	m_debugColor( *this, QLatin1String( "debugColor" ), true )
	,	m_infoColor( *this, QLatin1String( "infoColor" ), true )
	,	m_deregisteredColor( *this, QLatin1String( "deregisteredColor" ), true )
	,	m_disconnectedColor( *this, QLatin1String( "disconnectedColor" ), true )
{
	m_noneColor.set_value( colorForLevel->color( None ).name() );
	m_criticalColor.set_value( colorForLevel->color( Critical ).name() );
	m_errorColor.set_value( colorForLevel->color( Error ).name() );
	m_warningColor.set_value( colorForLevel->color( Warning ).name() );
	m_debugColor.set_value( colorForLevel->color( Debug ).name() );
	m_infoColor.set_value( colorForLevel->color( Info ).name() );
	m_deregisteredColor.set_value( colorForLevel->deregisteredColor().name() );
	m_disconnectedColor.set_value( colorForLevel->disconnectedColor().name() );

	set_defined();
}

void
ColorForLevelTag::initColorForLevel( ColorForLevel * colorForLevel )
{
	const auto none = QColor::fromString( m_noneColor.value() );
	const auto critical = QColor::fromString( m_criticalColor.value() );
	const auto error = QColor::fromString( m_errorColor.value() );
	const auto warning = QColor::fromString( m_warningColor.value() );
	const auto debug = QColor::fromString( m_debugColor.value() );
	const auto info = QColor::fromString( m_infoColor.value() );
	const auto deregistered = QColor::fromString( m_deregisteredColor.value() );
	const auto disconnected = QColor::fromString( m_disconnectedColor.value() );

	colorForLevel->setColors( none, critical, error, warning,
		debug, info, deregistered, disconnected );
}

} /* namespace Globe */

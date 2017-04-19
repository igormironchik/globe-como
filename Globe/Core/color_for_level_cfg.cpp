
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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
#include <Globe/Core/color_for_level_cfg.hpp>
#include <Globe/Core/color_for_level.hpp>


namespace Globe {

//
// ColorForLevelTag
//

ColorForLevelTag::ColorForLevelTag()
	:	QtConfFile::TagNoValue( QLatin1String( "colors" ), true )
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
	:	QtConfFile::TagNoValue( QLatin1String( "colors" ), true )
	,	m_noneColor( *this, QLatin1String( "noneColor" ), true )
	,	m_criticalColor( *this, QLatin1String( "criticalColor" ), true )
	,	m_errorColor( *this, QLatin1String( "errorColor" ), true )
	,	m_warningColor( *this, QLatin1String( "warningColor" ), true )
	,	m_debugColor( *this, QLatin1String( "debugColor" ), true )
	,	m_infoColor( *this, QLatin1String( "infoColor" ), true )
	,	m_deregisteredColor( *this, QLatin1String( "deregisteredColor" ), true )
	,	m_disconnectedColor( *this, QLatin1String( "disconnectedColor" ), true )
{
	m_noneColor.setValue( colorForLevel->color( None ).name() );
	m_criticalColor.setValue( colorForLevel->color( Critical ).name() );
	m_errorColor.setValue( colorForLevel->color( Error ).name() );
	m_warningColor.setValue( colorForLevel->color( Warning ).name() );
	m_debugColor.setValue( colorForLevel->color( Debug ).name() );
	m_infoColor.setValue( colorForLevel->color( Info ).name() );
	m_deregisteredColor.setValue( colorForLevel->deregisteredColor().name() );
	m_disconnectedColor.setValue( colorForLevel->disconnectedColor().name() );

	setDefined();
}

void
ColorForLevelTag::initColorForLevel( ColorForLevel * colorForLevel )
{
	QColor none;
	QColor critical;
	QColor error;
	QColor warning;
	QColor debug;
	QColor info;
	QColor deregistered;
	QColor disconnected;

	none.setNamedColor( m_noneColor.value() );
	critical.setNamedColor( m_criticalColor.value() );
	error.setNamedColor( m_errorColor.value() );
	warning.setNamedColor( m_warningColor.value() );
	debug.setNamedColor( m_debugColor.value() );
	info.setNamedColor( m_infoColor.value() );
	deregistered.setNamedColor( m_deregisteredColor.value() );
	disconnected.setNamedColor( m_disconnectedColor.value() );

	colorForLevel->setColors( none, critical, error, warning,
		debug, info, deregistered, disconnected );
}

} /* namespace Globe */

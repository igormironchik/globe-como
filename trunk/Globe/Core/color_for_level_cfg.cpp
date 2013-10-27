
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

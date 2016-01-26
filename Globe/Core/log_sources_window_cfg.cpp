
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

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
#include <Globe/Core/log_sources_window_cfg.hpp>


namespace Globe {

//
// LogSourcesCfg
//


LogSourcesCfg::LogSourcesCfg()
{
}

LogSourcesCfg::LogSourcesCfg( const WindowStateCfg & windowStateCfg )
	:	m_windowState( windowStateCfg )
{
}

LogSourcesCfg::LogSourcesCfg( const LogSourcesCfg & other )
	:	m_windowState( other.windowState() )
{
}

LogSourcesCfg &
LogSourcesCfg::operator = ( const LogSourcesCfg & other )
{
	if( this != &other )
	{
		m_windowState = other.windowState();
	}

	return *this;
}

const WindowStateCfg &
LogSourcesCfg::windowState() const
{
	return m_windowState;
}

void
LogSourcesCfg::setWindowState( const WindowStateCfg & cfg )
{
	m_windowState = cfg;
}


//
// LogSourcesCfgTag
//

LogSourcesCfgTag::LogSourcesCfgTag()
	:	QtConfFile::TagNoValue( QLatin1String( "logSourcesCfg" ), true )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
{
}

LogSourcesCfgTag::LogSourcesCfgTag( const LogSourcesCfg & cfg )
	:	QtConfFile::TagNoValue( QLatin1String( "logSourcesCfg" ), true )
	,	m_windowState( cfg.windowState(), *this,
			QLatin1String( "windowState" ), true )
{
	setDefined();
}

LogSourcesCfg
LogSourcesCfgTag::cfg() const
{
	LogSourcesCfg c;

	c.setWindowState( m_windowState.cfg() );

	return c;
}

} /* namespace Globe */

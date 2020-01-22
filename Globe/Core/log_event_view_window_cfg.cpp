
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

// Globe include.
#include <Globe/Core/log_event_view_window_cfg.hpp>


namespace Globe {

//
// LogEventCfg
//


LogEventCfg::LogEventCfg()
{
}

LogEventCfg::LogEventCfg( const WindowStateCfg & windowStateCfg )
	:	m_windowState( windowStateCfg )
{
}

LogEventCfg::LogEventCfg( const LogEventCfg & other )
	:	m_windowState( other.windowState() )
{
}

LogEventCfg &
LogEventCfg::operator = ( const LogEventCfg & other )
{
	if( this != &other )
	{
		m_windowState = other.windowState();
	}

	return *this;
}

const WindowStateCfg &
LogEventCfg::windowState() const
{
	return m_windowState;
}

void
LogEventCfg::setWindowState( const WindowStateCfg & cfg )
{
	m_windowState = cfg;
}


//
// LogEventCfgTag
//

LogEventCfgTag::LogEventCfgTag()
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "logEventCfg" ), true )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
{
}

LogEventCfgTag::LogEventCfgTag( const LogEventCfg & cfg )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "logEventCfg" ), true )
	,	m_windowState( cfg.windowState(), *this,
			QLatin1String( "windowState" ), true )
{
	set_defined();
}

LogEventCfg
LogEventCfgTag::cfg() const
{
	LogEventCfg c;

	c.setWindowState( m_windowState.cfg() );

	return c;
}

} /* namespace Globe */

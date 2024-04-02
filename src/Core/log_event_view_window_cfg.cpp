
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/log_event_view_window_cfg.hpp>


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

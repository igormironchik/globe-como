
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/log_sources_window_cfg.hpp>


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
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "logSourcesCfg" ), true )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
{
}

LogSourcesCfgTag::LogSourcesCfgTag( const LogSourcesCfg & cfg )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "logSourcesCfg" ), true )
	,	m_windowState( cfg.windowState(), *this,
			QLatin1String( "windowState" ), true )
{
	set_defined();
}

LogSourcesCfg
LogSourcesCfgTag::cfg() const
{
	LogSourcesCfg c;

	c.setWindowState( m_windowState.cfg() );

	return c;
}

} /* namespace Globe */

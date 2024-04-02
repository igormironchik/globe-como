
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__LOG_SOURCES_WINDOW_CFG_HPP__INCLUDED
#define GLOBE__LOG_SOURCES_WINDOW_CFG_HPP__INCLUDED

// Globe include.
#include <Core/window_state_cfg.hpp>

// cfgfile include.
#include <cfgfile/all.hpp>


namespace Globe {

//
// LogSourcesCfg
//

//! Configuration of the sources log.
class LogSourcesCfg {
public:
	LogSourcesCfg();

	explicit LogSourcesCfg( const WindowStateCfg & windowStateCfg );

	LogSourcesCfg( const LogSourcesCfg & other );

	LogSourcesCfg & operator = ( const LogSourcesCfg & other );

	//! \return Window state cfg.
	const WindowStateCfg & windowState() const;
	//! Set window state cfg.
	void setWindowState( const WindowStateCfg & cfg );

private:
	//! Window state.
	WindowStateCfg m_windowState;
}; // class LogSourcesCfg


//
// LogSourcesCfgTag
//

//! Tag with sources log configuration.
class LogSourcesCfgTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	LogSourcesCfgTag();

	explicit LogSourcesCfgTag( const LogSourcesCfg & cfg );

	//! \return Configuration.
	LogSourcesCfg cfg() const;

private:
	//! Window state.
	WindowStateCfgTag m_windowState;
}; // class LogSourcesCfgTag

} /* namespace Globe */

#endif // GLOBE__LOG_SOURCES_WINDOW_CFG_HPP__INCLUDED

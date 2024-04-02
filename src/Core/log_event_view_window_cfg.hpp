
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__LOG_EVENT_VIEW_WINDOW_CFG_HPP__INCLUDED
#define GLOBE__LOG_EVENT_VIEW_WINDOW_CFG_HPP__INCLUDED

// Globe include.
#include <Core/window_state_cfg.hpp>

// cfgfile include.
#include <cfgfile/all.hpp>


namespace Globe {

//
// LogEventCfg
//

//! Configuration of the event's log.
class LogEventCfg {
public:
	LogEventCfg();

	explicit LogEventCfg( const WindowStateCfg & windowStateCfg );

	LogEventCfg( const LogEventCfg & other );

	LogEventCfg & operator = ( const LogEventCfg & other );

	//! \return Window state cfg.
	const WindowStateCfg & windowState() const;
	//! Set window state cfg.
	void setWindowState( const WindowStateCfg & cfg );

private:
	//! Window state.
	WindowStateCfg m_windowState;
}; // class LogEventCfg


//
// LogEventCfgTag
//

//! Tag with event's log configuration.
class LogEventCfgTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	LogEventCfgTag();

	explicit LogEventCfgTag( const LogEventCfg & cfg );

	//! \return Configuration.
	LogEventCfg cfg() const;

private:
	//! Window state.
	WindowStateCfgTag m_windowState;
}; // class LogEventCfgTag

} /* namespace Globe */

#endif // GLOBE__LOG_EVENT_VIEW_WINDOW_CFG_HPP__INCLUDED

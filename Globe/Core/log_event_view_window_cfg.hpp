
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

#ifndef GLOBE__LOG_EVENT_VIEW_WINDOW_CFG_HPP__INCLUDED
#define GLOBE__LOG_EVENT_VIEW_WINDOW_CFG_HPP__INCLUDED

// Globe include.
#include <Globe/Core/window_state_cfg.hpp>

// QtConfFile include.
#include <QtConfFile/TagNoValue>


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
	:	public QtConfFile::TagNoValue
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

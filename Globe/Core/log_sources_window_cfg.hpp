
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

#ifndef GLOBE__LOG_SOURCES_WINDOW_CFG_HPP__INCLUDED
#define GLOBE__LOG_SOURCES_WINDOW_CFG_HPP__INCLUDED

// Globe include.
#include <Globe/Core/window_state_cfg.hpp>

// QtConfFile include.
#include <QtConfFile/TagNoValue>


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
	:	public QtConfFile::TagNoValue
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


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

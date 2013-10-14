
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

#ifndef GLOBE__LOG_SOURCES_WINDOW_CFG_HPP__INCLUDED
#define GLOBE__LOG_SOURCES_WINDOW_CFG_HPP__INCLUDED

// Globe include.
#include <Globe/window_state_cfg.hpp>

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

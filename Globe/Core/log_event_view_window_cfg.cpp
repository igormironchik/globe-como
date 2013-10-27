
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
	:	QtConfFile::TagNoValue( QLatin1String( "logEventCfg" ), true )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
{
}

LogEventCfgTag::LogEventCfgTag( const LogEventCfg & cfg )
	:	QtConfFile::TagNoValue( QLatin1String( "logEventCfg" ), true )
	,	m_windowState( cfg.windowState(), *this,
			QLatin1String( "windowState" ), true )
{
	setDefined();
}

LogEventCfg
LogEventCfgTag::cfg() const
{
	LogEventCfg c;

	c.setWindowState( m_windowState.cfg() );

	return c;
}

} /* namespace Globe */

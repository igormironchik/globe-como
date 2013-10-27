
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
#include <Globe/Core/log_sources_window_cfg.hpp>


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
	:	QtConfFile::TagNoValue( QLatin1String( "logSourcesCfg" ), true )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
{
}

LogSourcesCfgTag::LogSourcesCfgTag( const LogSourcesCfg & cfg )
	:	QtConfFile::TagNoValue( QLatin1String( "logSourcesCfg" ), true )
	,	m_windowState( cfg.windowState(), *this,
			QLatin1String( "windowState" ), true )
{
	setDefined();
}

LogSourcesCfg
LogSourcesCfgTag::cfg() const
{
	LogSourcesCfg c;

	c.setWindowState( m_windowState.cfg() );

	return c;
}

} /* namespace Globe */

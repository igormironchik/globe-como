
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
#include <Globe/Scheme/window_cfg.hpp>


namespace Globe {

namespace Scheme {

//
// WindowCfg
//

WindowCfg::WindowCfg()
{
}

WindowCfg::WindowCfg( const QString & schemeCfgFile,
	WindowStateCfg & windowState )
	:	m_schemeCfgFile( schemeCfgFile )
	,	m_windowState( windowState )
{
}

WindowCfg::~WindowCfg()
{
}

WindowCfg::WindowCfg( const WindowCfg & other )
	:	m_schemeCfgFile( other.schemeCfgFile() )
	,	m_windowState( other.windowStateCfg() )
{
}

WindowCfg &
WindowCfg::operator = ( const WindowCfg & other )
{
	if( this != &other )
	{
		m_schemeCfgFile = other.schemeCfgFile();
		m_windowState = other.windowStateCfg();
	}

	return *this;
}

const QString &
WindowCfg::schemeCfgFile() const
{
	return m_schemeCfgFile;
}

void
WindowCfg::setSchemeCfgFile( const QString & fileName )
{
	m_schemeCfgFile = fileName;
}

const WindowStateCfg &
WindowCfg::windowStateCfg() const
{
	return m_windowState;
}

void
WindowCfg::setWindowStateCfg( const WindowStateCfg & cfg )
{
	m_windowState = cfg;
}


//
// WindowCfgTag
//

WindowCfgTag::WindowCfgTag( const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_schemeCfgFile( *this, QLatin1String( "schemeCfgFile" ), true )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
{
}

WindowCfgTag::WindowCfgTag( const WindowCfg & cfg,
	const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_schemeCfgFile( *this, QLatin1String( "schemeCfgFile" ), true )
	,	m_windowState( cfg.windowStateCfg(), *this,
			QLatin1String( "windowState" ), true )
{
	m_schemeCfgFile.setValue( cfg.schemeCfgFile() );

	setDefined();
}

WindowCfgTag::~WindowCfgTag()
{
}

WindowCfg
WindowCfgTag::cfg() const
{
	return WindowCfg( m_schemeCfgFile.value(),
		m_windowState.cfg() );
}

} /* namespace Scheme */

} /* namespace Globe */

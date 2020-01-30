
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2020 Igor Mironchik

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

// Globe include.
#include <Scheme/window_cfg.hpp>


namespace Globe {

namespace Scheme {

//
// WindowCfg
//

WindowCfg::WindowCfg()
{
}

WindowCfg::WindowCfg( const QString & schemeCfgFile,
	const WindowStateCfg & windowState )
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
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > ( name, isMandatory )
	,	m_schemeCfgFile( *this, QLatin1String( "schemeCfgFile" ), true )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
{
}

WindowCfgTag::WindowCfgTag( const WindowCfg & cfg,
	const QString & name, bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > ( name, isMandatory )
	,	m_schemeCfgFile( *this, QLatin1String( "schemeCfgFile" ), true )
	,	m_windowState( cfg.windowStateCfg(), *this,
			QLatin1String( "windowState" ), true )
{
	m_schemeCfgFile.set_value( cfg.schemeCfgFile() );

	set_defined();
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

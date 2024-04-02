
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/mainwindow_cfg.hpp>


namespace Globe {

//
// MainWindowCfg
//

MainWindowCfg::MainWindowCfg()
	:	m_shownChannels( ShowAll )
{
}

MainWindowCfg::MainWindowCfg( const WindowStateCfg & windowState,
	ShownChannels shownChannels )
	:	m_windowState( windowState )
	,	m_shownChannels( shownChannels )
{
}

MainWindowCfg::MainWindowCfg( const MainWindowCfg & other )
	:	m_windowState( other.windowState() )
	,	m_shownChannels( other.shownChannels() )
{
}

MainWindowCfg &
MainWindowCfg::operator = ( const MainWindowCfg & other )
{
	if( this != &other )
	{
		m_windowState = other.windowState();
		m_shownChannels = other.shownChannels();
	}

	return *this;
}


const WindowStateCfg &
MainWindowCfg::windowState() const
{
	return m_windowState;
}

void
MainWindowCfg::setWindowState( const WindowStateCfg & state )
{
	m_windowState = state;
}

ShownChannels
MainWindowCfg::shownChannels() const
{
	return m_shownChannels;
}

void
MainWindowCfg::setShownChannels( ShownChannels shownChannels )
{
	m_shownChannels = shownChannels;
}


//
// ShownChannelsTag
//

static const QString showConnectedOnly = QLatin1String( "connectedOnly" );
static const QString showDisconnectedOnly = QLatin1String( "disconnectedOnly" );
static const QString showAll = QLatin1String( "showAll" );

static inline QString shownChannelsToString( ShownChannels shownChannels )
{
	if( shownChannels == ShowConnectedOnly )
		return showConnectedOnly;
	else if( shownChannels == ShowDisconnectedOnly )
		return showDisconnectedOnly;
	else
		return showAll;
}

static inline ShownChannels stringToShownChannels( const QString & v )
{
	if( v == showConnectedOnly )
		return ShowConnectedOnly;
	else if( v == showDisconnectedOnly )
		return ShowDisconnectedOnly;
	else
		return ShowAll;
}

ShownChannelsTag::ShownChannelsTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
{
	init();
}

ShownChannelsTag::ShownChannelsTag( ShownChannels shownChannels, cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
	const QString & name, bool isMandatory )
	:	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
{
	init();

	set_value( shownChannelsToString( shownChannels ) );
}

void
ShownChannelsTag::init()
{
	m_constraint.add_value( showConnectedOnly );
	m_constraint.add_value( showDisconnectedOnly );
	m_constraint.add_value( showAll );

	set_constraint( &m_constraint );
}

ShownChannels
ShownChannelsTag::shownChannels() const
{
	return stringToShownChannels( value() );
}


//
// MainWindowTag
//

MainWindowCfgTag::MainWindowCfgTag()
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "mainWindow" ), true )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
	,	m_shownChannels( *this, QLatin1String( "shownChannels" ), true )
{

}

MainWindowCfgTag::MainWindowCfgTag( const MainWindowCfg & cfg )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "mainWindow" ), true )
	,	m_windowState( cfg.windowState(), *this, QLatin1String( "windowState" ), true )
	,	m_shownChannels( cfg.shownChannels(), *this, QLatin1String( "shownChannels" ), true )
{
	set_defined();
}

MainWindowCfg
MainWindowCfgTag::cfg() const
{
	MainWindowCfg cfg;

	cfg.setWindowState( m_windowState.cfg() );
	cfg.setShownChannels( m_shownChannels.shownChannels() );

	return cfg;
}

} /* namespace Globe */

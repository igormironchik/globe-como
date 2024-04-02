
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__MAINWINDOW_CFG_HPP__INCLUDED
#define GLOBE__MAINWINDOW_CFG_HPP__INCLUDED

// Globe include.
#include <Core/window_state_cfg.hpp>
#include <Core/channels_to_show.hpp>

// cfgfile include.
#include <cfgfile/all.hpp>


namespace Globe {

//
// MainWindowCfg
//

//! Configuration of the main window.
class MainWindowCfg {
public:
	MainWindowCfg();

	MainWindowCfg( const WindowStateCfg & windowState,
		ShownChannels shownChannels );

	MainWindowCfg( const MainWindowCfg & other );

	MainWindowCfg & operator = ( const MainWindowCfg & other );

	//! \return Window state.
	const WindowStateCfg & windowState() const;
	//! Set window state.
	void setWindowState( const WindowStateCfg & state );

	//! \return Shwon channels mode.
	ShownChannels shownChannels() const;
	//! Set shown channels mode.
	void setShownChannels( ShownChannels shownChannels );

private:
	//! State of the window.
	WindowStateCfg m_windowState;
	//! Shown channels.
	ShownChannels m_shownChannels;
}; // class MainWindowCfg


//
// ShownChannelsTag
//

//! Tag with shown windows mode.
class ShownChannelsTag
	:	public cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t >
{
public:
	ShownChannelsTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	ShownChannelsTag( ShownChannels shownChannels,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	//! \return Shown channels mode.
	ShownChannels shownChannels() const;

private:
	//! Init.
	void init();

private:
	//! Constraint.
	cfgfile::constraint_one_of_t< QString > m_constraint;
}; // class ShownChannelsTag


//
// MainWindowTag
//

//! Tag with main window configuration.
class MainWindowCfgTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	MainWindowCfgTag();

	explicit MainWindowCfgTag( const MainWindowCfg & cfg );

	//! \return Main window's configuration.
	MainWindowCfg cfg() const;

private:
	//! Window state.
	WindowStateCfgTag m_windowState;
	//! Shown channels mode.
	ShownChannelsTag m_shownChannels;
}; // class MainWindowCfgTag

} /* namespace Globe */

#endif // GLOBE__MAINWINDOW_CFG_HPP__INCLUDED

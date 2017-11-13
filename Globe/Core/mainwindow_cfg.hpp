
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

#ifndef GLOBE__MAINWINDOW_CFG_HPP__INCLUDED
#define GLOBE__MAINWINDOW_CFG_HPP__INCLUDED

// Globe include.
#include <Globe/Core/window_state_cfg.hpp>
#include <Globe/Core/channels_to_show.hpp>

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

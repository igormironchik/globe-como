
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

#ifndef GLOBE__SOURCES_MAINWINDOW_CFG_HPP__INCLUDED
#define GLOBE__SOURCES_MAINWINDOW_CFG_HPP__INCLUDED

// cfgfile include.
#include <cfgfile/all.hpp>

// Globe include.
#include <Core/window_state_cfg.hpp>


namespace Globe {

//
// SourcesMainWindowTag
//

//! Tag with configuration of the sources main window.
class SourcesMainWindowTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	SourcesMainWindowTag();

	SourcesMainWindowTag( const QString & channelName,
		const WindowStateCfg & windowState );

	//! \return Channel's name.
	QString channelName() const;

	//! \return Window state.
	WindowStateCfg windowState() const;

private:
	//! Channel's name.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_channelName;
	//! State of the window.
	WindowStateCfgTag m_windowState;
}; // class SourcesMainWindowTag

} /* namespace Globe */

#endif // GLOBE__SOURCES_MAINWINDOW_CFG_HPP__INCLUDED

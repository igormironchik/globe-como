
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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

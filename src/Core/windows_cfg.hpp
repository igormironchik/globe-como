
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

#ifndef GLOBE__WINDOWS_CFG_HPP__INCLUDED
#define GLOBE__WINDOWS_CFG_HPP__INCLUDED

// cfgfile include.
#include <cfgfile/all.hpp>

// Qt include.
#include <QList>

// Globe include.
#include <Core/channel_view_window_cfg.hpp>

#include <Scheme/window_cfg.hpp>


namespace Globe {

//
// WindowsCfg
//

//! Configuration of the windows.
class WindowsCfg {
public:
	WindowsCfg();

	WindowsCfg( const QList< ChannelViewWindowCfg > & channelViewWindows,
		const QList< Scheme::WindowCfg > & schemeWindows );

	WindowsCfg( const WindowsCfg & other );

	WindowsCfg & operator = ( const WindowsCfg & other );

	//! \return Channel view windows configuration.
	const QList< ChannelViewWindowCfg > & channelViewWindows() const;
	//! Set channel view windows configuration.
	void setChannelViewWindows( const QList< ChannelViewWindowCfg > & windows );

	//! \return Scheme windows configuration.
	const QList< Scheme::WindowCfg > & schemeWindows() const;
	//! Set scheme windows configuration.
	void setSchemeWindows( const QList< Scheme::WindowCfg > & windows );

private:
	//! Channel view windows configuration.
	QList< ChannelViewWindowCfg > m_channelViewWindows;
	//! Scheme windows configuration.
	QList< Scheme::WindowCfg > m_schemeWindows;
}; // class WindowsCfg


//
// WindowsTag
//

//! Tag with windows configuration.
class WindowsTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	WindowsTag();

	explicit WindowsTag( const WindowsCfg & cfg );

	//! \return Windows configuration.
	WindowsCfg cfg() const;

private:
	//! Channel view windows configuration.
	cfgfile::tag_vector_of_tags_t< ChannelViewWindowTag,
		cfgfile::qstring_trait_t > m_channelViewWindows;
	//! Scheme windows configuration.
	cfgfile::tag_vector_of_tags_t< Scheme::WindowCfgTag,
		cfgfile::qstring_trait_t > m_schemeWindows;
}; // class WindowsTag

} /* namespace Globe */

#endif // GLOBE__WINDOWS_CFG_HPP__INCLUDED

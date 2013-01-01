
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

#ifndef GLOBE__MAINWINDOW_CFG_HPP__INCLUDED
#define GLOBE__MAINWINDOW_CFG_HPP__INCLUDED

// Globe include.
#include <Globe/window_state_cfg.hpp>
#include <Globe/channels_to_show.hpp>

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>
#include <QtConfFile/ConstraintOneOf>


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
	:	public QtConfFile::TagScalar< QString >
{
public:
	ShownChannelsTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	ShownChannelsTag( ShownChannels shownChannels, QtConfFile::Tag & owner,
		const QString & name, bool isMandatory = false );

	//! \return Shown channels mode.
	ShownChannels shownChannels() const;

private:
	//! Init.
	void init();

private:
	//! Constraint.
	QtConfFile::ConstraintOneOf< QString > m_constraint;
}; // class ShownChannelsTag


//
// MainWindowTag
//

//! Tag with main window configuration.
class MainWindowCfgTag
	:	public QtConfFile::TagNoValue
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

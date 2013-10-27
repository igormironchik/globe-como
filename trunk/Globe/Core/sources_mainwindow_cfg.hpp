
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

#ifndef GLOBE__SOURCES_MAINWINDOW_CFG_HPP__INCLUDED
#define GLOBE__SOURCES_MAINWINDOW_CFG_HPP__INCLUDED

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>

// Globe include.
#include <Globe/Core/window_state_cfg.hpp>


namespace Globe {

//
// SourcesMainWindowTag
//

//! Tag with configuration of the sources main window.
class SourcesMainWindowTag
	:	public QtConfFile::TagNoValue
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
	QtConfFile::TagScalar< QString > m_channelName;
	//! State of the window.
	WindowStateCfgTag m_windowState;
}; // class SourcesMainWindowTag

} /* namespace Globe */

#endif // GLOBE__SOURCES_MAINWINDOW_CFG_HPP__INCLUDED

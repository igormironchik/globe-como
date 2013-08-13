
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

#ifndef GLOBE__WINDOWS_CFG_HPP__INCLUDED
#define GLOBE__WINDOWS_CFG_HPP__INCLUDED

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagVectorOfTags>

// Qt include.
#include <QList>

// Globe include.
#include <Globe/channel_view_window_cfg.hpp>


namespace Globe {

//
// WindowsCfg
//

//! Configuration of the windows.
class WindowsCfg {
public:
	WindowsCfg();

	explicit WindowsCfg(
		const QList< ChannelViewWindowCfg > & channelViewWindows );

	//! \return Channel view windows configuration.
	const QList< ChannelViewWindowCfg > & channelViewWindows() const;
	//! Set channel view windows configuration.
	void setChannelViewWindows( const QList< ChannelViewWindowCfg > & windows );

private:
	//! Channel view windows configuration.
	QList< ChannelViewWindowCfg > m_channelViewWindows;
}; // class WindowsCfg


//
// WindowsTag
//

//! Tag with windows configuration.
class WindowsTag
	:	public QtConfFile::TagNoValue
{
public:
	WindowsTag();

	explicit WindowsTag( const WindowsCfg & cfg );

	//! \return Windows configuration.
	WindowsCfg cfg() const;

private:
	//! Channel view windows configuration.
	QtConfFile::TagVectorOfTags< ChannelViewWindowTag > m_channelViewWindows;
}; // class WindowsTag

} /* namespace Globe */

#endif // GLOBE__WINDOWS_CFG_HPP__INCLUDED

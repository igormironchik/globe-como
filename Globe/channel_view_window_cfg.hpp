
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

#ifndef GLOBE__CHANNEL_VIEW_WINDOW_CFG_HPP__INCLUDED
#define GLOBE__CHANNEL_VIEW_WINDOW_CFG_HPP__INCLUDED

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>

// Globe include.
#include <Globe/window_state_cfg.hpp>


namespace Globe {

//
// ChannelViewWindowCfg
//

//! Configuration of the channel view window.
class ChannelViewWindowCfg {
public:
	ChannelViewWindowCfg();

	ChannelViewWindowCfg( const QString & channelName,
		const WindowStateCfg & windowCfg );

	~ChannelViewWindowCfg();

	//! \return Name of the channel.
	const QString & channelName() const;
	//! Set name of the channel.
	void setChannelName( const QString & name );

	//! \return Window state cfg.
	const WindowStateCfg & windowStateCfg() const;
	//! Set window state cfg.
	void setWindowStateCfg( const WindowStateCfg & cfg );

private:
	//! Name of the channel.
	QString m_channelName;
	//! Window state cfg.
	WindowStateCfg m_windowState;
}; // class ChannelViewWindowCfg


//
// ChannelViewWindowTag
//

//! Tag with configuration of the channel view window.
class ChannelViewWindowTag
	:	public QtConfFile::TagNoValue
{
public:
	explicit ChannelViewWindowTag( const QString & name, bool isMandatory = false );

	ChannelViewWindowTag( const ChannelViewWindowCfg & cfg,
		const QString & name, bool isMandatory = false );

	~ChannelViewWindowTag();

	//! \return Configuration.
	ChannelViewWindowCfg cfg() const;

private:
	//! Name of the channel.
	QtConfFile::TagScalar< QString > m_channelName;
	//! Window state cfg.
	WindowStateCfgTag m_windowState;
}; // class ChannelViewWindowCfg

} /* namespace Globe */

#endif // GLOBE__CHANNEL_VIEW_WINDOW_CFG_HPP__INCLUDED

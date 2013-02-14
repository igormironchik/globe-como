
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

// Globe include.
#include <Globe/channel_view_window_cfg.hpp>


namespace Globe {

//
// ChannelViewWindowCfg
//

ChannelViewWindowCfg::ChannelViewWindowCfg()
{
}

ChannelViewWindowCfg::ChannelViewWindowCfg( const QString & channelName,
	const WindowStateCfg & windowCfg )
	:	m_channelName( channelName )
	,	m_windowState( windowCfg )
{
}

ChannelViewWindowCfg::~ChannelViewWindowCfg()
{
}

const QString &
ChannelViewWindowCfg::channelName() const
{
	return m_channelName;
}

void
ChannelViewWindowCfg::setChannelName( const QString & name )
{
	m_channelName = name;
}

const WindowStateCfg &
ChannelViewWindowCfg::windowStateCfg() const
{
	return m_windowState;
}

void
ChannelViewWindowCfg::setWindowStateCfg( const WindowStateCfg & cfg )
{
	m_windowState = cfg;
}


//
// ChannelViewWindowTag
//

ChannelViewWindowTag::ChannelViewWindowTag( const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_channelName( *this, QLatin1String( "channelName" ), true )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
{
}

ChannelViewWindowTag::ChannelViewWindowTag( const ChannelViewWindowCfg & cfg,
	const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_channelName( *this, QLatin1String( "channelName" ), true )
	,	m_windowState( cfg.windowStateCfg(), *this,
			QLatin1String( "windowState" ), true )
{
	m_channelName.setValue( cfg.channelName() );

	setDefined();
}

ChannelViewWindowTag::~ChannelViewWindowTag()
{
}

ChannelViewWindowCfg
ChannelViewWindowTag::cfg() const
{
	ChannelViewWindowCfg cfg;

	cfg.setChannelName( m_channelName.value() );
	cfg.setWindowStateCfg( m_windowState.cfg() );

	return cfg;
}

} /* namespace Globe */

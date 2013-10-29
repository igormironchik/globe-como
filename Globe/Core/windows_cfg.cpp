
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
#include <Globe/Core/windows_cfg.hpp>


namespace Globe {

//
// WindowsCfg
//

WindowsCfg::WindowsCfg()
{
}

WindowsCfg::WindowsCfg(	const QList< ChannelViewWindowCfg > & channelViewWindows,
	const QList< Scheme::WindowCfg > & schemeWindows )
	:	m_channelViewWindows( channelViewWindows )
	,	m_schemeWindows( schemeWindows )
{
}

WindowsCfg::WindowsCfg( const WindowsCfg & other )
	:	m_channelViewWindows( other.channelViewWindows() )
	,	m_schemeWindows( other.schemeWindows() )
{
}

WindowsCfg &
WindowsCfg::operator = ( const WindowsCfg & other )
{
	if( this != &other )
	{
		m_channelViewWindows = other.channelViewWindows();
		m_schemeWindows = other.schemeWindows();
	}

	return *this;
}

const QList< ChannelViewWindowCfg > &
WindowsCfg::channelViewWindows() const
{
	return m_channelViewWindows;
}

void
WindowsCfg::setChannelViewWindows( const QList< ChannelViewWindowCfg > & windows )
{
	m_channelViewWindows = windows;
}

const QList< Scheme::WindowCfg > &
WindowsCfg::schemeWindows() const
{
	return m_schemeWindows;
}

void
WindowsCfg::setSchemeWindows( const QList< Scheme::WindowCfg > & windows )
{
	m_schemeWindows = windows;
}


//
// WindowsTag
//

static const QString channelViewWindowTagName =
	QLatin1String( "channelViewWindow" );
static const QString schemeWindowTagName =
	QLatin1String( "schemeWindow" );

WindowsTag::WindowsTag()
	:	QtConfFile::TagNoValue( QLatin1String( "windowsCfg" ), true )
	,	m_channelViewWindows( *this, channelViewWindowTagName, false )
	,	m_schemeWindows( *this, schemeWindowTagName, false )
{
}

WindowsTag::WindowsTag( const WindowsCfg & cfg )
	:	QtConfFile::TagNoValue( QLatin1String( "windowsCfg" ), true )
	,	m_channelViewWindows( *this, channelViewWindowTagName, false )
	,	m_schemeWindows( *this, schemeWindowTagName, false )
{
	foreach( const ChannelViewWindowCfg & w, cfg.channelViewWindows() )
	{
		QtConfFile::TagVectorOfTags< ChannelViewWindowTag >::PointerToTag
			t( new ChannelViewWindowTag( w, channelViewWindowTagName ) );

		m_channelViewWindows.setValue( t );
	}

	foreach( const Scheme::WindowCfg & w, cfg.schemeWindows() )
	{
		QtConfFile::TagVectorOfTags< Scheme::WindowCfgTag >::PointerToTag
			t( new Scheme::WindowCfgTag( w, schemeWindowTagName ) );

		m_schemeWindows.setValue( t );
	}

	setDefined();
}

WindowsCfg
WindowsTag::cfg() const
{
	WindowsCfg cfg;

	QList< ChannelViewWindowCfg > channelViewWindows;

	foreach( QtConfFile::TagVectorOfTags< ChannelViewWindowTag >::PointerToTag t,
		m_channelViewWindows.values() )
	{
		channelViewWindows.append( t->cfg() );
	}

	cfg.setChannelViewWindows( channelViewWindows );

	QList< Scheme::WindowCfg > schemeWindows;

	foreach( QtConfFile::TagVectorOfTags< Scheme::WindowCfgTag >::PointerToTag t,
		m_schemeWindows.values() )
	{
		schemeWindows.append( t->cfg() );
	}

	cfg.setSchemeWindows( schemeWindows );

	return cfg;
}

} /* namespace Globe */

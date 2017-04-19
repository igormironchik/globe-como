
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

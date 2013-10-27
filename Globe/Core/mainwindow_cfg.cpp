
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
#include <Globe/Core/mainwindow_cfg.hpp>


namespace Globe {

//
// MainWindowCfg
//

MainWindowCfg::MainWindowCfg()
	:	m_shownChannels( ShowAll )
{
}

MainWindowCfg::MainWindowCfg( const WindowStateCfg & windowState,
	ShownChannels shownChannels )
	:	m_windowState( windowState )
	,	m_shownChannels( shownChannels )
{
}

MainWindowCfg::MainWindowCfg( const MainWindowCfg & other )
	:	m_windowState( other.windowState() )
	,	m_shownChannels( other.shownChannels() )
{
}

MainWindowCfg &
MainWindowCfg::operator = ( const MainWindowCfg & other )
{
	if( this != &other )
	{
		m_windowState = other.windowState();
		m_shownChannels = other.shownChannels();
	}

	return *this;
}


const WindowStateCfg &
MainWindowCfg::windowState() const
{
	return m_windowState;
}

void
MainWindowCfg::setWindowState( const WindowStateCfg & state )
{
	m_windowState = state;
}

ShownChannels
MainWindowCfg::shownChannels() const
{
	return m_shownChannels;
}

void
MainWindowCfg::setShownChannels( ShownChannels shownChannels )
{
	m_shownChannels = shownChannels;
}


//
// ShownChannelsTag
//

static const QString showConnectedOnly = QLatin1String( "connectedOnly" );
static const QString showDisconnectedOnly = QLatin1String( "disconnectedOnly" );
static const QString showAll = QLatin1String( "showAll" );

static inline QString shownChannelsToString( ShownChannels shownChannels )
{
	if( shownChannels == ShowConnectedOnly )
		return showConnectedOnly;
	else if( shownChannels == ShowDisconnectedOnly )
		return showDisconnectedOnly;
	else
		return showAll;
}

static inline ShownChannels stringToShownChannels( const QString & v )
{
	if( v == showConnectedOnly )
		return ShowConnectedOnly;
	else if( v == showDisconnectedOnly )
		return ShowDisconnectedOnly;
	else
		return ShowAll;
}

ShownChannelsTag::ShownChannelsTag( QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagScalar< QString > ( owner, name, isMandatory )
{
	init();
}

ShownChannelsTag::ShownChannelsTag( ShownChannels shownChannels, QtConfFile::Tag & owner,
	const QString & name, bool isMandatory )
	:	QtConfFile::TagScalar< QString > ( owner, name, isMandatory )
{
	init();

	setValue( shownChannelsToString( shownChannels ) );
}

void
ShownChannelsTag::init()
{
	m_constraint.addValue( showConnectedOnly );
	m_constraint.addValue( showDisconnectedOnly );
	m_constraint.addValue( showAll );

	setConstraint( &m_constraint );
}

ShownChannels
ShownChannelsTag::shownChannels() const
{
	return stringToShownChannels( value() );
}


//
// MainWindowTag
//

MainWindowCfgTag::MainWindowCfgTag()
	:	QtConfFile::TagNoValue( QLatin1String( "mainWindow" ), true )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
	,	m_shownChannels( *this, QLatin1String( "shownChannels" ), true )
{

}

MainWindowCfgTag::MainWindowCfgTag( const MainWindowCfg & cfg )
	:	QtConfFile::TagNoValue( QLatin1String( "mainWindow" ), true )
	,	m_windowState( cfg.windowState(), *this, QLatin1String( "windowState" ), true )
	,	m_shownChannels( cfg.shownChannels(), *this, QLatin1String( "shownChannels" ), true )
{
	setDefined();
}

MainWindowCfg
MainWindowCfgTag::cfg() const
{
	MainWindowCfg cfg;

	cfg.setWindowState( m_windowState.cfg() );
	cfg.setShownChannels( m_shownChannels.shownChannels() );

	return cfg;
}

} /* namespace Globe */

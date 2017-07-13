
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
#include <Globe/Core/globe_menu.hpp>
#include <Globe/Core/channel_view_window.hpp>
#include <Globe/Core/mainwindow.hpp>

#include <Globe/Scheme/window.hpp>

// Qt include.
#include <QMenu>
#include <QWidget>


namespace Globe {

//
// WindowsList
//

WindowsList::WindowsList( const QList< ChannelViewWindow* > & channelViewWindows,
	const QList< Scheme::Window* > & schemeWindows,
	const QList< Scheme::Window* > &  aggregates,
	MainWindow * main )
	:	m_channelViewWindows( channelViewWindows )
	,	m_schemeWindows( schemeWindows )
	,	m_aggregates( aggregates )
	,	m_main( main )
{
}


//
// Menu
//

Menu::Menu( QMenu * fileMenu, QMenu * settingsMenu,
	const QList< ToolWindowObject* > toolWindows,
	const WindowsList & windows, QMenu * help )
	:	m_fileMenu( fileMenu )
	,	m_settingsMenu( settingsMenu )
	,	m_toolWindows( toolWindows )
	,	m_windows( windows )
	,	m_help( help )
{
}

QMenu *
Menu::fileMenu() const
{
	return m_fileMenu;
}

QMenu *
Menu::settingsMenu() const
{
	return m_settingsMenu;
}

const QList< ToolWindowObject* > &
Menu::toolWindows() const
{
	return m_toolWindows;
}

const WindowsList &
Menu::windows() const
{
	return m_windows;
}

QMenu *
Menu::helpMenu() const
{
	return m_help;
}


//
// WindowsMenu
//

WindowsMenu::WindowsMenu( QMenu * menu, QWidget * thisWindow,
	const WindowsList & windows, QObject * parent )
	:	QObject( parent )
	,	m_menu( menu )
	,	m_thisWindow( thisWindow )
	,	m_windows( windows )
{
	initMenu();

	connect( m_menu, &QMenu::triggered,
		this, &WindowsMenu::showWindow );
}

WindowsMenu::~WindowsMenu()
{
}

void
WindowsMenu::update()
{
	initMenu();
}

void
WindowsMenu::showWindow( QAction * a )
{
	if( m_map.contains( a ) )
	{
		m_map[ a ]->setWindowState( Qt::WindowActive );
		m_map[ a ]->raise();
		m_map[ a ]->setFocus();
	}
}

void
WindowsMenu::initMenu()
{
	m_map.clear();
	m_menu->clear();

	QMenu * scheme = m_menu->addMenu( tr( "Scheme" ) );

	connect( scheme, &QMenu::triggered, this, &WindowsMenu::showWindow );

	for( auto * w : qAsConst( m_windows.m_schemeWindows ) )
	{
		if( w != m_thisWindow )
		{
			QAction * a = scheme->addAction( w->cfgFile() );

			m_map.insert( a, w );
		}
	}

	QMenu * ch = m_menu->addMenu( tr( "Channel" ) );

	connect( ch, &QMenu::triggered, this, &WindowsMenu::showWindow );

	for( auto * w : qAsConst( m_windows.m_channelViewWindows ) )
	{
		if( w != m_thisWindow )
		{
			QAction * a = ch->addAction( w->channel() );

			m_map.insert( a, w );
		}
	}

	QMenu * agg = m_menu->addMenu( tr( "Aggregate" ) );

	connect( agg, &QMenu::triggered, this, &WindowsMenu::showWindow );

	for( auto * w : qAsConst( m_windows.m_aggregates ) )
	{
		if( w != m_thisWindow )
		{
			QAction * a = agg->addAction( w->schemeName() );

			m_map.insert( a, w );
		}
	}

	if( m_thisWindow != m_windows.m_main )
	{
		m_menu->addSeparator();

		QAction * a = m_menu->addAction( tr( "Main Window" ) );

		m_map.insert( a, m_windows.m_main );
	}
}

} /* namespace Globe */

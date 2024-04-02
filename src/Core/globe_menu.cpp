
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/globe_menu.hpp>
#include <Core/channel_view_window.hpp>
#include <Core/mainwindow.hpp>

#include <Scheme/window.hpp>

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

	for( auto * w : std::as_const( m_windows.m_schemeWindows ) )
	{
		if( w != m_thisWindow )
		{
			QAction * a = scheme->addAction( w->cfgFile() );

			m_map.insert( a, w );
		}
	}

	QMenu * ch = m_menu->addMenu( tr( "Channel" ) );

	connect( ch, &QMenu::triggered, this, &WindowsMenu::showWindow );

	for( auto * w : std::as_const( m_windows.m_channelViewWindows ) )
	{
		if( w != m_thisWindow )
		{
			QAction * a = ch->addAction( w->channel() );

			m_map.insert( a, w );
		}
	}

	QMenu * agg = m_menu->addMenu( tr( "Aggregate" ) );

	connect( agg, &QMenu::triggered, this, &WindowsMenu::showWindow );

	for( auto * w : std::as_const( m_windows.m_aggregates ) )
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

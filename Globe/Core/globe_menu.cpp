
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


namespace Globe {

//
// Menu
//

Menu::Menu()
	:	m_fileMenu( 0 )
	,	m_settingsMenu( 0 )
{
}

Menu::Menu( QMenu * fileMenu, QMenu * settingsMenu,
	const QList< ToolWindowObject* > toolWindows )
	:	m_fileMenu( fileMenu )
	,	m_settingsMenu( settingsMenu )
	,	m_toolWindows( toolWindows )
{
}

Menu::Menu( const Menu & other )
	:	m_fileMenu( other.fileMenu() )
	,	m_settingsMenu( other.settingsMenu() )
	,	m_toolWindows( other.toolWindows() )
{
}

Menu &
Menu::operator = ( const Menu & other )
{
	if( this != &other )
	{
		m_fileMenu = other.fileMenu();
		m_settingsMenu = other.settingsMenu();
		m_toolWindows = other.toolWindows();
	}

	return *this;
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

} /* namespace Globe */

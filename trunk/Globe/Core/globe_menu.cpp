
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

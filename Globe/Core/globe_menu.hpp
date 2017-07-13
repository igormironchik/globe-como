
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

#ifndef GLOBE__GLOBE_MENU_HPP__INCLUDED
#define GLOBE__GLOBE_MENU_HPP__INCLUDED

// Qt include.
#include <QtGlobal>
#include <QList>

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_NAMESPACE


namespace Globe {

class ToolWindowObject;
class ChannelViewWindow;

namespace Scheme {

class Window;

} /* namespace Scheme */


//
// WindowsList
//

//! List of all windows in application.
struct WindowsList {

	WindowsList( const QList< ChannelViewWindow* > & channelViewWindows,
		const QList< Scheme::Window* > & schemeWindows,
		const QList< Scheme::Window* > &  aggregates );

	//! Channel view windows.
	const QList< ChannelViewWindow* > & m_channelViewWindows;
	//! Scheme windows.
	const QList< Scheme::Window* > & m_schemeWindows;
	//! Aggregate windows.
	const QList< Scheme::Window* > & m_aggregates;
}; // struct WindowsList


//
// Menu
//

//! Components of the menu of application.
class Menu {
public:
	Menu( QMenu * fileMenu, QMenu * settingsMenu,
		const QList< ToolWindowObject* > toolWindows,
		const WindowsList & windows );

	//! \return File menu.
	QMenu * fileMenu() const;

	//! \return Settings menu.
	QMenu * settingsMenu() const;

	//! \return List with tool window objects.
	const QList< ToolWindowObject* > & toolWindows() const;

	//! \return List of all windows.
	const WindowsList & windows() const;

private:
	//! File menu.
	QMenu * m_fileMenu;
	//! Settings menu.
	QMenu * m_settingsMenu;
	//! Tool windows objects.
	QList< ToolWindowObject* > m_toolWindows;
	//! All windows.
	const WindowsList & m_windows;
}; // class Menu

} /* namespace Globe */

#endif // GLOBE__GLOBE_MENU_HPP__INCLUDED

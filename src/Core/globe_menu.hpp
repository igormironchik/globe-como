
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__GLOBE_MENU_HPP__INCLUDED
#define GLOBE__GLOBE_MENU_HPP__INCLUDED

// Qt include.
#include <QtGlobal>
#include <QList>
#include <QObject>
#include <QMap>

QT_BEGIN_NAMESPACE
class QMenu;
class QWidget;
class QAction;
QT_END_NAMESPACE


namespace Globe {

class ToolWindowObject;
class ChannelViewWindow;
class MainWindow;

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
		const QList< Scheme::Window* > &  aggregates,
		MainWindow * main );

	//! Channel view windows.
	const QList< ChannelViewWindow* > & m_channelViewWindows;
	//! Scheme windows.
	const QList< Scheme::Window* > & m_schemeWindows;
	//! Aggregate windows.
	const QList< Scheme::Window* > & m_aggregates;
	//! Main window.
	MainWindow * m_main;
}; // struct WindowsList


//
// Menu
//

//! Components of the menu of application.
class Menu {
public:
	Menu( QMenu * fileMenu, QMenu * settingsMenu,
		const QList< ToolWindowObject* > toolWindows,
		const WindowsList & windows,
		QMenu * help );

	//! \return File menu.
	QMenu * fileMenu() const;

	//! \return Settings menu.
	QMenu * settingsMenu() const;

	//! \return List with tool window objects.
	const QList< ToolWindowObject* > & toolWindows() const;

	//! \return List of all windows.
	const WindowsList & windows() const;

	//! \return Help menu.
	QMenu * helpMenu() const;

private:
	//! File menu.
	QMenu * m_fileMenu;
	//! Settings menu.
	QMenu * m_settingsMenu;
	//! Tool windows objects.
	QList< ToolWindowObject* > m_toolWindows;
	//! All windows.
	const WindowsList & m_windows;
	//! Help menu.
	QMenu * m_help;
}; // class Menu


//
// WindowsMenu
//

//! Auxiliary class to create and work with windows menu.
class WindowsMenu Q_DECL_FINAL
	:	public QObject
{
	Q_OBJECT

public:
	WindowsMenu( QMenu * menu, QWidget * thisWindow,
		const WindowsList & windows,
		QObject * parent = Q_NULLPTR );
	~WindowsMenu();

public slots:
	//! Update menu.
	void update();

private slots:
	//! Show window.
	void showWindow( QAction * a );

private:
	//! Init menu.
	void initMenu();

private:
	Q_DISABLE_COPY( WindowsMenu )

	//! QAction -> Window map.
	QMap< QAction*, QWidget* > m_map;
	//! Menu.
	QMenu * m_menu;
	//! This window.
	QWidget * m_thisWindow;
	//! Windows.
	const WindowsList & m_windows;
}; // class WindowsMenu

} /* namespace Globe */

#endif // GLOBE__GLOBE_MENU_HPP__INCLUDED

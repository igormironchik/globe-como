
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__WITH_MENU_HPP__INCLUDED
#define GLOBE__WITH_MENU_HPP__INCLUDED


namespace Globe {

class Menu;


//
// WithMenu
//

//! Base interface for tool window.
class WithMenu {
public:
	WithMenu();

	virtual ~WithMenu();

	//! Init menu.
	virtual void initMenu( const Menu & menu ) = 0;
}; // class WithMenu

} /* namespace Globe */

#endif // GLOBE__WITH_MENU_HPP__INCLUDED

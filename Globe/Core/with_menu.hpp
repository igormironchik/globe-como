
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

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

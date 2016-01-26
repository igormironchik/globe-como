
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

#ifndef GLOBE__TOOL_WINDOW_HPP__INCLUDED
#define GLOBE__TOOL_WINDOW_HPP__INCLUDED

// Globe include.
#include <Globe/Core/with_menu.hpp>


namespace Globe {

class ToolWindowObject;


//
// ToolWindow
//

//! Base interface for tool window.
class ToolWindow
	:	public WithMenu
{
public:
	ToolWindow();

	virtual ~ToolWindow();

	//! \return Tool window object.
	virtual ToolWindowObject * toolWindowObject() = 0;
}; // class ToolWindow

} /* namespace Globe */

#endif // GLOBE__TOOL_WINDOW_HPP__INCLUDED

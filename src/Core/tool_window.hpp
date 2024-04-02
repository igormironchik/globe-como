
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__TOOL_WINDOW_HPP__INCLUDED
#define GLOBE__TOOL_WINDOW_HPP__INCLUDED

// Globe include.
#include <Core/with_menu.hpp>


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

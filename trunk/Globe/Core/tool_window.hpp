
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

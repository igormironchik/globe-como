
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
#include <Globe/scheme/window.hpp>

// Qt include.
#include <QCloseEvent>


namespace Globe {

namespace Scheme {

//
// WindowPrivate
//

class WindowPrivate {
public:
	WindowPrivate()
	{
	}
}; // class WindowPrivate


//
// Window
//

Window::Window( QWidget * parent, Qt::WindowFlags f )
	:	QMainWindow( parent, f )
	,	d( new WindowPrivate )
{
	init();
}

Window::~Window()
{
}

void
Window::initMenu( const Menu & menu )
{

}

void
Window::closeEvent( QCloseEvent * event )
{
	event->accept();
}

void
Window::init()
{

}

} /* namespace Scheme */

} /* namespace Globe */

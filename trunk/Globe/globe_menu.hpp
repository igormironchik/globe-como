
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


//
// Menu
//

//! Components of the menu of application.
class Menu {
public:
	Menu();

	Menu( QMenu * fileMenu, QMenu * settingsMenu,
		const QList< ToolWindowObject* > toolWindows );

	Menu( const Menu & other );

	Menu & operator = ( const Menu & other );

	//! \return File menu.
	QMenu * fileMenu() const;

	//! \return Settings menu.
	QMenu * settingsMenu() const;

	//! \return List with tool window objects.
	const QList< ToolWindowObject* > & toolWindows() const;

private:
	//! File menu.
	QMenu * m_fileMenu;
	//! Settings menu.
	QMenu * m_settingsMenu;
	//! Tool windows objects.
	QList< ToolWindowObject* > m_toolWindows;
};

} /* namespace Globe */

#endif // GLOBE__GLOBE_MENU_HPP__INCLUDED

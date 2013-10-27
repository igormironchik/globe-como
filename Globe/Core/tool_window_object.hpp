
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

#ifndef GLOBE__TOOL_WINDOW_OBJECT_HPP__INCLUDED
#define GLOBE__TOOL_WINDOW_OBJECT_HPP__INCLUDED

// Qt include.
#include <QObject>

QT_BEGIN_NAMESPACE
class QAction;
class QMainWindow;
QT_END_NAMESPACE


namespace Globe {

//
// ToolWindowObject
//

/*!
	This type of object provides information for the tools menu
	and is for the shown'hide operations of the tool window.
*/
class ToolWindowObject
	:	public QObject
{
	Q_OBJECT

public:
	ToolWindowObject( QAction * action, QMainWindow * toolWindow,
		QObject * parent = 0 );

	//! \return Action for the menu.
	QAction * menuEntity();

private slots:
	//! Show window.
	void showToolWindow();

private:
	//! Tool window.
	QMainWindow * m_toolWindow;
	//! Action.
	QAction * m_action;
}; // class ToolWindowObject

} /* namespace Globe */

#endif // GLOBE__TOOL_WINDOW_OBJECT_HPP__INCLUDED

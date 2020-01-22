
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2020 Igor Mironchik

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

#ifndef GLOBE__TOOL_WINDOW_OBJECT_HPP__INCLUDED
#define GLOBE__TOOL_WINDOW_OBJECT_HPP__INCLUDED

// Qt include.
#include <QObject>

QT_BEGIN_NAMESPACE
class QAction;
class QMainWindow;
QT_END_NAMESPACE

// Globe include.
#include <Globe/Core/export.hpp>


namespace Globe {

//
// ToolWindowObject
//

/*!
	This type of object provides information for the tools menu
	and is for the shown'hide operations of the tool window.
*/
class CORE_EXPORT ToolWindowObject
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

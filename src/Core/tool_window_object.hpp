
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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
#include <Core/export.hpp>


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

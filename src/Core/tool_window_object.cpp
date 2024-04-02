
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include
#include <Core/tool_window_object.hpp>

// Qt include.
#include <QAction>
#include <QMainWindow>


namespace Globe {

//
// ToolWindowObject
//

ToolWindowObject::ToolWindowObject( QAction * action, QMainWindow * toolWindow,
	QObject * parent )
	:	QObject( parent )
	,	m_toolWindow( toolWindow )
	,	m_action( action )
{
	connect( action, &QAction::triggered,
		this, &ToolWindowObject::showToolWindow );
}

QAction *
ToolWindowObject::menuEntity()
{
	return m_action;
}

void
ToolWindowObject::showToolWindow()
{
	if( m_toolWindow->isHidden() )
		m_toolWindow->show();
	else if( m_toolWindow->isMinimized() )
		m_toolWindow->showNormal();

	m_toolWindow->activateWindow();
}

} /* namespace Globe */

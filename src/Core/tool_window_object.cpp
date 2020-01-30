
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

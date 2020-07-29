
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

#ifndef GLOBE__SOURCES_MAINWINDOW_HPP__INCLUDED
#define GLOBE__SOURCES_MAINWINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Core/tool_window.hpp>
#include <Core/export.hpp>


namespace Globe {

//
// SourcesMainWindow
//

class SourcesMainWindowPrivate;

//! Main window with show all sources available in the application.
class CORE_EXPORT SourcesMainWindow
	:	public QMainWindow
	,	public ToolWindow
{
	Q_OBJECT

private:
	SourcesMainWindow( QWidget * parent = 0, Qt::WindowFlags flags = Qt::WindowFlags() );

	~SourcesMainWindow();

	static void cleanup();

public:
	//! \return Instance.
	static SourcesMainWindow & instance();

	//! \return Tool window object.
	ToolWindowObject * toolWindowObject();

	//! Save properties manager configuration.
	void saveConfiguration( const QString & fileName );
	//! Read properties manager configuration.
	void readConfiguration( const QString & fileName );

	//! Init menu.
	void initMenu( const Menu & menu );

protected:
	void closeEvent( QCloseEvent * event );

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( SourcesMainWindow )

	QScopedPointer< SourcesMainWindowPrivate > d;
}; // class SourcesMainWindow

} /* namespace Globe */

#endif // GLOBE__SOURCES_MAINWINDOW_HPP__INCLUDED

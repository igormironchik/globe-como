
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

#ifndef GLOBE__LOG_EVENT_VIEW_WINDOW_HPP__INCLUDED
#define GLOBE__LOG_EVENT_VIEW_WINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Core/log_event_view_model.hpp>
#include <Core/tool_window.hpp>
#include <Core/export.hpp>


namespace Globe {

//
// LogEventWindow
//

class LogEventWindowPrivate;

//! Window with event log.
class CORE_EXPORT LogEventWindow
	:	public QMainWindow
	,	public ToolWindow
{
	Q_OBJECT

private:
	LogEventWindow( QWidget * parent = 0, Qt::WindowFlags flags = Qt::WindowFlags() );

	~LogEventWindow();

	static void cleanup();

public:
	//! \return Instance.
	static LogEventWindow & instance();

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
	//! Set navigation buttons.
	void setNavigationButtons();
	//! \return List with log records.
	QList< LogEventRecord > readLog();
	//! \return List with log records.
	QList< LogEventRecord > readLogFirstTime();

private slots:
	//! Select from log.
	void selectFromLog();
	//! Next log page.
	void nextLogPage();
	//! Previous log page.
	void prevLogPage();
	//! Go to the first log page.
	void goToFirstLogPage();
	//! Go to the last log page.
	void goToLastLogPage();

private:
	Q_DISABLE_COPY( LogEventWindow )

	QScopedPointer< LogEventWindowPrivate > d;
}; // class LogEventWindow

} /* namespace Globe */

#endif // GLOBE__LOG_EVENT_VIEW_WINDOW_HPP__INCLUDED

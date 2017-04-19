
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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
#ifndef GLOBE__LOG_SOURCES_WINDOW_HPP__INCLUDED
#define GLOBE__LOG_SOURCES_WINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Globe/Core/log_sources_model.hpp>
#include <Globe/Core/tool_window.hpp>


namespace Globe {

//
// LogSourcesWindow
//

class LogSourcesWindowPrivate;

//! Window with event log.
class LogSourcesWindow
	:	public QMainWindow
	,	public ToolWindow
{
	Q_OBJECT

private:
	LogSourcesWindow( QWidget * parent = 0, Qt::WindowFlags flags = 0 );

	~LogSourcesWindow();

	static void cleanup();

public:
	//! \return Instance.
	static LogSourcesWindow & instance();

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
	QList< LogSourcesRecord > readLog();
	//! \return List with log records.
	QList< LogSourcesRecord > readLogFirstTime();

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
	Q_DISABLE_COPY( LogSourcesWindow )

	QScopedPointer< LogSourcesWindowPrivate > d;
}; // class LogSourcesWindow

} /* namespace Globe */

#endif // GLOBE__LOG_SOURCES_WINDOW_HPP__INCLUDED

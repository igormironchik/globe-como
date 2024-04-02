
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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

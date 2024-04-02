
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/
#ifndef GLOBE__LOG_SOURCES_WINDOW_HPP__INCLUDED
#define GLOBE__LOG_SOURCES_WINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Core/log_sources_model.hpp>
#include <Core/tool_window.hpp>
#include <Core/export.hpp>


namespace Globe {

//
// LogSourcesWindow
//

class LogSourcesWindowPrivate;

//! Window with event log.
class CORE_EXPORT LogSourcesWindow
	:	public QMainWindow
	,	public ToolWindow
{
	Q_OBJECT

private:
	LogSourcesWindow( QWidget * parent = 0, Qt::WindowFlags flags = Qt::WindowFlags() );

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


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

#ifndef LOGVIEWER__MAINWINDOW_HPP__INCLUDED
#define LOGVIEWER__MAINWINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Globe/Core/log_event_view_model.hpp>


namespace LogViewer {

//
// MainWindow
//

class MainWindowPrivate;

//! Window with event log.
class MainWindow
	:	public QMainWindow
{
	Q_OBJECT

private:
	MainWindow( QWidget * parent = 0, Qt::WindowFlags flags = 0 );

	~MainWindow();

	static void cleanup();

public:
	//! \return Instance.
	static MainWindow & instance();

private:
	//! Init.
	void init();
	//! Set navigation buttons.
	void setNavigationButtons();
	//! \return List with log records.
	QList< Globe::LogEventRecord > readLog();
	//! \return List with log records.
	QList< Globe::LogEventRecord > readLogFirstTime();

public slots:
	//! Start application.
	void start();

private slots:
	//! Error in configuration.
	void cfgError( const QString & what );
	//! Error in log.
	void logError();
	//! Log is ready.
	void logReady();
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
	Q_DISABLE_COPY( MainWindow )

	QScopedPointer< MainWindowPrivate > d;
}; // class MainWindow

} /* namespace LogViewer */

#endif // LOGVIEWER__MAINWINDOW_HPP__INCLUDED


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef LOGVIEWER__MAINWINDOW_HPP__INCLUDED
#define LOGVIEWER__MAINWINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Core/log_event_view_model.hpp>


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
	MainWindow( QWidget * parent = 0, Qt::WindowFlags flags = Qt::WindowFlags() );

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

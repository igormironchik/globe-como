
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef COMO__SAMPLES__QLISTVIEW_CLIENT__MAINWINDOW_HPP__INCLUDED
#define COMO__SAMPLES__QLISTVIEW_CLIENT__MAINWINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>


namespace Como {
	class ClientSocket;
} /* namespace Como */


//
// MainWindow
//

//! Main window of the exaple.
class MainWindow
	:	public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow( Como::ClientSocket * socket,
		QWidget * parent = 0, Qt::WindowFlags flags = Qt::WindowFlags() );
	~MainWindow();

private slots:
	//! Quit the application.
	void slotQuit();
	//! Connected to the server.
	void slotConnected();
	//! Disconnected from server.
	void slotDisconnected();

private:
	void init();

private:
	Q_DISABLE_COPY( MainWindow )

	struct MainWindowPrivate;
	QScopedPointer< MainWindowPrivate > d;
}; // class MainWindow

#endif // COMO__SAMPLES__QLISTVIEW_CLIENT__MAINWINDOW_HPP__INCLUDED

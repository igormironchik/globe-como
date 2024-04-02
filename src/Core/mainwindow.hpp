
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__MAINWINDOW_HPP__INCLUDED
#define GLOBE__MAINWINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Core/windows_cfg.hpp>
#include <Core/export.hpp>


QT_BEGIN_NAMESPACE
class QSessionManager;
QT_END_NAMESPACE


namespace Globe {

namespace Scheme {
	class Window;
} /* namespace Scheme */

class WindowStateCfg;
class ToolWindowObject;
class ChannelsList;
class ChannelViewWindow;
class Menu;

class MainWindowPrivate;

//
// MainWindow
//

//! Main window of the application.
class CORE_EXPORT MainWindow
	:	public QMainWindow
{
	Q_OBJECT

signals:
	//! New window created.
	void windowCreated( QWidget * );
	//! Window closed.
	void windowClosed( QWidget * );

private:
	MainWindow( QWidget * parent = 0, Qt::WindowFlags flags = Qt::WindowFlags() );

	~MainWindow();

	static void cleanup();

public:
	//! \return Instance.
	static MainWindow & instance();

	//! \return List with channels.
	ChannelsList * list();

	//! Channel view window was closed.
	void channelViewWindowClosed( ChannelViewWindow * window );
	//! Scheme window closed.
	void schemeWindowClosed( Scheme::Window * window );

	//! Init.
	void init( const QList< ToolWindowObject* > & toolWindows );

	//! \return Menu.
	const Menu & menu() const;

public slots:
	//! Start.
	void start();
	//! Show channel view.
	void showChannelView( const QString & channelName );
	//! Save configuration.
	void save();
	//! Show scheme.
	void showScheme( const QString & cfgFile, bool newScheme = false );
	//! Session finished.
	void sessionFinished( QSessionManager & );
	//! Add new Aggregate window.
	void addAggregate( Scheme::Window * w );
	//! Remove Aggregate window.
	void removeAggregate( Scheme::Window * w );
	//! \return Aggregate window by its name.
	Scheme::Window * findAggregate( const QString & name );

protected:
	friend class Configuration;

	void closeEvent( QCloseEvent * event );

	//! \return Windows configuration.
	WindowsCfg windowsCfg() const;
	//! Restore windows from configuration.
	void restoreWindows( const WindowsCfg & cfg );

private slots:
	//! About to quit.
	void aboutToQuit();
	//! New channel view.
	void newChannelView();
	//! Settings dialog.
	void settings();
	//! New scheme window.
	void newSchemeWindow();
	//! Open saved scheme.
	void openScheme();
	//! Shutdown.
	void shutdown();
	//! Update window menu.
	void updateWindowsMenu( QWidget * );
	//! Show about dialog.
	void about();
	//! Show about Qt dialog.
	void aboutQt();

private:
	//! Save configuration.
	void saveConfiguration();

private:
	Q_DISABLE_COPY( MainWindow )

	QScopedPointer< MainWindowPrivate > d;
}; // class MainWindow

} /* namespace Globe */

#endif // GLOBE__MAINWINDOW_HPP__INCLUDED

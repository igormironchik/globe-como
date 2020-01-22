
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

#ifndef GLOBE__MAINWINDOW_HPP__INCLUDED
#define GLOBE__MAINWINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Globe/Core/windows_cfg.hpp>
#include <Globe/Core/export.hpp>


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
	MainWindow( QWidget * parent = 0, Qt::WindowFlags flags = 0 );

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

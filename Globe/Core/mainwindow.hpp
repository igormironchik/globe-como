
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2013 Igor Mironchik

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef GLOBE__MAINWINDOW_HPP__INCLUDED
#define GLOBE__MAINWINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Globe/Core/windows_cfg.hpp>


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

class MainWindowPrivate;

//
// MainWindow
//

//! Main window of the application.
class MainWindow
	:	public QMainWindow
{
	Q_OBJECT

private:
	MainWindow( QWidget * parent = 0, Qt::WindowFlags flags = 0 );

	~MainWindow();

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

private:
	//! Save configuration.
	void saveConfiguration();

private:
	Q_DISABLE_COPY( MainWindow )

	QScopedPointer< MainWindowPrivate > d;
}; // class MainWindow

} /* namespace Globe */

#endif // GLOBE__MAINWINDOW_HPP__INCLUDED


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
#include <QtGui/QMainWindow>
#include <QtCore/QScopedPointer>


namespace Globe {

class ChannelsManager;
class DB;
class WindowStateCfg;
class PropertiesManager;
class ToolWindowObject;
class ChannelsList;
class SourcesMainWindow;

class MainWindowPrivate;

//
// MainWindow
//

//! Main window of the application.
class MainWindow
	:	public QMainWindow
{
	Q_OBJECT

public:
	MainWindow( const QString & cfgFileName,
		ChannelsManager * channelsManager, DB * db,
		PropertiesManager * propertiesManager,
		SourcesMainWindow * sourcesMainWindow,
		const QList< ToolWindowObject* > & toolWindows,
		QWidget * parent = 0, Qt::WindowFlags flags = 0 );

	~MainWindow();

	//! \return List with channels.
	ChannelsList * list();

public slots:
	//! Start.
	void start();

protected:
	void closeEvent( QCloseEvent * event );

private slots:
	//! About to quit.
	void aboutToQuit();

private:
	//! Init.
	void init();
	//! Save configuration.
	void saveConfiguration();

private:
	Q_DISABLE_COPY( MainWindow )

	QScopedPointer< MainWindowPrivate > d;
}; // class MainWindow

} /* namespace Globe */

#endif // GLOBE__MAINWINDOW_HPP__INCLUDED
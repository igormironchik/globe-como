
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

#ifndef GLOBE__SOURCES_MAINWINDOW_HPP__INCLUDED
#define GLOBE__SOURCES_MAINWINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Globe/Core/tool_window.hpp>


namespace Globe {

//
// SourcesMainWindow
//

class SourcesMainWindowPrivate;

//! Main window with show all sources available in the application.
class SourcesMainWindow
	:	public QMainWindow
	,	public ToolWindow
{
	Q_OBJECT

private:
	SourcesMainWindow( QWidget * parent = 0, Qt::WindowFlags flags = 0 );

	~SourcesMainWindow();

public:
	//! \return Instance.
	static SourcesMainWindow & instance();

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

private:
	Q_DISABLE_COPY( SourcesMainWindow )

	QScopedPointer< SourcesMainWindowPrivate > d;
}; // class SourcesMainWindow

} /* namespace Globe */

#endif // GLOBE__SOURCES_MAINWINDOW_HPP__INCLUDED

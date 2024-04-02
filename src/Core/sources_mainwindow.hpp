
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SOURCES_MAINWINDOW_HPP__INCLUDED
#define GLOBE__SOURCES_MAINWINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Core/tool_window.hpp>
#include <Core/export.hpp>


namespace Globe {

//
// SourcesMainWindow
//

class SourcesMainWindowPrivate;

//! Main window with show all sources available in the application.
class CORE_EXPORT SourcesMainWindow
	:	public QMainWindow
	,	public ToolWindow
{
	Q_OBJECT

private:
	SourcesMainWindow( QWidget * parent = 0, Qt::WindowFlags flags = Qt::WindowFlags() );

	~SourcesMainWindow();

	static void cleanup();

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

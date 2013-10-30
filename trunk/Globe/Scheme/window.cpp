
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

// Globe include.
#include <Globe/Scheme/window.hpp>
#include <Globe/Scheme/view.hpp>

#include <Globe/Core/mainwindow.hpp>
#include <Globe/Core/globe_menu.hpp>
#include <Globe/Core/tool_window_object.hpp>

// Qt include.
#include <QCloseEvent>
#include <QMenuBar>
#include <QMenu>


namespace Globe {

namespace Scheme {

//
// WindowPrivate
//

class WindowPrivate {
public:
	WindowPrivate()
		:	m_view( 0 )
	{
	}

	//! View.
	View * m_view;
	//! Scheme configuration file.
	QString m_cfgFile;
}; // class WindowPrivate


//
// Window
//

Window::Window( QWidget * parent, Qt::WindowFlags f )
	:	QMainWindow( parent, f )
	,	d( new WindowPrivate )
{
	init();
}

Window::~Window()
{
}

void
Window::initMenu( const Menu & menu )
{
	menuBar()->addMenu( menu.fileMenu() );

	QMenu * toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );

	foreach( ToolWindowObject * obj, menu.toolWindows() )
		toolsMenu->addAction( obj->menuEntity() );

	menuBar()->addMenu( menu.settingsMenu() );
}

WindowCfg
Window::cfg() const
{
	return WindowCfg( d->m_cfgFile, windowStateCfg( this ) );
}

void
Window::setCfg( const WindowCfg & cfg )
{
	d->m_cfgFile = cfg.schemeCfgFile();

	restoreWindowState( cfg.windowStateCfg(), this );
}

void
Window::loadScheme( const QString & fileName )
{
	d->m_cfgFile = fileName;

	setTitle( d->m_cfgFile );
}

void
Window::createNewScheme( const QString & fileName )
{
	d->m_cfgFile = fileName;

	if( !d->m_cfgFile.endsWith( QLatin1String( ".scheme" ) ) )
		d->m_cfgFile.append( QLatin1String( ".scheme" ) );

	setTitle( d->m_cfgFile );
}

void
Window::closeEvent( QCloseEvent * event )
{
	event->accept();

	MainWindow::instance().schemeWindowClosed( this );
}

void
Window::init()
{
	d->m_view = new View( this );

	setCentralWidget( d->m_view );
}

void
Window::setTitle( const QString & title )
{
	setWindowTitle( QString( "Scheme - [%1]" ).arg( title ) );
}

} /* namespace Scheme */

} /* namespace Globe */

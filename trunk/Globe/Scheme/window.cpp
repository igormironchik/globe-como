
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
#include <Globe/Scheme/scene.hpp>

#include <Globe/Core/mainwindow.hpp>
#include <Globe/Core/globe_menu.hpp>
#include <Globe/Core/tool_window_object.hpp>

// Qt include.
#include <QCloseEvent>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QActionGroup>


namespace Globe {

namespace Scheme {

//
// WindowPrivate
//

class WindowPrivate {
public:
	WindowPrivate()
		:	m_view( 0 )
		,	m_modeAction( 0 )
		,	m_editModeToolBar( 0 )
	{
	}

	//! View.
	View * m_view;
	//! Scheme configuration file.
	QString m_cfgFile;
	//! Mode action.
	QAction * m_modeAction;
	//! Tool bar with edit mode selectors.
	QToolBar * m_editModeToolBar;
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

	QMenu * modeMenu = menuBar()->addMenu( tr( "&Mode" ) );

	d->m_modeAction = modeMenu->addAction( tr( "Edit" ), this,
		SLOT( editMode() ) );

	d->m_modeAction->setCheckable( true );

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

	d->m_modeAction->setChecked( false );

	editMode();

	d->m_view->scene()->loadScheme( d->m_cfgFile );
}

void
Window::createNewScheme( const QString & fileName )
{
	d->m_cfgFile = fileName;

	if( !d->m_cfgFile.endsWith( QLatin1String( ".scheme" ) ) )
		d->m_cfgFile.append( QLatin1String( ".scheme" ) );

	setTitle( d->m_cfgFile );

	d->m_modeAction->setChecked( true );

	editMode();
}

void
Window::saveScheme()
{
	d->m_view->scene()->saveScheme( d->m_cfgFile );
}

void
Window::editMode()
{
	if( d->m_modeAction->isChecked() )
	{
		d->m_view->scene()->setMode( EditScene );
		d->m_editModeToolBar->show();
	}
	else
	{
		d->m_view->scene()->setMode( ViewScene );
		d->m_editModeToolBar->hide();
	}
}

void
Window::selectEditMode()
{
	d->m_view->scene()->setEditMode( EditSceneSelect );
}

void
Window::sourceEditMode()
{
	d->m_view->scene()->setEditMode( EditSceneNewSource );
}

void
Window::textBlockEditMode()
{
	d->m_view->scene()->setEditMode( EditSceneNewText );
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

	d->m_editModeToolBar = new QToolBar( tr( "Edit Mode" ), this );

	QAction * selectEditModeAction = d->m_editModeToolBar->addAction(
		QIcon( ":/img/select_mode_22x22.png" ), tr( "Select" ),
		this, SLOT( selectEditMode() ) );
	selectEditModeAction->setCheckable( true );

	QAction * sourceEditModeAction = d->m_editModeToolBar->addAction(
		QIcon( ":/img/add_source_22x22.png" ), tr( "Add Source" ),
		this, SLOT( sourceEditMode() ) );
	sourceEditModeAction->setCheckable( true );

	QAction * textEditModeAction = d->m_editModeToolBar->addAction(
		QIcon( ":/img/add_text_22x22.png" ), tr( "Add Text" ),
		this, SLOT( textBlockEditMode() ) );
	textEditModeAction->setCheckable( true );

	QActionGroup * actionGroup = new QActionGroup( this );
	actionGroup->addAction( selectEditModeAction );
	actionGroup->addAction( sourceEditModeAction );
	actionGroup->addAction( textEditModeAction );

	selectEditModeAction->setChecked( true );

	addToolBar( d->m_editModeToolBar );

	d->m_editModeToolBar->hide();
}

void
Window::setTitle( const QString & title )
{
	setWindowTitle( QString( "Scheme - [%1]" ).arg( title ) );
}

} /* namespace Scheme */

} /* namespace Globe */


/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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

// Globe include.
#include <Globe/Scheme/window.hpp>
#include <Globe/Scheme/view.hpp>
#include <Globe/Scheme/scene.hpp>
#include <Globe/Scheme/scheme_cfg.hpp>

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

SchemeCfg
Window::schemeCfg() const
{
	return d->m_view->scene()->schemeCfg();
}

const QString &
Window::schemeName() const
{
	return d->m_view->scene()->schemeName();
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
Window::loadScheme( const SchemeCfg & cfg, bool editing )
{
	if( !cfg.name().isEmpty() )
		setTitle( cfg.name() );

	if( !editing )
		d->m_modeAction->setChecked( false );
	else
		d->m_modeAction->setChecked( true );

	editMode();

	d->m_view->scene()->initScheme( cfg );

	MainWindow::instance().addAggregate( this );
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

		emit schemeChanged();
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
Window::aggregateEditMode()
{
	d->m_view->scene()->setEditMode( EditSceneNewAggregate );
}

void
Window::closeEvent( QCloseEvent * event )
{
	event->accept();

	if( !d->m_view->scene()->cfgFile().isEmpty() )
		MainWindow::instance().schemeWindowClosed( this );
	else
		MainWindow::instance().removeAggregate( this );

	emit schemeChanged();
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

	QAction * aggregateEditModeAction = d->m_editModeToolBar->addAction(
		QIcon( ":/img/add_aggregate_22x22.png" ), tr( "Add Aggregate" ),
		this, SLOT( aggregateEditMode() ) );
	aggregateEditModeAction->setCheckable( true );

	QActionGroup * actionGroup = new QActionGroup( this );
	actionGroup->addAction( selectEditModeAction );
	actionGroup->addAction( sourceEditModeAction );
	actionGroup->addAction( textEditModeAction );
	actionGroup->addAction( aggregateEditModeAction );

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


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Scheme/window.hpp>
#include <Scheme/view.hpp>
#include <Scheme/scene.hpp>
#include <Scheme/scheme_cfg.hpp>

#include <Core/mainwindow.hpp>
#include <Core/globe_menu.hpp>
#include <Core/tool_window_object.hpp>
#include <Core/configuration.hpp>

// Qt include.
#include <QCloseEvent>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QActionGroup>
#include <QApplication>
#include <QScreen>


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
		,	m_winMenu( Q_NULLPTR )
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
	//! Windows menu.
	QScopedPointer< WindowsMenu > m_winMenu;
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

	QMenu * win = menuBar()->addMenu( tr( "&Windows" ) );

	menuBar()->addMenu( menu.helpMenu() );

	d->m_winMenu.reset( new WindowsMenu( win, this, menu.windows(), this ) );
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

const QString &
Window::cfgFile() const
{
	return d->m_cfgFile;
}

void
Window::loadScheme( const QString & fileName )
{
	d->m_cfgFile = fileName;

	setTitle( d->m_cfgFile );

	d->m_modeAction->setChecked( false );

	editMode();

	d->m_view->scene()->loadScheme( Configuration::instance().path() + d->m_cfgFile );
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
	d->m_view->scene()->saveScheme( Configuration::instance().path() + d->m_cfgFile );
}

void
Window::loadScheme( const Globe::Scheme::SchemeCfg & cfg, bool editing )
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

	d->m_view->resize( ( d->m_view->scene()->sceneRect().size().toSize() +
		QSize( 10, 10 ) ).boundedTo(
			screen()->availableGeometry().size() - QSize( 200, 150 ) ) );
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

		emit schemePossiblyChanged();
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
Window::updateWindowsMenu( QWidget * )
{
	d->m_winMenu->update();
}

void
Window::closeEvent( QCloseEvent * event )
{
	event->accept();

	if( !d->m_view->scene()->cfgFile().isEmpty() )
		MainWindow::instance().schemeWindowClosed( this );
	else
		MainWindow::instance().removeAggregate( this );

	emit schemePossiblyChanged();
}

void
Window::init()
{
	setAttribute( Qt::WA_DeleteOnClose );

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

	connect( &MainWindow::instance(), &MainWindow::windowCreated,
		this, &Window::updateWindowsMenu );
	connect( &MainWindow::instance(), &MainWindow::windowClosed,
		this, &Window::updateWindowsMenu );
}

void
Window::setTitle( const QString & title )
{
	setWindowTitle( QString( "Scheme - [%1]" ).arg( title ) );
}

} /* namespace Scheme */

} /* namespace Globe */

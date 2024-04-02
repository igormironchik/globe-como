
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/channel_view_window.hpp>
#include <Core/channel_view.hpp>
#include <Core/channel_view_window_model.hpp>
#include <Core/tool_window_object.hpp>
#include <Core/channels.hpp>
#include <Core/mainwindow.hpp>
#include <Core/globe_menu.hpp>

// Qt include.
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QCloseEvent>
#include <QHeaderView>
#include <QToolBar>


namespace Globe {

//
// ChannelViewWindowPrivate
//

class ChannelViewWindowPrivate {
public:
	ChannelViewWindowPrivate()
		:	m_view( 0 )
		,	m_winMenu( Q_NULLPTR )
	{
	}

	//! View.
	ChannelView * m_view;
	//! Channel's name.
	QString m_channelName;
	//! Windows menu.
	QScopedPointer< WindowsMenu > m_winMenu;
}; // class ChannelViewWindowPrivate


//
// ChannelViewWindow
//

ChannelViewWindow::ChannelViewWindow( QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new ChannelViewWindowPrivate )
{
	init();
}

ChannelViewWindow::~ChannelViewWindow()
{
}

const QString &
ChannelViewWindow::channel() const
{
	return d->m_channelName;
}

bool
ChannelViewWindow::setChannel( const QString & channelName )
{
	Channel * channel = ChannelsManager::instance().channelByName( channelName );

	if( channel )
	{
		if( !channel->isMustBeConnected() && !channel->isConnected() )
		{
			const QMessageBox::StandardButton button =
				QMessageBox::question( 0, tr( "Channel is not connected..." ),
					tr( "Channel \"%1\" is not connected.\n"
						"Do you want to connect it?" )
							.arg( channelName ),
					QMessageBox::Ok | QMessageBox::Cancel,
					QMessageBox::Ok );

			if( button == QMessageBox::Ok )
				channel->connectToHost();
		}

		d->m_channelName = channelName;

		d->m_view->model()->initModel( d->m_channelName );

		setWindowTitle( channelName );

		return true;
	}
	else
	{
		QMessageBox::critical( 0, tr( "Unable to initialize window..." ),
			tr( "Unable to initialize window with channel \"%1\",\n"
				"because there is no such channel." )
					.arg( channelName ) );

		return false;
	}
}

ViewHeaderCfg
ChannelViewWindow::viewHeaderCfg() const
{
	ViewHeaderCfg cfg;

	cfg.setSortColumn( d->m_view->header()->sortIndicatorSection() );
	cfg.setSortOrder( d->m_view->header()->sortIndicatorOrder() );

	cfg.setSourceNameColumn( HeaderColumnCfg(
		d->m_view->header()->sectionSize( sourceNameColumn ),
		d->m_view->header()->visualIndex( sourceNameColumn ) ) );

	cfg.setTypeNameColumn( HeaderColumnCfg(
		d->m_view->header()->sectionSize( sourceTypeNameColumn ),
		d->m_view->header()->visualIndex( sourceTypeNameColumn ) ) );

	cfg.setValueColumn( HeaderColumnCfg(
		d->m_view->header()->sectionSize( valueColumn ),
		d->m_view->header()->visualIndex( valueColumn ) ) );

	cfg.setDateTimeColumn( HeaderColumnCfg(
		d->m_view->header()->sectionSize( dateTimeColumn ),
		d->m_view->header()->visualIndex( dateTimeColumn ) ) );

	cfg.setPriorityColumn( HeaderColumnCfg(
		d->m_view->header()->sectionSize( priorityColumn ),
		d->m_view->header()->visualIndex( priorityColumn ) ) );

	return cfg;
}

ChannelViewWindowCfg
ChannelViewWindow::cfg() const
{
	ChannelViewWindowCfg cfg;

	cfg.setChannelName( d->m_channelName );
	cfg.setWindowStateCfg( windowStateCfg( this ) );
	cfg.setViewHeaderCfg( viewHeaderCfg() );

	return cfg;
}

static int columnIndex( const QList< int > & positions, int column )
{
	for( int i = 0; i < positions.size(); ++i )
		if( positions[ i ] == column )
			return i;

	return -1;
}

static void restoreColumns( QList< int > & positions, QHeaderView * header )
{
	for( int i = 0; i < positions.size() - 1; ++i )
	{
		const int index = columnIndex( positions, i );

		if( index != -1 )
		{
			header->moveSection( index, i );

			positions.move( index, i );
		}
	}
}

void
ChannelViewWindow::restoreHeader( const ViewHeaderCfg & cfg )
{
	QList< int > positions;
	positions.append( cfg.priorityColumn().pos() );
	positions.append( cfg.dateTimeColumn().pos() );
	positions.append( cfg.typeNameColumn().pos() );
	positions.append( cfg.sourceNameColumn().pos() );
	positions.append( cfg.valueColumn().pos() );

	restoreColumns( positions, d->m_view->header() );

	d->m_view->header()->resizeSection( sourceNameColumn,
		cfg.sourceNameColumn().size() );
	d->m_view->header()->resizeSection( sourceTypeNameColumn,
		cfg.typeNameColumn().size() );
	d->m_view->header()->resizeSection( valueColumn,
		cfg.valueColumn().size() );
	d->m_view->header()->resizeSection( dateTimeColumn,
		cfg.dateTimeColumn().size() );
	d->m_view->header()->resizeSection( priorityColumn,
		cfg.priorityColumn().size() );

	d->m_view->header()->setSortIndicator( cfg.sortColumn(), cfg.sortOrder() );
}

void
ChannelViewWindow::updateWindowsMenu( QWidget * )
{
	d->m_winMenu->update();
}

void
ChannelViewWindow::setWindowCfg( const ChannelViewWindowCfg & c )
{
	restoreWindowState( c.windowStateCfg(), this );
	restoreHeader( c.viewHeaderCfg() );
}

void
ChannelViewWindow::init()
{
	setAttribute( Qt::WA_DeleteOnClose );

	d->m_view = new ChannelView( this );

	setCentralWidget( d->m_view );

	QToolBar * toolBar = new QToolBar( this );
	addToolBar( Qt::TopToolBarArea, toolBar );

	toolBar->addAction( d->m_view->copyAction() );
	toolBar->addAction( d->m_view->selectAllAction() );
	toolBar->addSeparator();
	toolBar->addAction( d->m_view->fillColorAction() );

	connect( &MainWindow::instance(), &MainWindow::windowCreated,
		this, &ChannelViewWindow::updateWindowsMenu );
	connect( &MainWindow::instance(), &MainWindow::windowClosed,
		this, &ChannelViewWindow::updateWindowsMenu );
}

void
ChannelViewWindow::initMenu( const Menu & menu )
{
	menuBar()->addMenu( menu.fileMenu() );

	QMenu * toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );

	foreach( ToolWindowObject * obj, menu.toolWindows() )
		toolsMenu->addAction( obj->menuEntity() );

	menuBar()->addMenu( menu.settingsMenu() );

	QMenu * win = menuBar()->addMenu( tr( "&Windows" ) );

	menuBar()->addMenu( menu.helpMenu() );

	d->m_winMenu.reset( new WindowsMenu( win, this, menu.windows(), this ) );
}

void
ChannelViewWindow::closeEvent( QCloseEvent * event )
{
	event->accept();

	MainWindow::instance().channelViewWindowClosed( this );
}

} /* namespace Globe */

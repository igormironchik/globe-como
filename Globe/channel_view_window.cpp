
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
#include <Globe/channel_view_window.hpp>
#include <Globe/channel_view.hpp>
#include <Globe/channel_view_window_model.hpp>
#include <Globe/tool_window_object.hpp>
#include <Globe/channels.hpp>
#include <Globe/mainwindow.hpp>
#include <Globe/globe_menu.hpp>

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
	{
	}

	//! View.
	ChannelView * m_view;
	//! Channel's name.
	QString m_channelName;
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
		d->m_view->header()->sectionSize( 0 ),
		d->m_view->header()->visualIndex( 0 ) ) );

	cfg.setTypeNameColumn( HeaderColumnCfg(
		d->m_view->header()->sectionSize( 1 ),
		d->m_view->header()->visualIndex( 1 ) ) );

	cfg.setValueColumn( HeaderColumnCfg(
		d->m_view->header()->sectionSize( 2 ),
		d->m_view->header()->visualIndex( 2 ) ) );

	cfg.setDateTimeColumn( HeaderColumnCfg(
		d->m_view->header()->sectionSize( 3 ),
		d->m_view->header()->visualIndex( 3 ) ) );

	cfg.setPriorityColumn( HeaderColumnCfg(
		d->m_view->header()->sectionSize( 4 ),
		d->m_view->header()->visualIndex( 4 ) ) );

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
	positions.append( cfg.sourceNameColumn().pos() );
	positions.append( cfg.typeNameColumn().pos() );
	positions.append( cfg.valueColumn().pos() );
	positions.append( cfg.dateTimeColumn().pos() );
	positions.append( cfg.priorityColumn().pos() );

	restoreColumns( positions, d->m_view->header() );

	d->m_view->header()->resizeSection( 0, cfg.sourceNameColumn().size() );
	d->m_view->header()->resizeSection( 1, cfg.typeNameColumn().size() );
	d->m_view->header()->resizeSection( 2, cfg.valueColumn().size() );
	d->m_view->header()->resizeSection( 3, cfg.dateTimeColumn().size() );
	d->m_view->header()->resizeSection( 4, cfg.priorityColumn().size() );

	d->m_view->header()->setSortIndicator( cfg.sortColumn(), cfg.sortOrder() );
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
	d->m_view = new ChannelView( this );

	setCentralWidget( d->m_view );

	QToolBar * toolBar = new QToolBar( this );
	addToolBar( Qt::TopToolBarArea, toolBar );

	toolBar->addAction( d->m_view->copyAction() );
	toolBar->addAction( d->m_view->selectAllAction() );
	toolBar->addSeparator();
	toolBar->addAction( d->m_view->fillColorAction() );
}

void
ChannelViewWindow::initMenu( const Menu & menu )
{
	menuBar()->addMenu( menu.fileMenu() );

	QMenu * toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );

	foreach( ToolWindowObject * obj, menu.toolWindows() )
		toolsMenu->addAction( obj->menuEntity() );

	menuBar()->addMenu( menu.settingsMenu() );
}

void
ChannelViewWindow::closeEvent( QCloseEvent * event )
{
	event->accept();

	MainWindow::instance().channelViewWindowClosed( this );
}

} /* namespace Globe */

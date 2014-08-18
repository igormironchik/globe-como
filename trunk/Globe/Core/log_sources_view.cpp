
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
#include <Globe/Core/log_sources_view.hpp>
#include <Globe/Core/log_sources_model.hpp>
#include <Globe/Core/color_for_level.hpp>
#include <Globe/Core/properties_manager.hpp>

// Qt include.
#include <QAction>
#include <QItemSelectionModel>
#include <QApplication>
#include <QClipboard>
#include <QPainter>
#include <QMenu>
#include <QContextMenuEvent>


namespace Globe {

//
// LogSourcesViewPrivate
//

class LogSourcesViewPrivate {
public:
	LogSourcesViewPrivate()
		:	m_model( 0 )
		,	m_copyAction( 0 )
		,	m_selectAllAction( 0 )
	{
	}

	//! Model.
	LogSourcesModel * m_model;
	//! Copy action.
	QAction * m_copyAction;
	//! Select all action.
	QAction * m_selectAllAction;
}; // class LogSourcesViewPrivate;


//
// LogSourcesView
//

LogSourcesView::LogSourcesView( QWidget * parent )
	:	QTreeView( parent )
	,	d( new LogSourcesViewPrivate )
{
	init();
}

LogSourcesView::~LogSourcesView()
{
}

LogSourcesModel *
LogSourcesView::model()
{
	return d->m_model;
}

void
LogSourcesView::init()
{
	setRootIsDecorated( false );
	setSortingEnabled( false );
	setSelectionMode( QAbstractItemView::ExtendedSelection );
	setSelectionBehavior( QAbstractItemView::SelectRows );
	setWordWrap( true );

	d->m_copyAction= new QAction( QIcon( ":/img/edit_copy_22x22.png" ),
		tr( "Copy" ), this );
	d->m_copyAction->setShortcut( QKeySequence( "Ctrl+C" ) );
	d->m_copyAction->setEnabled( false );

	d->m_selectAllAction = new QAction( QIcon( ":/img/edit_select_all_22x22.png" ),
		tr( "Select All" ), this );
	d->m_selectAllAction->setShortcut( QKeySequence( "Ctrl+A" ) );

	addAction( d->m_copyAction );
	addAction( d->m_selectAllAction );

	connect( d->m_copyAction, &QAction::triggered,
		this, &LogSourcesView::copyImplementation );
	connect( d->m_selectAllAction, &QAction::triggered,
		this, &LogSourcesView::selectAllImplementation );

	d->m_model = new LogSourcesModel( this );

	setModel( d->m_model );
}

void
LogSourcesView::selectionChanged( const QItemSelection & selected,
	const QItemSelection & deselected )
{
	if( !selected.isEmpty() )
		d->m_copyAction->setEnabled( true );
	else
		d->m_copyAction->setEnabled( false );

	QTreeView::selectionChanged( selected, deselected );
}

void
LogSourcesView::selectAllImplementation()
{
	selectAll();
}

void
LogSourcesView::copyImplementation()
{
	const QModelIndexList indexes = selectionModel()->selectedRows();

	const int size = indexes.size();

	QClipboard * clipboard = QApplication::clipboard();

	QString text;

	text.append( QLatin1String( "Date & Time; " ) );
	text.append( QLatin1String( "Channel Name; " ) );
	text.append( QLatin1String( "Type Name; " ) );
	text.append( QLatin1String( "Source name; " ) );
	text.append( QLatin1String( "Value; " ) );
	text.append( QLatin1String( "Description\n" ) );

	for( int i = 0; i < size; ++i )
	{
		const LogSourcesRecord & r = d->m_model->record( indexes[ i ] );

		text.append( r.dateTime() );
		text.append( QLatin1String( "; " ) );
		text.append( r.channelName() );
		text.append( QLatin1String( "; " ) );
		text.append( r.source().typeName() );
		text.append( QLatin1String( "; " ) );
		text.append( r.source().name() );
		text.append( QLatin1String( "; " ) );
		text.append( r.source().value().toString() );
		text.append( QLatin1String( "; " ) );
		text.append( r.source().description() );
		text.append( QLatin1String( "\n" ) );
	}

	clipboard->setText( text );

	clearSelection();
}

void
LogSourcesView::drawRow( QPainter * painter, const QStyleOptionViewItem & option,
	const QModelIndex & index ) const
{
	const LogSourcesRecord r = d->m_model->record( index );

	const Properties * props = PropertiesManager::instance()
		.findProperties( r.source(), r.channelName(), 0 );

	Level level = None;

	if( props )
		level = props->checkConditions( r.source().value(),
			r.source().type() ).level();

	painter->fillRect( option.rect,
		ColorForLevel::instance().color( level ) );

	QTreeView::drawRow( painter, option, index );
}

void
LogSourcesView::contextMenuEvent( QContextMenuEvent * event )
{
	QMenu menu( this );

	const QModelIndexList indexes = selectionModel()->selectedRows();

	if( !indexes.isEmpty() )
		menu.addAction( d->m_copyAction );

	menu.addAction( d->m_selectAllAction );

	menu.exec( event->globalPos() );

	event->accept();
}

} /* namespace Globe */


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

// Qt include.
#include <QSortFilterProxyModel>
#include <QHeaderView>
#include <QPainter>
#include <QAction>
#include <QItemSelectionModel>
#include <QApplication>
#include <QClipboard>
#include <QTableView>
#include <QContextMenuEvent>
#include <QMenu>

// Globe include.
#include <Globe/Core/channel_view.hpp>
#include <Globe/Core/channel_view_window_model.hpp>
#include <Globe/Core/color_for_level.hpp>


namespace Globe {

//
// ChannelViewPrivate
//

class ChannelViewPrivate {
public:
	ChannelViewPrivate()
		:	m_model( 0 )
		,	m_sortModel( 0 )
		,	m_copyAction( 0 )
		,	m_selectAllAction( 0 )
		,	m_fillColorAction( 0 )
	{
	}

	//! Model.
	ChannelViewWindowModel * m_model;
	//! Sort model.
	QSortFilterProxyModel * m_sortModel;
	//! Copy action.
	QAction * m_copyAction;
	//! Select all action.
	QAction * m_selectAllAction;
	//! Action for turning on/off coloring of view.
	QAction * m_fillColorAction;
}; // class ChannelViewPrivate


//
// ChannelView
//

ChannelView::ChannelView( QWidget * parent )
	:	QTreeView( parent )
	,	d( new ChannelViewPrivate )
{
	init();
}

ChannelView::~ChannelView()
{
}

ChannelViewWindowModel *
ChannelView::model()
{
	return d->m_model;
}

QSortFilterProxyModel *
ChannelView::sortModel()
{
	return d->m_sortModel;
}

QAction *
ChannelView::copyAction() const
{
	return d->m_copyAction;
}

QAction *
ChannelView::selectAllAction() const
{
	return d->m_selectAllAction;
}

QAction *
ChannelView::fillColorAction() const
{
	return d->m_fillColorAction;
}

void
ChannelView::selectionChanged ( const QItemSelection & selected,
	const QItemSelection & deselected )
{
	if( !selected.isEmpty() )
		d->m_copyAction->setEnabled( true );
	else
		d->m_copyAction->setEnabled( false );

	QTreeView::selectionChanged( selected, deselected );
}

void
ChannelView::selectAllImplementation()
{
	selectAll();
}

static QString boolToString( bool value )
{
	if( value )
		return QLatin1String( "true" );
	else
		return QLatin1String( "false" );
}

void
ChannelView::copyImplementation()
{
	QModelIndexList indexes = selectionModel()->selectedIndexes();

	const int size = indexes.size();

	for( int i = 0; i < size; ++i )
		indexes[ i ] = d->m_sortModel->mapToSource( indexes[ i ] );

	QClipboard * clipboard = QApplication::clipboard();

	QString text;

	const int columnsCount = d->m_model->columnCount();

	for( int i = 0; i < columnsCount; ++i )
	{
		text.append( d->m_model->headerData( i, Qt::Horizontal,
			Qt::DisplayRole ).toString() );

		text.append( QLatin1String( ";" ) );
	}

	text.append( tr( "Registered" ) );
	text.append( QLatin1String( ";\n" ) );

	for( int i = 0, c = 1; i < size; ++i, ++c )
	{
		text.append( d->m_model->data( indexes[ i ] ).toString() );
		text.append( QLatin1String( ";" ) );

		if( c == columnsCount )
		{
			const bool isRegistered = d->m_model->isRegistered( indexes[ i ] );

			text.append( boolToString( isRegistered ) );
			text.append( QLatin1String( ";\n" ) );

			c = 0;
		}
	}

	clipboard->setText( text );

	clearSelection();
}

void
ChannelView::fillWithColorChanged()
{
	update();
}

void
ChannelView::colorForLevelChanged()
{
	update();
}

void
ChannelView::drawRow( QPainter * painter, const QStyleOptionViewItem & option,
	const QModelIndex & index ) const
{
	if( d->m_fillColorAction->isChecked() )
	{
		if( !d->m_model->isConnected() )
			painter->fillRect( option.rect,
				ColorForLevel::instance().disconnectedColor() );
		else
		{
			const QModelIndex actualIndex = d->m_sortModel->mapToSource( index );

			if( !d->m_model->isRegistered( actualIndex ) )
				painter->fillRect( option.rect,
					ColorForLevel::instance().deregisteredColor() );
			else
				painter->fillRect( option.rect,
					ColorForLevel::instance().color( d->m_model->level( actualIndex ) ) );
		}
	}

	QTreeView::drawRow( painter, option, index );
}

void
ChannelView::contextMenuEvent( QContextMenuEvent * event )
{
	QMenu menu( this );

	const QModelIndexList indexes = selectionModel()->selectedRows();

	if( !indexes.isEmpty() )
		menu.addAction( d->m_copyAction );

	menu.addAction( d->m_selectAllAction );

	menu.addSeparator();

	menu.addAction( d->m_fillColorAction );

	menu.exec( event->globalPos() );

	event->accept();
}

void
ChannelView::init()
{
	setRootIsDecorated( false );
	setSortingEnabled( true );
	setSelectionMode( QAbstractItemView::ExtendedSelection );
	setSelectionBehavior( QAbstractItemView::SelectRows );
	setWordWrap( true );
	setDragDropMode( QAbstractItemView::DragOnly );

	d->m_copyAction= new QAction( QIcon( ":/img/edit_copy_22x22.png" ),
		tr( "Copy" ), this );
	d->m_copyAction->setShortcut( QKeySequence( "Ctrl+C" ) );
	d->m_copyAction->setEnabled( false );

	d->m_selectAllAction = new QAction( QIcon( ":/img/edit_select_all_22x22.png" ),
		tr( "Select All" ), this );
	d->m_selectAllAction->setShortcut( QKeySequence( "Ctrl+A" ) );

	d->m_fillColorAction = new QAction( QIcon( ":/img/fill_color_22x22.png" ),
		tr( "Fill With Color" ), this );
	d->m_fillColorAction->setShortcut( QKeySequence( "Ctrl+F" ) );
	d->m_fillColorAction->setCheckable( true );
	d->m_fillColorAction->setChecked( true );

	addAction( d->m_copyAction );
	addAction( d->m_selectAllAction );
	addAction( d->m_fillColorAction );

	connect( d->m_copyAction, &QAction::triggered,
		this, &ChannelView::copyImplementation );
	connect( d->m_selectAllAction, &QAction::triggered,
		this, &ChannelView::selectAllImplementation );
	connect( d->m_fillColorAction, &QAction::changed,
		this, &ChannelView::fillWithColorChanged );
	connect( &ColorForLevel::instance(), &ColorForLevel::changed,
		this, &ChannelView::colorForLevelChanged );

	d->m_model = new ChannelViewWindowModel( this );

	d->m_sortModel = new QSortFilterProxyModel( this );
	d->m_sortModel->setSourceModel( d->m_model );

	setModel( d->m_sortModel );

	// Enable moving of first column.
	// It's a hack. See QTBUG-33974.
	QTableView unused;
	unused.setVerticalHeader( header() );
	header()->setParent( this );
	unused.setVerticalHeader( new QHeaderView( Qt::Horizontal ) );
}

} /* namespace Globe */

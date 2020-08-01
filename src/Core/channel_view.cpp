
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2020 Igor Mironchik

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
#include <Core/channel_view.hpp>
#include <Core/channel_view_window_model.hpp>
#include <Core/color_for_level.hpp>
#include <Core/properties_manager.hpp>
#include <Core/word_wrap_delegate.hpp>

#include <QDebug>


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
		,	m_editPropertiesAction( 0 )
		,	m_deletePropertiesAction( 0 )
		,	m_addPropertiesAction( 0 )
		,	m_promotePropertiesAction( 0 )
		,	m_delegate( nullptr )
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
	//! Action for editing of properties.
	QAction * m_editPropertiesAction;
	//! Action for deleteion of properties.
	QAction * m_deletePropertiesAction;
	//! Action for adding of properties.
	QAction * m_addPropertiesAction;
	//! Action for promoting of properties.
	QAction * m_promotePropertiesAction;
	//! Delegate.
	WordWrapItemDelegate * m_delegate;
	//! Current source.
	Como::Source m_currentSource;
	//! Key for current properties.
	PropertiesKey m_currentKey;
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
	viewport()->update();
}

void
ChannelView::colorForLevelChanged()
{
	viewport()->update();
}

void
ChannelView::addProperties()
{
	PropertiesManager::instance().addProperties( d->m_currentSource,
		d->m_model->channelName(), this );
}

void
ChannelView::editProperties()
{
	PropertiesManager::instance().editProperties( d->m_currentKey, this );
}

void
ChannelView::deleteProperties()
{
	PropertiesManager::instance().removeProperties( d->m_currentKey, this );
}

void
ChannelView::promoteProperties()
{
	PropertiesManager::instance().promoteProperties( d->m_currentKey, this );
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

	const QModelIndex index = d->m_sortModel->mapToSource( currentIndex() );

	if( index.isValid() )
	{
		menu.addSeparator();

		d->m_currentSource = d->m_model->source( index );

		const Properties * p = PropertiesManager::instance().findProperties(
			d->m_currentSource, d->m_model->channelName(), &d->m_currentKey );

		if( p )
		{
			menu.addAction( d->m_editPropertiesAction );
			menu.addAction( d->m_promotePropertiesAction );
			menu.addAction( d->m_deletePropertiesAction );
		}
		else
			menu.addAction( d->m_addPropertiesAction );
	}

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

	d->m_delegate = new WordWrapItemDelegate( this );
	setItemDelegate( d->m_delegate );

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

	d->m_addPropertiesAction = new QAction( QIcon( ":/img/add_22x22.png" ),
		tr( "Add Properties" ), this );
	d->m_editPropertiesAction = new QAction( QIcon( ":/img/edit_22x22.png" ),
		tr( "Edit Properties" ), this );
	d->m_deletePropertiesAction = new QAction( QIcon( ":/img/remove_22x22.png" ),
		tr( "Delete Properties" ), this );
	d->m_promotePropertiesAction = new QAction( QIcon( ":/img/export_22x22.png" ),
		tr( "Promote Properties To" ), this );

	connect( d->m_addPropertiesAction, &QAction::triggered,
		this, &ChannelView::addProperties );
	connect( d->m_editPropertiesAction, &QAction::triggered,
		this, &ChannelView::editProperties );
	connect( d->m_deletePropertiesAction, &QAction::triggered,
		this, &ChannelView::deleteProperties );
	connect( d->m_promotePropertiesAction, &QAction::triggered,
		this, &ChannelView::promoteProperties );

	d->m_model = new ChannelViewWindowModel( this );

	d->m_sortModel = new QSortFilterProxyModel( this );
	d->m_sortModel->setSourceModel( d->m_model );

	connect( d->m_model, &ChannelViewWindowModel::priorityChanged,
		this, &ChannelView::priorityChanged );

	setModel( d->m_sortModel );

	// Enable moving of first column.
	// It's a hack. See QTBUG-33974.
	QTableView unused;
	unused.setVerticalHeader( header() );
	header()->setParent( this );
	unused.setVerticalHeader( new QHeaderView( Qt::Horizontal ) );

	connect( header(), &QHeaderView::sectionResized,
		this, &ChannelView::sectionResized );
}

void
ChannelView::sectionResized( int section, int, int )
{
	for( int i = 0; i < d->m_model->rowCount(); ++i )
		emit d->m_delegate->sizeHintChanged( d->m_model->index( i, section ) );
}

void
ChannelView::priorityChanged()
{
	if( d->m_sortModel->sortColumn() == priorityColumn )
		d->m_sortModel->invalidate();
}

} /* namespace Globe */

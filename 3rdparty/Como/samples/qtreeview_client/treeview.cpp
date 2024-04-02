
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// QTreeViewClient include.
#include "treeview.hpp"
#include "model.hpp"

// Qt include.
#include <QPainter>
#include <QHeaderView>


//
// TreeView::TreeViewPrivate
//

struct TreeView::TreeViewPrivate {
	explicit TreeViewPrivate( Model * model )
		:	m_model( model )
	{
	}

	Model * m_model;
}; // struct TreeView::TreeViewPrivate


//
// TreeView
//

TreeView::TreeView( Model * model, QWidget * parent )
	:	QTreeView( parent )
	,	d( new TreeViewPrivate( model ) )
{
	init();
}

TreeView::~TreeView()
{
}

void
TreeView::init()
{
	setRootIsDecorated( false );
	setSortingEnabled( true );
	setWordWrap( true );
	setAllColumnsShowFocus( true );
	sortByColumn( 0, Qt::AscendingOrder );
}

void
TreeView::drawRow( QPainter * painter,
	const QStyleOptionViewItem & option,
	const QModelIndex & index ) const
{
	const QColor c = d->m_model->color( index );
	painter->fillRect( option.rect, c );
	QTreeView::drawRow( painter, option, index );
}

void
TreeView::dataChanged( const QModelIndex & topLeft,
	const QModelIndex & bottomRight )
{
	QTreeView::dataChanged( topLeft, bottomRight );

	for( int i = topLeft.column(); i <= bottomRight.column(); ++i )
		resizeColumnToContents( i );
}


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include "properties_manager_view.hpp"

// Qt include.
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>


namespace Globe {

//
// PropertiesManagerViewPrivate
//

class PropertiesManagerViewPrivate {
public:
	PropertiesManagerViewPrivate()
		:	m_addAction( 0 )
		,	m_editAction( 0 )
		,	m_delAction( 0 )
		,	m_promoteAction( 0 )
	{
	}

	QAction * m_addAction;
	QAction * m_editAction;
	QAction * m_delAction;
	QAction * m_promoteAction;
}; // class PropertiesManagerViewPrivate


//
// PropertiesManagerView
//

PropertiesManagerView::PropertiesManagerView( QWidget * parent )
	:	QTreeView( parent )
	,	d( new PropertiesManagerViewPrivate )
{
}

PropertiesManagerView::~PropertiesManagerView()
{
}

void
PropertiesManagerView::setActions( QAction * add,
	QAction * edit, QAction * del, QAction * promote )
{
	d->m_addAction = add;
	d->m_editAction = edit;
	d->m_delAction = del;
	d->m_promoteAction = promote;
}

void
PropertiesManagerView::contextMenuEvent( QContextMenuEvent * e )
{
	QMenu menu( this );

	menu.addAction( d->m_addAction );
	menu.addAction( d->m_editAction );
	menu.addAction( d->m_delAction );
	menu.addAction( d->m_promoteAction );

	const QModelIndexList indexes = selectionModel()->selectedRows();

	if( !indexes.isEmpty() )
	{
		d->m_editAction->setEnabled( true );
		d->m_delAction->setEnabled( true );
		d->m_promoteAction->setEnabled( true );
	}
	else
	{
		d->m_editAction->setEnabled( false );
		d->m_delAction->setEnabled( false );
		d->m_promoteAction->setEnabled( false );
	}

	menu.exec( e->globalPos() );

	e->accept();
}

} /* namespace Globe */

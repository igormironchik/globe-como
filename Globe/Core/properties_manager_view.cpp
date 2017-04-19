
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

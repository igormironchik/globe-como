
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2014 Igor Mironchik

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
	{
	}

	QAction * m_addAction;
	QAction * m_editAction;
	QAction * m_delAction;
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
	QAction * edit, QAction * del )
{
	d->m_addAction = add;
	d->m_editAction = edit;
	d->m_delAction = del;
}

void
PropertiesManagerView::contextMenuEvent( QContextMenuEvent * e )
{
	QMenu menu( this );

	menu.addAction( d->m_addAction );
	menu.addAction( d->m_editAction );
	menu.addAction( d->m_delAction );

	const QModelIndexList indexes = selectionModel()->selectedRows();

	if( !indexes.isEmpty() )
	{
		d->m_editAction->setEnabled( true );
		d->m_delAction->setEnabled( true );
	}
	else
	{
		d->m_editAction->setEnabled( false );
		d->m_delAction->setEnabled( false );
	}

	menu.exec( e->globalPos() );

	e->accept();
}

} /* namespace Globe */

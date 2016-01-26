
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

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
#include <Globe/Core/sounds_disabled_view.hpp>
#include <Globe/Core/sounds_disabled_model.hpp>

// Qt include.
#include <QMenu>
#include <QContextMenuEvent>
#include <QSortFilterProxyModel>


namespace Globe {

//
// DisabledSoundsViewPrivate
//

class DisabledSoundsViewPrivate {
public:
	DisabledSoundsViewPrivate()
		:	m_model( 0 )
		,	m_sortModel( 0 )
	{
	}

	//! Model.
	DisabledSoundsModel * m_model;
	//! Sort model.
	QSortFilterProxyModel * m_sortModel;
	//! Current index.
	QModelIndex m_currentIndex;
}; // class DisabledSoundsViewPrivate


//
// DisabledSoundsView
//

DisabledSoundsView::DisabledSoundsView( QWidget * parent )
	:	QTreeView( parent )
	,	d( new DisabledSoundsViewPrivate )
{
	init();
}

DisabledSoundsView::~DisabledSoundsView()
{
}

void
DisabledSoundsView::enableSound()
{
	d->m_model->enableSound(
		d->m_sortModel->mapToSource( d->m_currentIndex ) );
}

void
DisabledSoundsView::resort()
{
	d->m_sortModel->sort( d->m_sortModel->sortColumn(),
		d->m_sortModel->sortOrder() );
}

void
DisabledSoundsView::contextMenuEvent( QContextMenuEvent * event )
{
	QMenu menu( this );

	d->m_currentIndex = currentIndex();

	if( d->m_currentIndex.isValid() )
	{
		menu.addAction( QIcon( ":/img/add_22x22.png" ),
			tr( "Enable Sound" ),
			this, SLOT( enableSound() ) );

		menu.exec( event->globalPos() );

		event->accept();
	}
	else
		event->ignore();
}

void
DisabledSoundsView::init()
{
	setRootIsDecorated( false );
	setSortingEnabled( true );
	setSelectionMode( QAbstractItemView::ExtendedSelection );
	setSelectionBehavior( QAbstractItemView::SelectRows );
	setWordWrap( true );
	setAlternatingRowColors( true );

	d->m_model = new DisabledSoundsModel( this );

	d->m_sortModel = new QSortFilterProxyModel( this );

	d->m_sortModel->setSourceModel( d->m_model );

	setModel( d->m_sortModel );

	connect( d->m_model, &DisabledSoundsModel::resortNeeded,
		this, &DisabledSoundsView::resort );
}

} /* namespace Globe */

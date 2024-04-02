
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/sounds_disabled_view.hpp>
#include <Core/sounds_disabled_model.hpp>

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

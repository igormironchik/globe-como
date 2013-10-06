
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
#include <Globe/sounds_disabled_view.hpp>
#include <Globe/sounds_disabled_model.hpp>

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

	connect( d->m_model, SIGNAL( resortNeeded() ),
		this, SLOT( resort() ) );
}

} /* namespace Globe */

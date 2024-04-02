
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/sounds_played_view.hpp>
#include <Core/sounds_played_model.hpp>
#include <Core/color_for_level.hpp>
#include <Core/sounds_disabled_to_dialog.hpp>
#include <Core/sounds_disabled.hpp>

// Qt include.
#include <QMenu>
#include <QContextMenuEvent>
#include <QPainter>


namespace Globe {

//
// PlayedSoundsViewPrivate
//

class PlayedSoundsViewPrivate {
public:
	PlayedSoundsViewPrivate()
		:	m_model( 0 )
	{
	}

	//! Model.
	PlayedSoundsModel * m_model;
	//! Current record.
	PlayedSoundsModelRecord m_currentRecord;
}; // class PlayedSoundsViewPrivate


//
// PlayedSoundsView
//

PlayedSoundsView::PlayedSoundsView( QWidget * parent )
	:	QTreeView( parent )
	,	d( new PlayedSoundsViewPrivate )
{
	init();
}

PlayedSoundsView::~PlayedSoundsView()
{
}

PlayedSoundsModel *
PlayedSoundsView::model()
{
	return d->m_model;
}

void
PlayedSoundsView::disableSound()
{
	QDateTime to;

	DisableSoundToDialog dlg( to, this );

	if( dlg.exec() == QDialog::Accepted )
	{
		if( to > QDateTime::currentDateTime() )
		{
			DisabledSounds::instance().disableSounds(
				d->m_currentRecord.source(),
				d->m_currentRecord.channelName(), to );
		}
	}
}

void
PlayedSoundsView::contextMenuEvent( QContextMenuEvent * event )
{
	QMenu menu( this );

	const QModelIndex index = currentIndex();

	if( index.isValid() )
	{
		d->m_currentRecord = d->m_model->record( index );

		menu.addAction( QIcon( ":/img/remove_22x22.png" ),
			tr( "Disable Sound" ),
			this, SLOT( disableSound() ) );

		menu.exec( event->globalPos() );

		event->accept();
	}
	else
		event->ignore();
}

void
PlayedSoundsView::drawRow( QPainter * painter, const QStyleOptionViewItem & option,
	const QModelIndex & index ) const
{
	painter->fillRect( option.rect,
		ColorForLevel::instance().color( d->m_model->record( index ).level() ) );

	QTreeView::drawRow( painter, option, index );
}

void
PlayedSoundsView::init()
{
	setRootIsDecorated( false );
	setSortingEnabled( false );
	setSelectionMode( QAbstractItemView::ExtendedSelection );
	setSelectionBehavior( QAbstractItemView::SelectRows );
	setWordWrap( true );

	d->m_model = new PlayedSoundsModel( this );

	setModel( d->m_model );
}

} /* namespace Globe */


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

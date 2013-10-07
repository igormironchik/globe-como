
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
#include <Globe/sounds_played_view.hpp>
#include <Globe/sounds_played_model.hpp>
#include <Globe/color_for_level.hpp>
#include <Globe/sounds_disabled_to_dialog.hpp>
#include <Globe/sounds_disabled.hpp>

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

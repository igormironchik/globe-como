
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SOUNDS_PLAYED_VIEW_HPP__INCLUDED
#define GLOBE__SOUNDS_PLAYED_VIEW_HPP__INCLUDED

// Qt include.
#include <QTreeView>
#include <QScopedPointer>


namespace Globe {

class PlayedSoundsModel;


//
// PlayedSoundsView
//

class PlayedSoundsViewPrivate;

//! View with played sounds.
class PlayedSoundsView
	:	public QTreeView
{
	Q_OBJECT

public:
	PlayedSoundsView( QWidget * parent = 0 );

	~PlayedSoundsView();

	//! \return Model.
	PlayedSoundsModel * model();

private slots:
	//! Disable sound for the selected item.
	void disableSound();

protected:
	//! Context menu event.
	void contextMenuEvent( QContextMenuEvent * event );
	//! Draw row.
	void drawRow( QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index ) const;

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( PlayedSoundsView )

	QScopedPointer< PlayedSoundsViewPrivate > d;
}; // class PlayedSoundsView

} /* namespace Globe */

#endif // GLOBE__SOUNDS_PLAYED_VIEW_HPP__INCLUDED

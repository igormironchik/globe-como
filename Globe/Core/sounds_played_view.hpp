
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

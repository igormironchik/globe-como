
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

#ifndef GLOBE__SOUNDS_DISABLED_VIEW_HPP__INCLUDED
#define GLOBE__SOUNDS_DISABLED_VIEW_HPP__INCLUDED

// Qt include.
#include <QTreeView>
#include <QScopedPointer>


namespace Globe {

//
// DisabledSoundsView
//

class DisabledSoundsViewPrivate;

//! View with played sounds.
class DisabledSoundsView
	:	public QTreeView
{
	Q_OBJECT

public:
	DisabledSoundsView( QWidget * parent = 0 );

	~DisabledSoundsView();

private slots:
	//! Enable sound for the selected item.
	void enableSound();
	//! Resort.
	void resort();

protected:
	//! Context menu event.
	void contextMenuEvent( QContextMenuEvent * event );

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( DisabledSoundsView )

	QScopedPointer< DisabledSoundsViewPrivate > d;
}; // class DisabledSoundsView

} /* namespace Globe */

#endif // GLOBE__SOUNDS_DISABLED_VIEW_HPP__INCLUDED


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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

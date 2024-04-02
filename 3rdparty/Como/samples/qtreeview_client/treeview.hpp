
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef COMO__SAMPLES__QLISTVIEW_CLIENT__TREEVIEW_HPP__INCLUDED
#define COMO__SAMPLES__QLISTVIEW_CLIENT__TREEVIEW_HPP__INCLUDED

// Qt include.
#include <QTreeView>
#include <QScopedPointer>


class Model;


//
// TreeView
//

//! ListView with Como::Source sources.
class TreeView
	:	public QTreeView
{
	Q_OBJECT

public:
	explicit TreeView( Model * model, QWidget * parent = 0 );
	~TreeView();

protected:
	void drawRow( QPainter * painter,
		const QStyleOptionViewItem & option,
		const QModelIndex & index ) const;

protected slots:
	void dataChanged( const QModelIndex & topLeft,
		const QModelIndex & bottomRight );

private:
	void init();

private:
	Q_DISABLE_COPY( TreeView )

	struct TreeViewPrivate;
	QScopedPointer< TreeViewPrivate > d;
}; // class TreeView

#endif // COMO__SAMPLES__QLISTVIEW_CLIENT__TREEVIEW_HPP__INCLUDED

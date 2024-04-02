
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__LOG_SOURCES_VIEW_HPP__INCLUDED
#define GLOBE__LOG_SOURCES_VIEW_HPP__INCLUDED

// Qt include.
#include <QTreeView>
#include <QScopedPointer>


namespace Globe {

class LogSourcesModel;


//
// LogSourcesView
//

class LogSourcesViewPrivate;

//! View of the sources log.
class LogSourcesView
	:	public QTreeView
{
	Q_OBJECT

public:
	LogSourcesView( QWidget * parent = 0 );

	~LogSourcesView();

	//! \return Underlying model.
	LogSourcesModel * model();

protected slots:
	//! Selection changed.
	void selectionChanged( const QItemSelection & selected,
		const QItemSelection & deselected );

private slots:
	//! Select all.
	void selectAllImplementation();
	//! Copy.
	void copyImplementation();
	//! Section resized.
	void sectionResized( int section, int, int );

protected:
	void drawRow( QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index ) const;
	void contextMenuEvent( QContextMenuEvent * event );

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( LogSourcesView )

	QScopedPointer< LogSourcesViewPrivate > d;
}; // class LogSourcesView

} /* namespace Globe */

#endif // GLOBE__LOG_SOURCES_VIEW_HPP__INCLUDED

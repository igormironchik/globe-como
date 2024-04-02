
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__LOG_EVENT_VIEW_HPP__INCLUDED
#define GLOBE__LOG_EVENT_VIEW_HPP__INCLUDED

// Qt include.
#include <QTreeView>
#include <QScopedPointer>

// Globe include.
#include <Core/export.hpp>


namespace Globe {

class LogEventViewModel;


//
// LogEventView
//

class LogEventViewPrivate;

//! View of the event log.
class CORE_EXPORT LogEventView
	:	public QTreeView
{
	Q_OBJECT

public:
	LogEventView( QWidget * parent = 0 );

	~LogEventView();

	//! \return Underlying model.
	LogEventViewModel * model();

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
	//! Context menu event.
	void contextMenuEvent( QContextMenuEvent * event );

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( LogEventView )

	QScopedPointer< LogEventViewPrivate > d;
}; // class LogEventView

} /* namespace Globe */

#endif // GLOBE__LOG_EVENT_VIEW_HPP__INCLUDED

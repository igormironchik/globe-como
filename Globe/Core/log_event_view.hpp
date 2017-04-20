
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

#ifndef GLOBE__LOG_EVENT_VIEW_HPP__INCLUDED
#define GLOBE__LOG_EVENT_VIEW_HPP__INCLUDED

// Qt include.
#include <QTreeView>
#include <QScopedPointer>

// Globe include.
#include <Globe/Core/export.hpp>


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

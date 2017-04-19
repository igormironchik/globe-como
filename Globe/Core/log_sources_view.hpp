
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

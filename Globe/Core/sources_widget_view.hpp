
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

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

#ifndef GLOBE__SOURCES_WIDGET_VIEW_HPP__INCLUDED
#define GLOBE__SOURCES_WIDGET_VIEW_HPP__INCLUDED

// Qt include.
#include <QTreeView>
#include <QScopedPointer>

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
QT_END_NAMESPACE


namespace Globe {

class SourcesModel;

//
// SourcesWidgetView
//

class SourcesWidgetViewPrivate;

//! View with sources.
class SourcesWidgetView
	:	public QTreeView
{
	Q_OBJECT

public:
	SourcesWidgetView( QWidget * parent = 0 );
	~SourcesWidgetView();

	//! Set sources model.
	void setSourcesAndSortModels( SourcesModel * model,
		QSortFilterProxyModel * proxyModel );
	//! Set channel's name.
	void setChannelName( const QString & channelName );

protected:
	//! Context menu event.
	void contextMenuEvent( QContextMenuEvent * event );

private slots:
	//! Edit properties.
	void editProperties();
	//! Add properties.
	void addProperties();

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( SourcesWidgetView )

	QScopedPointer< SourcesWidgetViewPrivate > d;
}; // class SourcesWidgetView

} /* namespace Globe */

#endif // GLOBE__SOURCES_WIDGET_VIEW_HPP__INCLUDED

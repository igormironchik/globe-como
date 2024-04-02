
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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

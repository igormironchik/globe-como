
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2013 Igor Mironchik

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
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

class PropertiesManager;
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

	//! Set properties manager.
	void setPropertiesManager( PropertiesManager * propertiesManager );
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

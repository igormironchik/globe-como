
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

// Globe include.
#include <Globe/sources_widget_view.hpp>
#include <Globe/properties_map.hpp>
#include <Globe/properties_manager.hpp>
#include <Globe/sources_model.hpp>

// Qt include.
#include <QContextMenuEvent>
#include <QMenu>
#include <QSortFilterProxyModel>


namespace Globe {

//
// SourcesWidgetViewPrivate;
//

class SourcesWidgetViewPrivate {
public:
	SourcesWidgetViewPrivate()
		:	m_model( 0 )
		,	m_proxyModel( 0 )
	{
	}

	//! Sources model.
	SourcesModel * m_model;
	//! Proxy model.
	QSortFilterProxyModel * m_proxyModel;
	//! Name of the current channel.
	QString m_channelName;
	//! Properties key.
	PropertiesKey m_key;
	//! Source.
	Como::Source m_source;
}; // class SourcesWidgetViewPrivate;


//
// SourcesWidgetView
//

SourcesWidgetView::SourcesWidgetView( QWidget * parent )
	:	QTreeView( parent )
	,	d( new SourcesWidgetViewPrivate )
{
	init();
}

SourcesWidgetView::~SourcesWidgetView()
{
}

void
SourcesWidgetView::setSourcesAndSortModels( SourcesModel * model,
	QSortFilterProxyModel * proxyModel )
{
	d->m_model = model;
	d->m_proxyModel = proxyModel;
}

void
SourcesWidgetView::setChannelName( const QString & channelName )
{
	d->m_channelName= channelName;
}

void
SourcesWidgetView::contextMenuEvent( QContextMenuEvent * event )
{
	if( d->m_model && d->m_proxyModel && !d->m_channelName.isEmpty() )
	{
		QMenu menu( this );

		const QModelIndex index = currentIndex();

		if( index.isValid() )
		{
			d->m_source = d->m_model->source(
				d->m_proxyModel->mapToSource( index ) );

			const Properties * props = PropertiesManager::instance()
				.findProperties( d->m_source, d->m_channelName, &d->m_key );

			if( props )
				menu.addAction( QIcon( ":/img/edit_22x22.png" ),
					tr( "Edit current properties" ),
					this, SLOT( editProperties() ) );

			menu.addAction( QIcon( ":/img/add_22x22.png" ),
				tr( "Add properties" ),
				this, SLOT( addProperties() ) );

			menu.exec( event->globalPos() );

			event->accept();
		}
		else
			event->ignore();
	}
	else
		event->ignore();
}

void
SourcesWidgetView::editProperties()
{
	PropertiesManager::instance().editProperties( d->m_key, this );
}

void
SourcesWidgetView::addProperties()
{
	PropertiesManager::instance().addProperties( d->m_source,
		d->m_channelName, this );
}

void
SourcesWidgetView::init()
{
	setSortingEnabled( true );
	setRootIsDecorated( false );
	setAlternatingRowColors( true );
}

} /* namespace Globe */

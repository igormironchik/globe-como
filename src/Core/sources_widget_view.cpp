
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2020 Igor Mironchik

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

// Globe include.
#include <Core/sources_widget_view.hpp>
#include <Core/properties_map.hpp>
#include <Core/properties_manager.hpp>
#include <Core/sources_model.hpp>

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
	setDragDropMode( QAbstractItemView::DragOnly );
}

} /* namespace Globe */

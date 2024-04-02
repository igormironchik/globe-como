
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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


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
#include <Core/sources_widget.hpp>
#include <Core/sources.hpp>
#include <Core/sources_model.hpp>
#include <Core/channels.hpp>

#include "ui_sources_widget.h"

// Qt include.
#include <QComboBox>
#include <QSortFilterProxyModel>


namespace Globe {

//
// SourcesWidgetPrivate
//

class SourcesWidgetPrivate {
public:
	SourcesWidgetPrivate()
		:	m_model( 0 )
		,	m_sortModel( 0 )
	{
	}

	//! Ui.
	Ui::SourcesWidget m_ui;
	//! Model.
	SourcesModel * m_model;
	//! Sort model.
	QSortFilterProxyModel * m_sortModel;
}; // class SourcesWidgetPrivate


//
// SourcesWidget
//

SourcesWidget::SourcesWidget( QWidget * parent, Qt::WindowFlags f )
	:	QWidget( parent, f )
	,	d( new SourcesWidgetPrivate )
{
	init();
}

SourcesWidget::~SourcesWidget()
{
}

void
SourcesWidget::init()
{
	d->m_ui.setupUi( this );

	d->m_model = new SourcesModel( this );

	d->m_sortModel = new QSortFilterProxyModel( this );
	d->m_sortModel->setSourceModel( d->m_model );

	d->m_ui.m_view->setModel( d->m_sortModel );
	d->m_ui.m_view->setSourcesAndSortModels( d->m_model, d->m_sortModel );

	d->m_ui.m_channel->setInsertPolicy( QComboBox::InsertAlphabetically );

	connect( &SourcesManager::instance(), &SourcesManager::newSource,
		this, &SourcesWidget::newSource );

	connect( &ChannelsManager::instance(), &ChannelsManager::channelCreated,
		this, &SourcesWidget::channelCreated );

	connect( &ChannelsManager::instance(), &ChannelsManager::channelRemoved,
		this, &SourcesWidget::channelRemoved );

	void ( QComboBox::*signal ) ( int ) =
		&QComboBox::currentIndexChanged;

	connect( d->m_ui.m_channel, signal,
		this, &SourcesWidget::selectChannel );

	connect( d->m_ui.m_view, &SourcesWidgetView::clicked,
		this, &SourcesWidget::itemActivated );

	foreach( const QString & channelName, SourcesManager::instance().channelsNames() )
		d->m_ui.m_channel->addItem( channelName );
}

QString
SourcesWidget::channelName() const
{
	return d->m_ui.m_channel->currentText();
}

void
SourcesWidget::setChannelName( const QString & channelName )
{
	const int index = d->m_ui.m_channel->findText( channelName );

	if( index != -1 )
		d->m_ui.m_channel->setCurrentIndex( index );
}

void
SourcesWidget::newSource( const Como::Source & source,
	const QString & channelName )
{
	if( d->m_ui.m_channel->currentText() == channelName )
		d->m_model->addItem( source );
}

void
SourcesWidget::channelCreated( Channel * channel )
{
	d->m_ui.m_channel->addItem( channel->name() );
}

void
SourcesWidget::channelRemoved( Channel * channel )
{
	const int index = d->m_ui.m_channel->findText( channel->name() );

	if( index != -1 )
	{
		if( index == d->m_ui.m_channel->currentIndex() )
		{
			d->m_ui.m_channel->removeItem( index );
			d->m_ui.m_channel->setCurrentIndex( -1 );
			d->m_model->clear();
		}
		else
			d->m_ui.m_channel->removeItem( index );
	}
}

void
SourcesWidget::selectChannel( int index )
{
	const auto channelName = d->m_ui.m_channel->itemText( index );

	if( !channelName.isEmpty() )
	{
		d->m_model->setChannelName( channelName );
		d->m_model->initModel( SourcesManager::instance().sources( channelName ) );
		d->m_ui.m_view->setChannelName( channelName );

		emit channelSelected( channelName );
	}
}

void
SourcesWidget::itemActivated( const QModelIndex & index )
{
	if( index.isValid() )
		emit sourceSelected( d->m_model->source(
			d->m_sortModel->mapToSource( index ) ) );
}

} /* namespace Globe */

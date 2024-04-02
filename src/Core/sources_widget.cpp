
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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
SourcesWidget::channelCreated( Globe::Channel * channel )
{
	d->m_ui.m_channel->addItem( channel->name() );
}

void
SourcesWidget::channelRemoved( Globe::Channel * channel )
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

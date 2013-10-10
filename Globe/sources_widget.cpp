
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
#include <Globe/sources_widget.hpp>
#include <Globe/sources.hpp>
#include <Globe/sources_model.hpp>
#include <Globe/channels.hpp>

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

	connect( &SourcesManager::instance(),
		SIGNAL( newSource( const Como::Source &, const QString & ) ),
		this, SLOT( newSource( const Como::Source &, const QString & ) ) );

	connect( &ChannelsManager::instance(), SIGNAL( channelCreated( Channel * ) ),
		this, SLOT( channelCreated( Channel * ) ) );

	connect( &ChannelsManager::instance(), SIGNAL( channelRemoved( Channel * ) ),
		this, SLOT( channelRemoved( Channel * ) ) );

	connect( d->m_ui.m_channel, SIGNAL( currentIndexChanged( const QString & ) ),
		this, SLOT( selectChannel( const QString & ) ) );

	connect( d->m_ui.m_view, SIGNAL( clicked( const QModelIndex & ) ),
		this, SLOT( itemActivated( const QModelIndex & ) ) );

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
			d->m_ui.m_channel->setCurrentIndex( -1 );
			d->m_model->clear();
		}
		else
			d->m_ui.m_channel->removeItem( index );
	}
}

void
SourcesWidget::selectChannel( const QString & channelName )
{
	if( !channelName.isEmpty() )
	{
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

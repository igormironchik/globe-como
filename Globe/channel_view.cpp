
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

// Qt include.
#include <QtGui/QSortFilterProxyModel>
#include <QtGui/QHeaderView>
#include <QtGui/QPainter>

// Globe include.
#include <Globe/channel_view.hpp>
#include <Globe/channel_view_window_model.hpp>
#include <Globe/color_for_level.hpp>

#ifdef DEBUG

// ModelTest include.
#include <modeltest.h>

#endif


namespace Globe {

//
// ChannelViewPrivate
//

class ChannelViewPrivate {
public:
	ChannelViewPrivate( PropertiesManager * propertiesManager,
		SourcesManager * sourcesManager,
		ChannelsManager * channelsManager,
		ColorForLevel * colorForLevel )
		:	m_model( 0 )
		,	m_sortModel( 0 )
		,	m_propertiesManager( propertiesManager )
		,	m_sourcesManager( sourcesManager )
		,	m_channelsManager( channelsManager )
		,	m_colorForLevel( colorForLevel )
	{
	}

	//! Model.
	ChannelViewWindowModel * m_model;
	//! Sort model.
	QSortFilterProxyModel * m_sortModel;
	//! Properties manager.
	PropertiesManager * m_propertiesManager;
	//! Sources manager.
	SourcesManager * m_sourcesManager;
	//! Channels manager.
	ChannelsManager * m_channelsManager;
	//! Correspondence between level and color.
	ColorForLevel * m_colorForLevel;
}; // class ChannelViewPrivate


//
// ChannelView
//

ChannelView::ChannelView( PropertiesManager * propertiesManager,
		SourcesManager * sourcesManager,
		ChannelsManager * channelsManager,
		ColorForLevel * colorForLevel,
		QWidget * parent )
	:	QTreeView( parent )
	,	d( new ChannelViewPrivate( propertiesManager, sourcesManager,
			channelsManager, colorForLevel ) )
{
	init();
}

ChannelView::~ChannelView()
{
}

ChannelViewWindowModel *
ChannelView::model()
{
	return d->m_model;
}

QSortFilterProxyModel *
ChannelView::sortModel()
{
	return d->m_sortModel;
}

void
ChannelView::drawRow( QPainter * painter, const QStyleOptionViewItem & option,
	const QModelIndex & index ) const
{	
	if( !d->m_model->isConnected() )
		painter->fillRect( option.rect,
			d->m_colorForLevel->disconnectedColor() );
	else
	{
		const QModelIndex actualIndex = d->m_sortModel->mapToSource( index );

		if( !d->m_model->isRegistered( actualIndex ) )
			painter->fillRect( option.rect,
				d->m_colorForLevel->deregisteredColor() );
		else
			painter->fillRect( option.rect,
				d->m_colorForLevel->color( d->m_model->level( actualIndex ) ) );
	}

	QTreeView::drawRow( painter, option, index );
}

void
ChannelView::init()
{
	setRootIsDecorated( false );
	setSortingEnabled( true );

	header()->setStretchLastSection( false );

	d->m_model = new ChannelViewWindowModel( d->m_propertiesManager,
		d->m_sourcesManager, d->m_channelsManager, this );

#ifdef DEBUG
	new ModelTest( d->m_model, this );
#endif

	d->m_sortModel = new QSortFilterProxyModel( this );
	d->m_sortModel->setSourceModel( d->m_model );

	setModel( d->m_sortModel );
}

} /* namespace Globe */

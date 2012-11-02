
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 Igor Mironchik

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
#include <Globe/channels_list.hpp>
#include <Globe/channels.hpp>


namespace Globe {

//
// ChannelsListPrivate
//

class ChannelsListPrivate {
public:
	ChannelsListPrivate( QWidget * parent,
		ChannelsTypeOfSorting typeOfSorting = AsIs,
		Qt::SortOrder sortOrder = Qt::AscendingOrder )
		:	m_widget( new ChannelsListWidget( typeOfSorting, sortOrder, parent ) )
	{
	}

	//! Widget.
	ChannelsListWidget * m_widget;
}; // class ChannelsListPrivate


//
// ChannelsList
//


ChannelsList::ChannelsList( ChannelsTypeOfSorting typeOfSorting = AsIs,
	Qt::SortOrder sortOrder = Qt::AscendingOrder, QWidget * parent )
	:	QScrollArea( parent )
	,	d( new ChannelsListPrivate( this, typeOfSorting, sortOrder ) )
{
	init();
}

void
ChannelsList::init()
{
	setWidget( d->m_widget );
}

void
ChannelsList::addChannel( Channel * channel )
{
	d->m_widget->addChannel( channel );
}

void
ChannelsList::removeChannel( Channel * channel )
{
	d->m_widget->removeChannel( channel );
}


//
// ChannelsListWidgetPrivate
//

class ChannelsListWidgetPrivate {
public:
	ChannelsListWidgetPrivate( ChannelsTypeOfSorting typeOfSorting = AsIs,
		Qt::SortOrder sortOrder = Qt::AscendingOrder )
		:	m_typeOfSorting( typeOfSorting )
		,	m_sortOrder( sortOrder )
	{
	}

	//! Type of sorting.
	ChannelsTypeOfSorting m_typeOfSorting;
	//! Sort order.
	Qt::SortOrder m_sortOrder;
}; // class ChannelsListWidgetPrivate


//
// ChannelsListWidget
//

ChannelsListWidget::ChannelsListWidget( ChannelsTypeOfSorting typeOfSorting = AsIs,
	Qt::SortOrder sortOrder = Qt::AscendingOrder,
	QWidget * parent, Qt::WindowFlags f )
	:	QWidget( parent, f )
	,	d( new ChannelsListWidgetPrivate( typeOfSorting, sortOrder ) )
{
}

void
ChannelsListWidget::addChannel( Channel * channel )
{
}

void
ChannelsListWidget::removeChannel( Channel * channel )
{
}

void
ChannelsListWidget::sort( Qt::SortOrder order, ChannelsTypeOfSorting type )
{
}

void
ChannelsListWidget::showConnectedOnly()
{
}

void
ChannelsListWidget::showDisconnectedOnly()
{
}

void
ChannelsListWidget::showAll()
{
}

} /* namespace Globe */

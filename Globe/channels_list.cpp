
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
#include <Globe/channel_widget.hpp>
#include <Globe/channels.hpp>
#include <Globe/channels_to_show.hpp>

// Qt include.
#include <QtCore/QList>
#include <QtGui/QFrame>
#include <QtGui/QResizeEvent>


namespace Globe {

//
// ChannelsListPrivate
//

class ChannelsListPrivate {
public:
	ChannelsListPrivate( QWidget * parent,
		ShownChannels shownChannels, Qt::SortOrder sortOrder )
		:	m_widget( new ChannelsListWidget( shownChannels, sortOrder, parent ) )
	{
	}

	//! Widget.
	ChannelsListWidget * m_widget;
}; // class ChannelsListPrivate


//
// ChannelsList
//


ChannelsList::ChannelsList( ShownChannels shownChannels,
	Qt::SortOrder sortOrder, QWidget * parent )
	:	QScrollArea( parent )
	,	d( new ChannelsListPrivate( this, shownChannels, sortOrder ) )
{
	init();
}

void
ChannelsList::resizeEvent( QResizeEvent * event )
{
	d->m_widget->resizeWidget( event->size() );

	QScrollArea::resizeEvent( event );
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
// ChannelWidgetAndLine
//

class ChannelWidgetAndLine {
public:
	ChannelWidgetAndLine()
		:	m_widget( 0 )
		,	m_line( 0 )
	{
	}

	ChannelWidgetAndLine( ChannelWidget * widget, QFrame * line )
		:	m_widget( widget )
		,	m_line( line )
	{
	}

	friend bool operator == ( const ChannelWidgetAndLine & w1,
		const ChannelWidgetAndLine & w2 )
	{
		return ( w1.widget() == w2.widget() );
	}

	//! \return ChannelWidget.
	ChannelWidget * widget() const
	{
		return m_widget;
	}

	//! \return Line.
	QFrame * line() const
	{
		return m_line;
	}

private:
	//! ChannelWidget.
	ChannelWidget * m_widget;
	//! Line.
	QFrame * m_line;
}; // class ChannelWidgetAndLine


//
// ChannelsListWidgetPrivate
//

const int channelWidgetPadding = 5;
const int linePadding = 10;
const int spaceBetweenChannelWidgets = 4;

class ChannelsListWidgetPrivate {
public:
	ChannelsListWidgetPrivate( QWidget * widget,
		ShownChannels shownChannels, Qt::SortOrder sortOrder )
		:	m_widget( widget )
		,	m_shownChannels( shownChannels )
		,	m_sortOrder( sortOrder )
		,	m_minWidth( 0 )
		,	m_minHeight( 0 )
		,	m_currentWidth( 0 )
		,	m_currentHeight( 0 )
		,	m_channelsToShowWidget( new ChannelsToShow( widget ) )
		,	m_channelsToShowWidgetHeight( m_channelsToShowWidget->height() )
	{
		m_channelsToShowWidget->move( 0, 0 );
		m_minWidth = m_currentWidth = m_channelsToShowWidget->width();
		m_currentHeight = m_channelsToShowWidget->height();
		m_widget->resize( m_currentWidth, m_currentHeight );
	}

	//! Update widgets position.
	void updateWidgetsPosition()
	{
		int idx = 0;

		foreach( const ChannelWidgetAndLine & w, m_widgets )
		{
			if( !w.widget()->isHidden() )
			{
				w.widget()->move( channelWidgetPadding,
					m_channelsToShowWidgetHeight +
					( idx * m_minHeight ) +
					( idx * spaceBetweenChannelWidgets ) );
				w.line()->move( linePadding, m_channelsToShowWidgetHeight +
					( ( idx + 1 ) * m_minHeight ) +
					( idx * spaceBetweenChannelWidgets ) + 1 );
				w.line()->show();
				++idx;
			}
		}

		ensureLastLineIsNotVisible();

		m_currentHeight = m_channelsToShowWidgetHeight + m_minHeight * idx +
			( ( idx - 1 ) * spaceBetweenChannelWidgets );

		m_widget->resize( m_currentWidth, m_currentHeight );
	}

	//! Ensure that last line is not visible.
	void ensureLastLineIsNotVisible()
	{
		int lastVisibleIndex = 0;
		int i = 0;

		foreach( const ChannelWidgetAndLine & w, m_widgets )
		{
			if( !w.widget()->isHidden() )
				lastVisibleIndex = i;

			++i;
		}

		m_widgets.at( lastVisibleIndex ).line()->hide();
	}

	//! Resize widgets.
	void resizeWidgets( const QSize & s )
	{
		if( s.width() > m_minWidth )
			m_currentWidth = s.width();
		else
			m_currentWidth = m_minWidth;

		const QSize size( m_currentWidth - channelWidgetPadding * 2,
			m_minHeight );

		m_channelsToShowWidget->resize( m_currentWidth,
			m_channelsToShowWidgetHeight );

		foreach( const ChannelWidgetAndLine & w, m_widgets )
		{
			w.widget()->resize( size );
			w.line()->resize( QSize( m_currentWidth - linePadding * 2,
				w.line()->sizeHint().height() ) );
		}
	}

	//! \return ChannelWidgetAndLine for the given channel.
	const ChannelWidgetAndLine & findWidget( Channel * channel )
	{
		static const ChannelWidgetAndLine dummy;

		foreach( const ChannelWidgetAndLine & w, m_widgets )
			if( w.widget()->channel() == channel )
				return w;

		return dummy;
	}

	//! \return Is ChannelWidgetAndLine the last in the list.
	bool isLast( const ChannelWidgetAndLine & w )
	{
		return ( m_widgets.indexOf( w ) == ( m_widgets.size() - 1 ) );
	}

	//! Widget.
	QWidget * m_widget;
	//! Type of sorting.
	ShownChannels m_shownChannels;
	//! Sort order.
	Qt::SortOrder m_sortOrder;
	//! List with child widgets.
	QList< ChannelWidgetAndLine > m_widgets;
	//! Max width of the child widget.
	int m_minWidth;
	//! Max height of the child widget.
	int m_minHeight;
	//! Current width of the widget.
	int m_currentWidth;
	//!Current height of the widget.
	int m_currentHeight;
	//! Widgets that allow to user select display mode of the channels.
	ChannelsToShow * m_channelsToShowWidget;
	//! Height of the m_channelsToShowWidget.
	int m_channelsToShowWidgetHeight;
}; // class ChannelsListWidgetPrivate


//
// ChannelsListWidget
//

ChannelsListWidget::ChannelsListWidget( ShownChannels shownChannels,
	Qt::SortOrder sortOrder, QWidget * parent, Qt::WindowFlags f )
	:	QWidget( parent, f )
	,	d( new ChannelsListWidgetPrivate( this, shownChannels, sortOrder ) )
{
	connect( d->m_channelsToShowWidget, SIGNAL( displayAllChannels() ),
		this, SLOT( showAll() ) );
	connect( d->m_channelsToShowWidget, SIGNAL( displayConnectedChannels() ),
		this, SLOT( showConnectedOnly() ) );
	connect( d->m_channelsToShowWidget, SIGNAL( displayDisconnectedChannels() ),
		this, SLOT( showDisconnectedOnly() ) );
}

void
ChannelsListWidget::addChannel( Channel * channel )
{
	if( channel )
	{
		const ChannelWidgetAndLine & w = d->findWidget( channel );

		if( !w.widget() )
		{
			ChannelWidget * widget = new ChannelWidget( channel, this );
			QFrame * line = new QFrame( this );
			line->setFrameStyle( QFrame::HLine | QFrame::Sunken );
			d->m_widgets.push_back( ChannelWidgetAndLine( widget, line ) );
			widget->resize( widget->sizeHint() );

			const int width = qMax( d->m_minWidth,
				widget->width() + channelWidgetPadding * 2 );
			const int height = qMax( d->m_minHeight, widget->height() );

			if( width > d->m_minWidth )
				d->m_minWidth = width;

			if( height > d->m_minHeight )
				d->m_minHeight = height;

			d->resizeWidgets( size() );

			connect( channel, SIGNAL( connected() ),
				this, SLOT( connected() ) );
			connect( channel, SIGNAL( disconnected() ),
				this, SLOT( disconnected() ) );

			if( d->m_shownChannels == ShowConnectedOnly && !channel->isConnected() )
			{
				widget->hide();
				line->hide();
			}
			else if( d->m_shownChannels == ShowDisconnectedOnly && channel->isConnected() )
			{
				widget->hide();
				line->hide();
			}
			else
			{
				widget->show();
				line->show();
			}

			sort( d->m_sortOrder );
		}
	}
}

void
ChannelsListWidget::removeChannel( Channel * channel )
{
	if( channel )
	{
		disconnect( channel, 0, 0, 0 );

		const ChannelWidgetAndLine & w = d->findWidget( channel );

		if( w.widget() )
		{
			w.widget()->hide();
			w.line()->hide();
			d->m_widgets.removeOne( w );
			w.widget()->deleteLater();
			w.line()->deleteLater();
			d->updateWidgetsPosition();
		}
	}
}

class ChannelWidgetLessThenFunction {
public:
	bool operator() ( const ChannelWidgetAndLine & w1,
		const ChannelWidgetAndLine & w2 )
	{
		return w1.widget()->channel()->name() < w2.widget()->channel()->name();
	}
}; // class ChannelWidgetLessThenFunction

class ChannelWidgetGreaterThenFunction {
public:
	bool operator() ( const ChannelWidgetAndLine & w1,
		const ChannelWidgetAndLine & w2 )
	{
		return w1.widget()->channel()->name() > w2.widget()->channel()->name();
	}
}; // class ChannelWidgetGreaterThenFunction

void
ChannelsListWidget::sort( Qt::SortOrder order )
{
	d->m_sortOrder = order;

	if( order == Qt::AscendingOrder )
	{
		ChannelWidgetLessThenFunction func;
		qSort( d->m_widgets.begin(), d->m_widgets.end(), func );
	}
	else
	{
		ChannelWidgetGreaterThenFunction func;
		qSort( d->m_widgets.begin(), d->m_widgets.end(), func );
	}

	d->updateWidgetsPosition();
}

void
ChannelsListWidget::shownChannels( ShownChannels shownChannels )
{
	d->m_shownChannels = shownChannels;

	if( d->m_shownChannels == ShowConnectedOnly )
		showConnectedOnly();
	else if( d->m_shownChannels == ShowDisconnectedOnly )
		showDisconnectedOnly();
	else
		showAll();
}

void
ChannelsListWidget::showConnectedOnly()
{
	d->m_shownChannels = ShowConnectedOnly;

	foreach( const ChannelWidgetAndLine & w, d->m_widgets )
		if( !w.widget()->channel()->isConnected() )
		{
			w.widget()->hide();
			w.line()->hide();
		}
		else
		{
			w.widget()->show();
			w.line()->show();
		}

	d->updateWidgetsPosition();
}

void
ChannelsListWidget::showDisconnectedOnly()
{
	d->m_shownChannels = ShowDisconnectedOnly;

	foreach( const ChannelWidgetAndLine & w, d->m_widgets )
		if( w.widget()->channel()->isConnected() )
		{
			w.widget()->hide();
			w.line()->hide();
		}
		else
		{
			w.widget()->show();
			w.line()->show();
		}

	d->updateWidgetsPosition();
}

void
ChannelsListWidget::showAll()
{
	d->m_shownChannels = ShowAll;

	foreach( const ChannelWidgetAndLine & w, d->m_widgets )
	{
		if( w.widget()->isHidden() )
		{
			w.widget()->show();
			w.line()->show();
		}
	}

	d->updateWidgetsPosition();
}

void
ChannelsListWidget::resizeWidget( const QSize & size )
{
	d->resizeWidgets( size );

	int width = qMax( d->m_currentWidth, size.width() );
	int height = qMax( d->m_currentHeight, size.height() );

	resize( QSize( width, height ) );
}

void
ChannelsListWidget::connected()
{
	Channel * ch = qobject_cast< Channel* > ( sender() );
	const ChannelWidgetAndLine & w = d->findWidget( ch );

	if( w.widget() )
	{
		if( d->m_shownChannels == ShowConnectedOnly )
		{
			w.widget()->show();
			w.line()->show();
			d->updateWidgetsPosition();
		}
		else if( d->m_shownChannels == ShowDisconnectedOnly )
		{
			w.widget()->hide();
			w.line()->hide();
			d->updateWidgetsPosition();
		}
	}
}

void
ChannelsListWidget::disconnected()
{
	Channel * ch = qobject_cast< Channel* > ( sender() );
	const ChannelWidgetAndLine & w = d->findWidget( ch );

	if( w.widget() )
	{
		if( d->m_shownChannels == ShowConnectedOnly )
		{
			w.widget()->hide();
			w.line()->hide();
			d->updateWidgetsPosition();
		}
		else if( d->m_shownChannels == ShowDisconnectedOnly )
		{
			w.widget()->show();
			w.line()->show();
			d->updateWidgetsPosition();
		}
	}
}

} /* namespace Globe */

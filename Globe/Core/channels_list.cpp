
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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
#include <Globe/Core/channels_list.hpp>
#include <Globe/Core/channel_widget.hpp>
#include <Globe/Core/channels.hpp>
#include <Globe/Core/channel_attributes.hpp>
#include <Globe/Core/mainwindow.hpp>
#include <Globe/Core/log.hpp>

// Qt include.
#include <QList>
#include <QFrame>
#include <QResizeEvent>
#include <QContextMenuEvent>
#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QMessageBox>


namespace Globe {

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

class ChannelsListPrivate {
public:
	ChannelsListPrivate( QWidget * widget,
		ShownChannels shownChannels,
		Qt::SortOrder sortOrder )
		:	m_widget( widget )
		,	m_sortOrder( sortOrder )
		,	m_minWidth( 0 )
		,	m_minHeight( 0 )
		,	m_currentWidth( 0 )
		,	m_currentHeight( 0 )
		,	m_channelsToShowWidget( new ChannelsToShow( shownChannels, widget ) )
		,	m_channelsToShowWidgetHeight( m_channelsToShowWidget->sizeHint().height() )
		,	m_addChannelAction( 0 )
		,	m_delChannelAction( 0 )
		,	m_showChannelViewAction( 0 )
		,	m_currentWidgetIndex( -1 )
	{
		m_channelsToShowWidget->move( 0, 0 );
		m_minWidth = m_currentWidth = m_channelsToShowWidget->width();
		m_currentHeight = m_channelsToShowWidget->sizeHint().height();
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
		int lastVisibleIndex = -1;
		int i = 0;

		foreach( const ChannelWidgetAndLine & w, m_widgets )
		{
			if( !w.widget()->isHidden() )
				lastVisibleIndex = i;

			++i;
		}

		if( lastVisibleIndex != -1 )
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

	/*!
		\return Index of the ChannelWidgetAndLine for the given \a pos
		or -1 if there is no ChannelWidget for the given \a pos.
	*/
	int indexOfChannelWidget( const QPoint & pos )
	{
		int index = 0;

		foreach( const ChannelWidgetAndLine & w, m_widgets )
		{
			if( w.widget()->geometry().contains( pos ) )
				return index;

			++index;
		}

		return -1;
	}

	//! Widget.
	QWidget * m_widget;
	//! Sort order.
	Qt::SortOrder m_sortOrder;
	//! List with child widgets.
	QList< ChannelWidgetAndLine > m_widgets;
	//! Min width of the child widget.
	int m_minWidth;
	//! Min height of the child widget.
	int m_minHeight;
	//! Current width of the widget.
	int m_currentWidth;
	//! Current height of the widget.
	int m_currentHeight;
	//! Widgets that allow to user select display mode of the channels.
	ChannelsToShow * m_channelsToShowWidget;
	//! Height of the m_channelsToShowWidget.
	int m_channelsToShowWidgetHeight;
	//! Add new channel action.
	QAction * m_addChannelAction;
	//! Remove channel action.
	QAction * m_delChannelAction;
	//! Show channel view.
	QAction * m_showChannelViewAction;
	//! Index of current ChannelWidget.
	int m_currentWidgetIndex;
}; // class ChannelsListPrivate


//
// ChannelsList
//

ChannelsList::ChannelsList( ShownChannels shownChannels,
	Qt::SortOrder sortOrder,
	QWidget * parent,
	Qt::WindowFlags f )
	:	ScrolledWidget( parent, f )
	,	d( new ChannelsListPrivate( this, shownChannels, sortOrder ) )
{
	init();
}

ChannelsList::~ChannelsList()
{
}

void
ChannelsList::init()
{
	d->m_addChannelAction = new QAction( QIcon( ":/img/add_22x22.png" ),
		tr( "Add Channel" ), this );
	d->m_delChannelAction = new QAction( QIcon( ":/img/remove_22x22.png" ),
		tr( "Delete Channel" ), this );
	d->m_showChannelViewAction = new QAction( tr( "Show Channel View" ), this );

	connect( d->m_channelsToShowWidget, &ChannelsToShow::displayAllChannels,
		this, &ChannelsList::showAll );
	connect( d->m_channelsToShowWidget, &ChannelsToShow::displayConnectedChannels,
		this, &ChannelsList::showConnectedOnly );
	connect( d->m_channelsToShowWidget, &ChannelsToShow::displayDisconnectedChannels,
		this, &ChannelsList::showDisconnectedOnly );

	void ( ChannelsList::*slot )() = &ChannelsList::addChannel;

	connect( d->m_addChannelAction, &QAction::triggered,
		this, slot );
	connect( d->m_delChannelAction, &QAction::triggered,
		this, &ChannelsList::delChannel );
	connect( d->m_showChannelViewAction, &QAction::triggered,
		this, &ChannelsList::showChannelView );
}

void
ChannelsList::addChannel( Channel * channel )
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

			connect( channel, &Channel::connected,
				this, &ChannelsList::connected );
			connect( channel, &Channel::disconnected,
				this, &ChannelsList::disconnected );

			if( d->m_channelsToShowWidget->shownChannelsMode() == ShowConnectedOnly &&
				!channel->isConnected() )
			{
				widget->hide();
				line->hide();
			}
			else if( d->m_channelsToShowWidget->shownChannelsMode() == ShowDisconnectedOnly &&
				channel->isConnected() )
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
ChannelsList::removeChannel( Channel * channel )
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

ShownChannels
ChannelsList::shownChannelsMode() const
{
	return d->m_channelsToShowWidget->shownChannelsMode();
}

void
ChannelsList::setShownChannelsMode( ShownChannels mode )
{
	d->m_channelsToShowWidget->setShownChannelsMode( mode );
}

void
ChannelsList::contextMenuEvent( QContextMenuEvent * event )
{
	d->m_currentWidgetIndex = d->indexOfChannelWidget( event->pos() );

	QMenu menu( this );
	menu.addAction( d->m_addChannelAction );

	if( d->m_currentWidgetIndex != -1 )
	{
		menu.addAction( d->m_delChannelAction );
		menu.addSeparator();
		menu.addAction( d->m_showChannelViewAction );
	}

	menu.exec( event->globalPos() );

	event->accept();
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
ChannelsList::sort( Qt::SortOrder order )
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
ChannelsList::showConnectedOnly()
{
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
ChannelsList::showDisconnectedOnly()
{
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
ChannelsList::showAll()
{
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
ChannelsList::resizeWidget( const QSize & size )
{
	d->resizeWidgets( size );

	int width = qMax( d->m_currentWidth, size.width() );
	int height = qMax( d->m_currentHeight, size.height() );

	resize( QSize( width, height ) );
}

void
ChannelsList::connected()
{
	Channel * ch = dynamic_cast< Channel* > ( sender() );
	const ChannelWidgetAndLine & w = d->findWidget( ch );

	if( w.widget() )
	{
		if( d->m_channelsToShowWidget->shownChannelsMode() == ShowConnectedOnly )
		{
			w.widget()->show();
			w.line()->show();
			d->updateWidgetsPosition();
		}
		else if( d->m_channelsToShowWidget->shownChannelsMode() == ShowDisconnectedOnly )
		{
			w.widget()->hide();
			w.line()->hide();
			d->updateWidgetsPosition();
		}
	}
}

void
ChannelsList::disconnected()
{
	Channel * ch = dynamic_cast< Channel* > ( sender() );
	const ChannelWidgetAndLine & w = d->findWidget( ch );

	if( w.widget() )
	{
		if( d->m_channelsToShowWidget->shownChannelsMode() == ShowConnectedOnly )
		{
			w.widget()->hide();
			w.line()->hide();
			d->updateWidgetsPosition();
		}
		else if( d->m_channelsToShowWidget->shownChannelsMode() == ShowDisconnectedOnly )
		{
			w.widget()->show();
			w.line()->show();
			d->updateWidgetsPosition();
		}
	}
}

void
ChannelsList::addChannel()
{
	ChannelAttributes attributes;

	const QStringList types = ChannelsManager::instance().supportedChannels();

	if( !types.isEmpty() )
	{
		ChannelAttributesDialog dlg( attributes, types, this );

		if( QDialog::Accepted == dlg.exec() )
		{
			Channel * channel = ChannelsManager::instance().createChannel(
				attributes.name(), attributes.address(), attributes.port(),
				attributes.type() );

			if( channel )
				addChannel( channel );
			else
			{
				Log::instance().writeMsgToEventLog( LogLevelError,
					QString( "Unable to create channel with "
						"name: \"%1\" address: \"%2\", port: %3 "
						"and type: \"%4\"" )
							.arg( attributes.name() )
							.arg( attributes.address().toString() )
							.arg( QString::number( attributes.port() ) )
							.arg( attributes.type() ) );

				QMessageBox::critical( 0, tr( "Unable to create channel..." ),
					tr( "Unable to create channel with:\n"
						"\tName: %1\n"
						"\tAddress: %2\n"
						"\tPort: %3\n"
						"\tType: %4" )
							.arg( attributes.name() )
							.arg( attributes.address().toString() )
							.arg( QString::number( attributes.port() ) )
							.arg( attributes.type() ) );
			}
		}
	}
	else
		QMessageBox::critical( 0, tr( "Unable to create channel..." ),
			tr( "Unable to create channel.\n"
				"No one channel plugin has been loaded." ) );
}

void
ChannelsList::delChannel()
{
	if( d->m_currentWidgetIndex != -1 )
	{
		const ChannelWidgetAndLine & widgetAndLine =
			d->m_widgets.at( d->m_currentWidgetIndex );

		if( QMessageBox::question( this,
				tr( "You are about to delete channel..." ),
				tr( "You are about to delete channel \"%1\".\n"
					"Are you sure?" )
					.arg( widgetAndLine.widget()->channel()->name() ) )
			== QMessageBox::Yes )
		{
			ChannelsManager::instance().removeChannel(
				widgetAndLine.widget()->channel()->name() );

			widgetAndLine.widget()->hide();
			widgetAndLine.line()->hide();
			widgetAndLine.widget()->deleteLater();
			widgetAndLine.line()->deleteLater();

			d->m_widgets.removeAt( d->m_currentWidgetIndex );
			d->m_currentWidgetIndex = -1;

			d->updateWidgetsPosition();
		}
	}
}

void
ChannelsList::showChannelView()
{
	if( d->m_currentWidgetIndex != -1 )
	{
		const ChannelWidgetAndLine & widgetAndLine =
			d->m_widgets.at( d->m_currentWidgetIndex );

		d->m_currentWidgetIndex = -1;

		MainWindow::instance().showChannelView(
			widgetAndLine.widget()->channel()->name() );
	}
}

} /* namespace Globe */

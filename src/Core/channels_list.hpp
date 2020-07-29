
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

#ifndef GLOBE__CHANNELS_LIST_HPP__INCLUDED
#define GLOBE__CHANNELS_LIST_HPP__INCLUDED

// Qt include.
#include <QScopedPointer>

// Globe include.
#include <Core/channels_to_show.hpp>
#include <Core/scrolled_widget.hpp>


namespace Globe {

class Channel;


class ChannelsListPrivate;

//
// ChannelsList
//

/*!
	Widget with list of channel widgets.
	This widget is used in ChannelsList to present
	list of channel widgets.
*/
class ChannelsList
	:	public ScrolledWidget
{
	Q_OBJECT

public:
	ChannelsList( ShownChannels shownChannels = ShowAll,
		Qt::SortOrder sortOrder = Qt::AscendingOrder,
		QWidget * parent = 0,
		Qt::WindowFlags f = Qt::WindowFlags() );

	~ChannelsList();

	//! Add channel.
	void addChannel( Channel * channel );
	//! Remove channel.
	void removeChannel( Channel * channel );

	//! \return Shown channels mode.
	ShownChannels shownChannelsMode() const;
	//! Set shown channels mode.
	void setShownChannelsMode( ShownChannels mode );

protected:
	void contextMenuEvent( QContextMenuEvent * event );
	//! Resize widget.
	void resizeWidget( const QSize & size );

public slots:
	//! Sort channels in the given order.
	void sort( Qt::SortOrder order );
	//! Show only connected channels.
	void showConnectedOnly();
	//! Show only disconnected channels.
	void showDisconnectedOnly();
	//! Show all channels.
	void showAll();

private slots:
	//! Channel connected.
	void connected();
	//! Channel disconnected.
	void disconnected();
	//! Add new channel.
	void addChannel();
	//! Delete channel.
	void delChannel();
	//! Show channel view.
	void showChannelView();

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( ChannelsList )

	QScopedPointer< ChannelsListPrivate > d;
}; // class ChannelsList

} /* namespace Globe */

#endif // GLOBE__CHANNELS_LIST_HPP__INCLUDED

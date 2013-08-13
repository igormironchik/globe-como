
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

#ifndef GLOBE__CHANNELS_LIST_HPP__INCLUDED
#define GLOBE__CHANNELS_LIST_HPP__INCLUDED

// Qt include.
#include <QScopedPointer>

// Globe include.
#include <Globe/channels_to_show.hpp>
#include <Globe/scrolled_widget.hpp>


namespace Globe {

class Channel;
class ChannelsManager;
class MainWindow;


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
	ChannelsList( MainWindow * mainWindow,
		ChannelsManager * channelsManager,
		ShownChannels shownChannels = ShowAll,
		Qt::SortOrder sortOrder = Qt::AscendingOrder,
		QWidget * parent = 0,
		Qt::WindowFlags f = 0 );
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

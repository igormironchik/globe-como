
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

#ifndef GLOBE__CHANNEL_WIDGET_HPP__INCLUDED
#define GLOBE__CHANNEL_WIDGET_HPP__INCLUDED

// Qt include.
#include <QWidget>
#include <QScopedPointer>


namespace Globe {

class Channel;
class ChannelWidgetPrivate;

//
// ChannelWidget
//

/*!
	Widget that will display channel and controls to
	control channel.
*/
class ChannelWidget
	:	public QWidget
{
	Q_OBJECT

public:
	explicit ChannelWidget( Channel * channel,
		QWidget * parent = 0, Qt::WindowFlags f = 0 );
	~ChannelWidget();

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	//! \return Channel.
	Channel * channel() const;

private slots:
	//! Timeout was changed.
	void timeoutChanged( int msecs );
	//! New message rate.
	void messageRate( int msgCount );
	//! Channel connected.
	void connected();
	//! Channel disconnected.
	void disconnected();
	//! Connect button was clicked.
	void connectButtonClicked();
	//! Disconnect button clicked.
	void disconnectButtonClicked();
	//! Reconnect button was clicked.
	void reconnectButtonClicked();

private:
	//!Init.
	void init();

private:
	Q_DISABLE_COPY( ChannelWidget )

	QScopedPointer< ChannelWidgetPrivate > d;
}; // class ChannelWidget

} /* namespace Globe */

#endif // GLOBE__CHANNEL_WIDGET_HPP__INCLUDED

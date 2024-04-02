
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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
		QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );
	~ChannelWidget();

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	//! \return Channel.
	Channel * channel() const;

public slots:
	//! Set timeout.
	void setTimeout( int t );

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

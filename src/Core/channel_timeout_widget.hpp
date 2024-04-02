
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__CHANNEL_TIMEOUT_WIDGET_HPP__INCLUDED
#define GLOBE__CHANNEL_TIMEOUT_WIDGET_HPP__INCLUDED

// Qt include.
#include <QWidget>
#include <QScopedPointer>


namespace Globe {

class ChannelTimeoutWidgetPrivate;

//
// ChannelTimeoutWidget
//

/*!
	Widget that displays current timeout in the channel
	and allow to set timeout in the channel.
*/
class ChannelTimeoutWidget
	:	public QWidget
{
	Q_OBJECT

signals:
	//! Emits when user change timeout.
	void timeoutChanged( int msecs );

public:
	ChannelTimeoutWidget( int timeout = 0,
		QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );
	~ChannelTimeoutWidget();

	QSize sizeHint() const;
	QSize minimumSizeHint() const;

public slots:
	//! Set timeout.
	void setTimeout( int t );

protected:
	void paintEvent( QPaintEvent * event );
	void mouseMoveEvent( QMouseEvent * event );
	void mousePressEvent( QMouseEvent * event );
	void mouseReleaseEvent( QMouseEvent * event );
	bool event( QEvent * event );
	void toolTipEvent( QEvent * event );

private:
	//! \return Tool tip for current state of the widget.
	QString prepareToolTip() const;

private:
	QScopedPointer< ChannelTimeoutWidgetPrivate > d;
}; // class ChannelTimeoutWidget

} /* namespace Globe */

#endif // GLOBE__CHANNEL_TIMEOUT_WIDGET_HPP__INCLUDED

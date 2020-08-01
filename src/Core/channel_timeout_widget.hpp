
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

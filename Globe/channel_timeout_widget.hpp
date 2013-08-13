
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
		QWidget * parent = 0, Qt::WindowFlags f = 0 );
	~ChannelTimeoutWidget();

	QSize sizeHint() const;
	QSize minimumSizeHint() const;

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

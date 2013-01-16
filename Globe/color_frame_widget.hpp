
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

#ifndef GLOBE__COLOR_FRAME_WIDGET_HPP__INCLUDED
#define GLOBE__COLOR_FRAME_WIDGET_HPP__INCLUDED

// Qt include.
#include <QtGui/QWidget>
#include <QtCore/QScopedPointer>


namespace Globe {

//
// ColorFrameWidget
//

class ColorFrameWidgetPrivate;

//! Widget with colored frame.
class ColorFrameWidget
	:	public QWidget
{
	Q_OBJECT

public:
	ColorFrameWidget( QWidget * parent = 0, Qt::WindowFlags f = 0 );
	~ColorFrameWidget();

	//! Set child widget.
	void setWidget( QWidget * w );

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

public slots:
	//! Highlight as current widget.
	void highlightAsCurrent( bool doUpdate = true );
	//! Remove "current" highlight.
	void removeCurrentHighlightMode( bool doUpdate = true );
	//! Highlight as "context menu requested".
	void highlightAsContextMenuRequested( bool doUpdate = true );
	//! Remove "context menu requested" highlight.
	void removeContextMenuRequestedHighlight( bool doUpdate = true );
	//! Highlight as "wrong" widget.
	void highlightAsWrong( bool doUpdate = true );
	//! Highlight as normal widget.
	void highlightAsNormal( bool doUpdate = true );

protected:
	void resizeEvent( QResizeEvent * event );
	void paintEvent( QPaintEvent * event );

private:
	Q_DISABLE_COPY( ColorFrameWidget )

	QScopedPointer< ColorFrameWidgetPrivate > d;
}; // class ColorFrameWidget

} /* namespace Globe */

#endif // GLOBE__COLOR_FRAME_WIDGET_HPP__INCLUDED


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

// Globe include.
#include <Globe/color_frame_widget.hpp>

// Qt include.
#include <QtGui/QResizeEvent>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtGui/QPalette>
#include <QtCore/QFlags>


namespace Globe {

//
// HighlightMode
//

//! Highlight mode.
enum HighlightMode {
	//! Highlight as normal widget.
	HighlightAsNormal = 0x01,
	//! Highlight as current widget.
	HighlightAsCurrent = 0x02,
	//! Highlight as "wrong" widget.
	HighlightAsWrong = 0x04,
	//! Highlight as "context menu requested".
	HighlightAsContextMenuRequested = 0x08
}; // enum HighlightMode

Q_DECLARE_FLAGS( HighlightModes, HighlightMode )
Q_DECLARE_OPERATORS_FOR_FLAGS( HighlightModes )


static const double borderWidth = 3.0;

static const QSize borderSize = QSize( borderWidth * 2,
	borderWidth * 2 );


//
// ColorFrameWidgetPrivate
//

class ColorFrameWidgetPrivate {
public:
	explicit ColorFrameWidgetPrivate( QWidget * parent )
		:	m_parent( parent )
		,	m_widget( 0 )
		,	m_highlightMode( HighlightAsNormal )
	{
	}

	//! Update size.
	void updateSizeAndPos()
	{
		QSize size = m_widget->minimumSize();
		size += borderSize;

		m_parent->resize( borderSize );

		m_widget->move( borderWidth, borderWidth );
	}

	//! Parent.
	QWidget * m_parent;
	//! Widget.
	QWidget * m_widget;
	//! Highlight mode.
	HighlightModes m_highlightMode;
}; // class ColorFrameWidgetPrivate


//
// ColorFrameWidget
//

ColorFrameWidget::ColorFrameWidget( QWidget * parent, Qt::WindowFlags f )
	:	QWidget( parent, f )
	,	d( new ColorFrameWidgetPrivate( this ) )
{
}

ColorFrameWidget::~ColorFrameWidget()
{
}

void
ColorFrameWidget::setWidget( QWidget * w )
{
	if( w == d->m_widget || !w )
		return;

	if( d->m_widget )
	{
		d->m_widget->deleteLater();
		d->m_widget = 0;
	}

	if( w->parentWidget() != this )
		w->setParent( this );

	d->m_widget = w;

	d->updateSizeAndPos();

	d->m_widget->show();
}

QSize
ColorFrameWidget::minimumSizeHint() const
{
	if( !d->m_widget )
		return QSize();

	QSize size = d->m_widget->minimumSize();

	size += borderSize;

	return size;
}

QSize
ColorFrameWidget::sizeHint() const
{
	return minimumSizeHint();
}

void
ColorFrameWidget::highlightAsCurrent( bool doUpdate )
{
	d->m_highlightMode |= HighlightAsCurrent;

	if( doUpdate )
		update();
}

void
ColorFrameWidget::removeCurrentHighlightMode( bool doUpdate )
{
	d->m_highlightMode ^= HighlightAsCurrent;

	if( doUpdate )
		update();
}

void
ColorFrameWidget::highlightAsContextMenuRequested( bool doUpdate )
{
	d->m_highlightMode |= HighlightAsContextMenuRequested;

	if( doUpdate )
		update();
}

void
ColorFrameWidget::removeContextMenuRequestedHighlight( bool doUpdate )
{
	d->m_highlightMode ^= HighlightAsContextMenuRequested;

	if( doUpdate )
		update();
}

void
ColorFrameWidget::highlightAsWrong( bool doUpdate )
{
	if( d->m_highlightMode & HighlightAsCurrent )
		d->m_highlightMode = HighlightAsCurrent | HighlightAsWrong;
	else
		d->m_highlightMode = HighlightAsWrong;

	if( doUpdate )
		update();
}

void
ColorFrameWidget::highlightAsNormal( bool doUpdate )
{
	if( d->m_highlightMode & HighlightAsCurrent )
		d->m_highlightMode = HighlightAsCurrent | HighlightAsNormal;
	else
		d->m_highlightMode = HighlightAsNormal;

	if( doUpdate )
		update();
}

void
ColorFrameWidget::resizeEvent( QResizeEvent * event )
{
	if( !d->m_widget )
		return;

	QSize size = event->size();

	size -= borderSize;

	d->m_widget->resize( size );
}

void
ColorFrameWidget::paintEvent( QPaintEvent * event )
{
	Q_UNUSED( event )

	QPainter painter( this );

	QPen pen;

	if( d->m_highlightMode & HighlightAsCurrent )
		pen.setColor( palette().color( QPalette::Highlight ) );
	else if( d->m_highlightMode & HighlightAsContextMenuRequested )
		pen.setColor( palette().color( QPalette::Highlight ).lighter() );
	else if( d->m_highlightMode & HighlightAsWrong )
		pen.setColor( Qt::darkRed );
	else if( d->m_highlightMode & HighlightAsNormal )
		pen.setColor( palette().color( QPalette::Window ) );

	pen.setWidth( borderWidth );

	painter.setPen( pen );

	const QRectF rect( (double) borderWidth / 2.0, (double) borderWidth / 2.0,
		(double) width() - borderWidth, (double) height() - borderWidth );

	painter.drawRect( rect );
}

} /* namespace Globe */

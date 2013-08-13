
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
#include <Globe/scrolled_widget.hpp>

// Qt include.
#include <QResizeEvent>


namespace Globe {

//
// ScrolledWidget
//

ScrolledWidget::ScrolledWidget( QWidget * parent, Qt::WindowFlags f )
	:	QWidget( parent, f )
{
}

ScrolledWidget::~ScrolledWidget()
{
}


//
// ScrolledView
//

ScrolledView::ScrolledView( QWidget * parent )
	:	QScrollArea( parent )
	,	m_widget( 0 )
{
}

ScrolledView::~ScrolledView()
{
}

void
ScrolledView::setWidget( ScrolledWidget * w )
{
	m_widget = w;

	QScrollArea::setWidget( m_widget );
}

void
ScrolledView::resizeEvent( QResizeEvent * event )
{
	m_widget->resizeWidget( event->size() );

	QScrollArea::resizeEvent( event );
}

} /* namespace Globe */

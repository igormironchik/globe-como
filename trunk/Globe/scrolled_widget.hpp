
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

#ifndef GLOBE__SCROLLED_WIDGET_HPP__INCLUDED
#define GLOBE__SCROLLED_WIDGET_HPP__INCLUDED

// Qt include.
#include <QtGui/QScrollArea>
#include <QtGui/QWidget>


namespace Globe {

//
// ScrolledWidget
//

//! Scrolled widget.
class ScrolledWidget
	:	public QWidget
{
	Q_OBJECT

	friend class ScrolledView;

public:
	ScrolledWidget( QWidget * parent = 0, Qt::WindowFlags f = 0 );

	virtual ~ScrolledWidget();

protected:
	//! Resize widget.
	virtual void resizeWidget( const QSize & size ) = 0;

private:
	Q_DISABLE_COPY( ScrolledWidget )
}; // class ScrolledWidget


//
// ScrolledView
//

//! Scrolled view.
class ScrolledView
	:	public QScrollArea
{
	Q_OBJECT

public:
	ScrolledView( QWidget * parent = 0 );
	~ScrolledView();

	//! Set widget to scroll.
	void setWidget( ScrolledWidget * w );

protected:
	void resizeEvent( QResizeEvent * event );

private:
	Q_DISABLE_COPY( ScrolledView )

	ScrolledWidget * m_widget;
}; // class ScrolledView

} /* namespace Globe */

#endif // GLOBE__SCROLLED_WIDGET_HPP__INCLUDED

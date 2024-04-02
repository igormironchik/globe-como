
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SCROLLED_WIDGET_HPP__INCLUDED
#define GLOBE__SCROLLED_WIDGET_HPP__INCLUDED

// Qt include.
#include <QScrollArea>
#include <QWidget>


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
	ScrolledWidget( QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );

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

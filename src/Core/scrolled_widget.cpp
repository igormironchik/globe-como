
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/scrolled_widget.hpp>

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

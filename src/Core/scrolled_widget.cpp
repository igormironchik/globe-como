
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

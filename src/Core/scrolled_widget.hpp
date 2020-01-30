
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

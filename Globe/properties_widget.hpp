
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

#ifndef GLOBE__PROPERTIES_WIDGET_HPP__INCLUDED
#define GLOBE__PROPERTIES_WIDGET_HPP__INCLUDED

// Qt include.
#include <QtCore/QScopedPointer>

// Globe include.
#include <Globe/properties.hpp>
#include <Globe/scrolled_widget.hpp>


namespace Globe {

//
// PropertiesList
//

class PropertiesListPrivate;

/*!
	Widget with list of condition widgets.
	This widget is used in PropertiesList to present
	list of condition widgets.
*/
class PropertiesList
	:	public ScrolledWidget
{
	Q_OBJECT

public:
	PropertiesList( QWidget * parent = 0, Qt::WindowFlags f = 0 );
	~PropertiesList();

	//! \return Properties.
	Properties properties() const;
	//! Set properties.
	void setProperties( const Properties & p );

protected:
	void contextMenuEvent( QContextMenuEvent * event );
	//! Resize widget.
	void resizeWidget( const QSize & size );

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( PropertiesList )

	QScopedPointer< PropertiesListPrivate > d;
}; // class PropertiesList

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_WIDGET_HPP__INCLUDED

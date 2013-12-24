
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

#ifndef GLOBE__SCHEME__VIEW_HPP__INCLUDED
#define GLOBE__SCHEME__VIEW_HPP__INCLUDED

// Qt include.
#include <QGraphicsView>
#include <QScopedPointer>


namespace Globe {

namespace Scheme {

class Scene;


//
// View
//

class ViewPrivate;

//! View that will display scene with the scheme.
class View
	:	public QGraphicsView
{
	Q_OBJECT

public:
	View( QWidget * parent = 0 );

	~View();

	//! \return Scene.
	Scene * scene();

protected:
	void dragEnterEvent( QDragEnterEvent * event );
	void dragMoveEvent( QDragMoveEvent * event );
	void dropEvent( QDropEvent * event );

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( View )

	QScopedPointer< ViewPrivate > d;
}; // class View

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__VIEW_HPP__INCLUDED


/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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

	QSize sizeHint() const Q_DECL_OVERRIDE;

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


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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

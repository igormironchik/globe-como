
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
#include <Globe/Scheme/scene.hpp>

#include <Globe/Core/sources_dialog.hpp>

// Qt include.
#include <QWidget>
#include <QPalette>
#include <QGraphicsSceneMouseEvent>


namespace Globe {

namespace Scheme {

//
// ScenePrivate
//

class ScenePrivate {
public:
	ScenePrivate()
		:	m_mode( ViewScene )
		,	m_editMode( EditSceneSelect )
		,	m_parentWidget( 0 )
	{
	}

	//! Mode of the scene.
	SceneMode m_mode;
	//! Edit mode of the scene.
	EditSceneMode m_editMode;
	//! Parent widget.
	QWidget * m_parentWidget;
}; // class ScenePrivate


//
// Scene
//

Scene::Scene( QObject * parent )
	:	QGraphicsScene( parent )
	,	d( new ScenePrivate )
{
	init();
}

Scene::~Scene()
{
}

SceneMode
Scene::mode() const
{
	return d->m_mode;
}

void
Scene::setMode( SceneMode mode )
{
	d->m_mode = mode;
}

EditSceneMode
Scene::editMode() const
{
	return d->m_editMode;
}

void
Scene::setEditMode( EditSceneMode mode )
{
	d->m_editMode = mode;
}

void
Scene::setParentWidget( QWidget * parent )
{
	d->m_parentWidget = parent;
}

void
Scene::mouseReleaseEvent( QGraphicsSceneMouseEvent * mouseEvent )
{
	if( d->m_mode == EditScene )
	{
		if( mouseEvent->button() == Qt::LeftButton )
		{
			switch( d->m_editMode )
			{
				case EditSceneNewSource :
				{
					Como::Source source;
					QString channel;

					SourcesDialog dlg( source, channel, d->m_parentWidget );

					if( dlg.exec() == QDialog::Accepted )
					{

					}
				}
				break;

				case EditSceneNewText :
				{

				}
				break;
			}
		}
	}
}

void
Scene::init()
{
	QWidget w;

	setBackgroundBrush( w.palette().color( QPalette::Window ) );
}

} /* namespace Scheme */

} /* namespace Globe */

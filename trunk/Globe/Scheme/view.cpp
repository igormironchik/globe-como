
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
#include <Globe/Scheme/view.hpp>
#include <Globe/Scheme/scene.hpp>

// Qt include.
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QByteArray>

// Como include.
#include <Como/Source>


namespace Globe {

namespace Scheme {

//
// ViewPrivate
//

class ViewPrivate {
public:
	ViewPrivate()
		:	m_scene( 0 )
	{
	}

	//! Scene.
	Scene * m_scene;
}; // class ViewPrivate


//
// View
//

View::View( QWidget * parent )
	:	QGraphicsView( parent )
	,	d( new ViewPrivate )
{
	init();
}

View::~View()
{
}

Scene *
View::scene()
{
	return d->m_scene;
}

void
View::dragEnterEvent( QDragEnterEvent * event )
{
	if( d->m_scene->mode() == EditScene &&
		event->mimeData()->hasFormat( QLatin1String( "application/como.source" ) ) )
			event->acceptProposedAction();
}

void
View::dragMoveEvent( QDragMoveEvent * event )
{
	if( d->m_scene->mode() == EditScene &&
		event->mimeData()->hasFormat( QLatin1String( "application/como.source" ) ) )
			event->acceptProposedAction();
}

void
View::dropEvent( QDropEvent * event )
{
	if( d->m_scene->mode() == EditScene )
	{
		QByteArray data = event->mimeData()->data(
			QLatin1String( "application/como.source" ) );

		QDataStream stream( &data, QIODevice::ReadOnly );

		QString channelName, sourceName, typeName, description;
		QDateTime dateTime;
		QVariant value;
		quint16 uintType;

		stream >> channelName;
		stream >> uintType;
		stream >> sourceName;
		stream >> typeName;
		stream >> dateTime;
		stream >> description;
		stream >> value;

		Como::Source source( (Como::Source::Type) uintType,
			sourceName, typeName, value, description );
		source.setDateTime( dateTime );

		d->m_scene->addSource( channelName, source,
			mapToScene( event->pos() ) );

		event->acceptProposedAction();
	}
}

void
View::init()
{
	setAcceptDrops( true );

	d->m_scene = new Scene( this );

	d->m_scene->setParentWidget( this );

	setAlignment( Qt::AlignLeft | Qt::AlignTop );

	setScene( d->m_scene );

	setViewportUpdateMode( QGraphicsView::FullViewportUpdate );
}

} /* namespace Scheme */

} /* namespace Globe */

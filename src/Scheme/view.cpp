
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
#include <Scheme/view.hpp>
#include <Scheme/scene.hpp>

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

QSize
View::sizeHint() const
{
	return ( QGraphicsView::sizeHint() + QSize( 10, 10 ) );
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

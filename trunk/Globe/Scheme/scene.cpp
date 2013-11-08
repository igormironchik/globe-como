
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
#include <Globe/Scheme/source.hpp>
#include <Globe/Scheme/selection.hpp>
#include <Globe/Scheme/scheme_cfg.hpp>

#include <Globe/Core/sources_dialog.hpp>
#include <Globe/Core/log.hpp>

// Qt include.
#include <QWidget>
#include <QPalette>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QKeyEvent>

// QtConfFile include.
#include <QtConfFile/Utils>
#include <QtConfFile/Exceptions>


namespace Globe {

namespace Scheme {

//
// DummyItem
//

class DummyItem
	:	public QGraphicsItem
{
public:
	//! \return Bounding rectangle.
	QRectF boundingRect() const
	{
		return QRectF( 0, 0, 1, 1 );
	}

	//! Paint item.
	void paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
		QWidget * widget )
	{
		Q_UNUSED( painter )
		Q_UNUSED( option )
		Q_UNUSED( widget )
	}
}; // class DummyItem


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

	//! Notify all items about scene mode changes.
	void notifyItemsAboutModeChange( SceneMode mode )
	{
		foreach( Source * s, m_sources )
			s->setMode( mode );
	}

	//! Notify all items about scene edit mode changes.
	void notifyItemsAboutEditModeChange( EditSceneMode mode )
	{
		foreach( Source * s, m_sources )
			s->setEditMode( mode );
	}

	//! Mode of the scene.
	SceneMode m_mode;
	//! Edit mode of the scene.
	EditSceneMode m_editMode;
	//! Parent widget.
	QWidget * m_parentWidget;
	//! Source items.
	QMap< QString, Source* > m_sources;
	//! Selection.
	Selection m_selection;
}; // class ScenePrivate


//
// createKey
//

//! Create key for the source.
QString createKey( const Como::Source & source, const QString & channelName )
{
	QString key;

	key.append( channelName );
	key.append( source.typeName() );
	key.append( source.name() );

	return key;
}


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
	d->m_selection.clear();

	d->m_mode = mode;

	d->notifyItemsAboutModeChange( d->m_mode );
}

EditSceneMode
Scene::editMode() const
{
	return d->m_editMode;
}

void
Scene::setEditMode( EditSceneMode mode )
{
	d->m_selection.clear();

	d->m_editMode = mode;

	d->notifyItemsAboutEditModeChange( mode );
}

void
Scene::setParentWidget( QWidget * parent )
{
	d->m_parentWidget = parent;
}

void
Scene::removeSource( Source * source )
{
	const QString key = createKey( source->source(), source->channelName() );

	removeItem( source );

	d->m_selection.removeItem( source );

	d->m_sources.remove( key );
}

void
Scene::loadScheme( const QString & fileName )
{
	SchemeCfgTag tag;

	try {
		QtConfFile::readQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		SchemeCfg cfg = tag.cfg();

		foreach( const SourceCfg & s, cfg.sources() )
		{
			Como::Source source( s.type(), s.sourceName(), s.typeName(),
				QVariant(), QString() );

			const QString key = createKey( source, s.channelName() );

			if( !d->m_sources.contains( key ) )
			{
				Source * item = new Source( source, s.channelName(),
					&d->m_selection, this );
				item->setMode( d->m_mode );
				item->setEditMode( d->m_editMode );
				item->setCfg( s );

				addItem( item );

				d->m_sources.insert( key, item );
			}
		}

		Log::instance().writeMsgToEventLog( LogLevelInfo,
			QString( "Scheme successfully loaded from file \"%1\"." )
				.arg( fileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError,
			QString( "Unable to load scheme configuration "
				"from file \"%1\".\n"
				"%2" )
					.arg( fileName )
					.arg( x.whatAsQString() ) );

		QMessageBox::critical( 0,
			tr( "Unable to read scheme configuration..." ),
			tr( "Unable to read scheme configuration from file \"%1\"\n\n"
				"%2" )
				.arg( fileName )
				.arg( x.whatAsQString() ) );
	}
}

void
Scene::saveScheme( const QString & fileName )
{
	try {
		SchemeCfg cfg;

		QList< SourceCfg > sources;

		foreach( Source * s, d->m_sources )
			sources.append( s->cfg() );

		cfg.setSources( sources );

		SchemeCfgTag tag( cfg );

		QtConfFile::writeQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo,
			QString( "Scheme configuration saved "
				"in file \"%1\"." )
					.arg( fileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError,
			QString( "Unable to save scheme configuration "
				"to file \"%1\"." )
					.arg( fileName ) );

		QMessageBox::critical( 0,
			tr( "Unable to save scheme configuration..." ),
			tr( "Unable to save scheme configuration to file \"%1\".\n\n%2" )
				.arg( fileName )
				.arg( x.whatAsQString() ) );
	}

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
						const QString key = createKey( source, channel );

						if( !d->m_sources.contains( key ) )
						{
							Source * item = new Source( source, channel,
								&d->m_selection, this );
							item->setPos( mouseEvent->scenePos() );
							item->setMode( d->m_mode );
							item->setEditMode( d->m_editMode );

							addItem( item );

							d->m_sources.insert( key, item );
						}
						else
							QMessageBox::warning( 0,
								tr( "Source already on the scheme..." ),
								tr( "Source already on the scheme." ) );
					}

					mouseEvent->accept();
				}
				break;

				case EditSceneNewText :
				{
					mouseEvent->accept();
				}
				break;

				default :
				{
					QGraphicsScene::mouseReleaseEvent( mouseEvent );

					if( !mouseEvent->isAccepted() )
						d->m_selection.clear();
				}
				break;
			}
		}
		else
			QGraphicsScene::mouseReleaseEvent( mouseEvent );
	}
	else
		QGraphicsScene::mouseReleaseEvent( mouseEvent );
}

void
Scene::keyPressEvent( QKeyEvent * keyEvent )
{
	if( !d->m_selection.isEmpty() && d->m_mode == EditScene &&
		d->m_editMode == EditSceneSelect )
	{
		int delta = 1;

		switch( keyEvent->modifiers() )
		{
			case Qt::ShiftModifier : delta = 10; break;
			case Qt::AltModifier : delta = 1; break;
			case Qt::NoModifier : delta = 5; break;
		}

		switch( keyEvent->key() )
		{
			case Qt::Key_Up :
				d->m_selection.moveUp( delta );
				break;

			case Qt::Key_Down :
				d->m_selection.moveDown( delta );
				break;

			case Qt::Key_Left :
				d->m_selection.moveLeft( delta );
				break;

			case Qt::Key_Right :
				d->m_selection.moveRight( delta );
				break;

			case Qt::Key_Delete :
				d->m_selection.deleteItems();
				break;

			default :
				QGraphicsScene::keyPressEvent( keyEvent );
				break;
		}
	}
	else
		QGraphicsScene::keyPressEvent( keyEvent );
}

void
Scene::init()
{
	QWidget w;

	setBackgroundBrush( w.palette().color( QPalette::Window ) );

	DummyItem * item = new DummyItem;

	item->setPos( 0, 0 );

	addItem( item );
}

} /* namespace Scheme */

} /* namespace Globe */

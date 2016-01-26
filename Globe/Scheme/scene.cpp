
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

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
#include <Globe/Scheme/scene.hpp>
#include <Globe/Scheme/source.hpp>
#include <Globe/Scheme/selection.hpp>
#include <Globe/Scheme/scheme_cfg.hpp>
#include <Globe/Scheme/text.hpp>
#include <Globe/Scheme/text_cfg.hpp>

#include <Globe/Core/sources_dialog.hpp>
#include <Globe/Core/log.hpp>
#include <Globe/Core/channels.hpp>
#include <Globe/Core/sources.hpp>
#include <Globe/Core/properties_manager.hpp>

// Qt include.
#include <QWidget>
#include <QPalette>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QKeyEvent>
#include <QMap>
#include <QList>

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
// Key
//

//! Key for sources map.
class Key {
public:
	Key( const Como::Source & source, const QString & channelName )
		:	m_source( source )
		,	m_channelName( channelName )
		,	m_key( m_channelName + m_source.typeName() + m_source.name() )
	{
	}

	//! \return Source.
	const Como::Source & source() const
	{
		return m_source;
	}

	//! \return Channel name.
	const QString & channelName() const
	{
		return m_channelName;
	}

	//! \return String key.
	const QString & key() const
	{
		return m_key;
	}

	friend bool operator < ( const Key & k1, const Key & k2 )
	{
		return k1.key() < k2.key();
	}

private:
	//! Source.
	Como::Source m_source;
	//! Channel name.
	QString m_channelName;
	//! String key.
	QString m_key;
}; // class Key


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

		foreach( Text * t, m_texts )
			t->setMode( mode );
	}

	//! Notify all items about scene edit mode changes.
	void notifyItemsAboutEditModeChange( EditSceneMode mode )
	{
		foreach( Source * s, m_sources )
			s->setEditMode( mode );

		foreach( Text * t, m_texts )
			t->setEditMode( mode );
	}

	//! Source deregistered.
	void sourceDeregistered( const Como::Source & s, const QString & channel )
	{
		const Key key( s, channel );

		QMap< Key, Source* >::Iterator it = m_sources.find( key );

		if( it != m_sources.end() )
			it.value()->deregistered();
	}

	//! Channel disconnected.
	void channelDisconnected( const QString & channel )
	{
		QMapIterator< Key, Source* > it( m_sources );

		while( it.hasNext() )
		{
			it.next();

			if( it.key().channelName() == channel )
					it.value()->disconnected();
		}
	}

	//! Channel deregistered.
	void channelDeregistered( const QString & channel )
	{
		QMapIterator< Key, Source* > it( m_sources );

		while( it.hasNext() )
		{
			it.next();

			if( it.key().channelName() == channel )
					it.value()->deregistered();
		}
	}

	//! Update source.
	void updateSource( const Como::Source & s, const QString & channel )
	{
		const Key key( s, channel );

		QMap< Key, Source* >::Iterator it = m_sources.find( key );

		if( it != m_sources.end() )
			it.value()->setSource( s );
	}

	//! Mode of the scene.
	SceneMode m_mode;
	//! Edit mode of the scene.
	EditSceneMode m_editMode;
	//! Parent widget.
	QWidget * m_parentWidget;
	//! Source items.
	QMap< Key, Source* > m_sources;
	//! Selection.
	Selection m_selection;
	//! Text items.
	QList< Text* > m_texts;
	//! Configuration file.
	QString m_cfgFile;
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
	d->m_selection.clear();

	d->m_mode = mode;

	d->notifyItemsAboutModeChange( d->m_mode );

	if( d->m_mode == ViewScene )
		syncSources();
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
	const Key key( source->source(), source->channelName() );

	removeItem( source );

	d->m_selection.removeItem( source );

	d->m_sources.remove( key );

	if( !isChannelInUse( source->channelName() ) )
		removeChannel( source->channelName() );
}

void
Scene::removeText( Text * text )
{
	removeItem( text );

	d->m_selection.removeItem( text );

	d->m_texts.removeOne( text );
}

void
Scene::loadScheme( const QString & fileName )
{
	SchemeCfgTag tag;

	try {
		QtConfFile::readQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		SchemeCfg cfg = tag.cfg();

		d->m_cfgFile = fileName;

		foreach( const SourceCfg & s, cfg.sources() )
		{
			Como::Source source( s.type(), s.sourceName(), s.typeName(),
				QVariant(), QString() );

			const Key key( source, s.channelName() );

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

		foreach( const TextCfg & t, cfg.texts() )
		{
			Text * text = new Text( t.text(), &d->m_selection, this );
			text->setMode( d->m_mode );
			text->setEditMode( d->m_editMode );
			text->setCfg( t );

			addItem( text );

			d->m_texts.append( text );
		}

		populateChannels();

		syncSources();

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

		QList< TextCfg > texts;

		foreach( Text * t, d->m_texts )
			texts.append( t->cfg() );

		cfg.setTexts( texts );

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
Scene::addSource( const QString & channelName, const Como::Source & source,
	const QPointF & pos )
{
	Source * item = new Source( source, channelName,
		&d->m_selection, this );
	item->setPos( pos );
	item->setMode( d->m_mode );
	item->setEditMode( d->m_editMode );

	addItem( item );

	if( !isChannelInUse( channelName ) )
		addChannel( channelName );

	d->m_sources.insert( Key( source, channelName ), item );
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
						const Key key( source, channel );

						if( !d->m_sources.contains( key ) )
							addSource( channel, source,
								mouseEvent->scenePos() );
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
					Text * text = new Text( tr( "Text" ),
						&d->m_selection, this );
					text->setPos( mouseEvent->scenePos() );
					text->setMode( d->m_mode );
					text->setEditMode( d->m_editMode );

					addItem( text );

					d->m_texts.append( text );

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
Scene::channelRemoved( Channel * channel )
{
	if( d->m_mode == ViewScene )
	{
		d->channelDisconnected( channel->name() );
	}
}

void
Scene::sourceUpdated( const Como::Source & source )
{
	if( d->m_mode == ViewScene )
	{
		Channel * channel = qobject_cast< Channel* > ( sender() );

		if( channel )
			d->updateSource( source, channel->name() );
	}
}

void
Scene::sourceDeregistered( const Como::Source & source )
{
	if( d->m_mode == ViewScene )
	{
		Channel * channel = qobject_cast< Channel* > ( sender() );

		if( channel )
			d->sourceDeregistered( source, channel->name() );
	}
}

void
Scene::connected()
{
	if( d->m_mode == ViewScene )
	{
		Channel * channel = qobject_cast< Channel* > ( sender() );

		d->channelDeregistered( channel->name() );
	}
}

void
Scene::disconnected()
{
	if( d->m_mode == ViewScene )
	{
		Channel * channel = qobject_cast< Channel* > ( sender() );

		d->channelDisconnected( channel->name() );
	}
}

void
Scene::newSource( const Como::Source & s, const QString & channel )
{
	d->updateSource( s, channel );
}

void
Scene::propertiesChanged()
{
	foreach( Source * s, d->m_sources )
		s->propertiesChanged();
}

void
Scene::init()
{
	QWidget w;

	setBackgroundBrush( w.palette().color( QPalette::Window ) );

	DummyItem * item = new DummyItem;

	item->setPos( 0, 0 );

	addItem( item );

	connect( &ChannelsManager::instance(), &ChannelsManager::channelRemoved,
		this, &Scene::channelRemoved );

	connect( &SourcesManager::instance(), &SourcesManager::newSource,
		this, &Scene::newSource );

	connect( &PropertiesManager::instance(),
		&PropertiesManager::propertiesChanged,
		this, &Scene::propertiesChanged );
}

void
Scene::populateChannels()
{
	QStringList channels;

	QMapIterator< Key, Source* > it( d->m_sources );

	while( it.hasNext() )
	{
		it.next();

		if( !channels.contains( it.key().channelName() ) )
			channels.append( it.key().channelName() );
	}

	foreach( const QString & name, channels )
		addChannel( name );
}

void
Scene::addChannel( const QString & name )
{
	Channel * channel = ChannelsManager::instance().channelByName( name );

	if( channel )
	{
		connect( channel, &Channel::sourceUpdated,
			this, &Scene::sourceUpdated );

		connect( channel, &Channel::sourceDeregistered,
			this, &Scene::sourceDeregistered );

		connect( channel, &Channel::connected,
			this, &Scene::connected );

		connect( channel, &Channel::disconnected,
			this, &Scene::disconnected );
	}
	else
	{
		Log::instance().writeMsgToEventLog( LogLevelError,
			QString( "Channel \"%1\" is unavailable for the\n"
					 "scheme \"%2\"." )
				.arg( name )
				.arg( d->m_cfgFile ) );

		QMessageBox::critical( 0, tr( "Channel is unavailable..." ),
			tr( "Channel \"%1\" is unavailable for the\n"
				"scheme \"%2\"." )
				.arg( name )
				.arg( d->m_cfgFile ) );
	}
}

void
Scene::removeChannel( const QString & name )
{
	Channel * channel = ChannelsManager::instance().channelByName( name );

	if( channel )
		disconnect( channel, 0, 0, 0 );
}

bool
Scene::isChannelInUse( const QString & name )
{
	QMapIterator< Key, Source* > it( d->m_sources );

	while( it.hasNext() )
	{
		it.next();

		if( it.key().channelName() == name )
			return true;
	}

	return false;
}

void
Scene::syncSources()
{
	QList< QString > channels;

	{
		QMapIterator< Key, Source* > it( d->m_sources );

		while( it.hasNext() )
		{
			it.next();

			if( !channels.contains( it.key().channelName() ) )
				channels.append( it.key().channelName() );

			Como::Source s = it.value()->source();
			bool isRegistered = false;

			if( SourcesManager::instance().syncSource( it.key().channelName(),
				s, isRegistered ) )
					it.value()->setSource( s );

			if( !isRegistered )
				it.value()->deregistered();
		}
	}

	QMap< QString, bool > connectedDisconnected;

	foreach( const QString & name, channels )
	{
		Channel * channel = ChannelsManager::instance().channelByName( name );

		if( channel )
			connectedDisconnected.insert( name, channel->isConnected() );
		else
			connectedDisconnected.insert( name, false );
	}

	QMapIterator< QString, bool > it( connectedDisconnected );

	while( it.hasNext() )
	{
		it.next();

		if( !it.value() )
			d->channelDisconnected( it.key() );
	}
}

} /* namespace Scheme */

} /* namespace Globe */

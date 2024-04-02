
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SCHEME__SCENE_HPP__INCLUDED
#define GLOBE__SCHEME__SCENE_HPP__INCLUDED

// Globe include.
#include <Scheme/enums.hpp>

// Como include.
#include <Como/Source>

// Qt include.
#include <QGraphicsScene>
#include <QScopedPointer>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE


namespace Globe {

class Channel;


namespace Scheme {

class Source;
class Text;
class Aggregate;
class SchemeCfg;


//
// Scene
//

class ScenePrivate;

//! Scene that will display the scheme.
class Scene
	:	public QGraphicsScene
{
	Q_OBJECT

public:
	Scene( QObject * parent = 0 );

	~Scene();

	//! \return Configuration file name.
	const QString & cfgFile() const;

	//! \return Scheme name.
	const QString & schemeName() const;

	//! \return Scheme configuration.
	SchemeCfg schemeCfg() const;

	//! \return Scene mode.
	SceneMode mode() const;
	//! Set scene mode.
	void setMode( SceneMode mode );

	//! \return Edit scene mode.
	EditSceneMode editMode() const;
	//! Set edit scene mode.
	void setEditMode( EditSceneMode mode );

	//! Set parent widget.
	void setParentWidget( QWidget * parent );

	//! Remove source from the scene.
	void removeSource( Source * source );
	//! Remove text item from the scene.
	void removeText( Text * text );
	//! Remove aggregate from the scene.
	void removeAggregate( Aggregate * agg );

	//! Load scheme.
	void loadScheme( const QString & fileName );
	//! Save scheme.
	void saveScheme( const QString & fileName );

	//! Init scheme.
	void initScheme( const SchemeCfg & cfg );

	//! Add source item.
	void addSource( const QString & channelName, const Como::Source & source,
		const QPointF & pos );

protected:
	void mouseReleaseEvent( QGraphicsSceneMouseEvent * mouseEvent );
	void keyPressEvent( QKeyEvent * keyEvent );

protected:
	friend class Aggregate;

	//! Add channel.
	void addChannel( const QString & name );

private slots:
	//! Channel was removed.
	void channelRemoved( Globe::Channel * channel );
	//! New source or update.
	void sourceUpdated( const Como::Source & source );
	//! Source deregistered.
	void sourceDeregistered( const Como::Source & source );
	//! Connected to host.
	void connected();
	//! Disconnected from host.
	void disconnected();
	//! New source available.
	void newSource( const Como::Source & s, const QString & channel );
	//! Properties changed.
	void propertiesChanged();

private:
	//! Init.
	void init();
	//! Populate channels.
	void populateChannels();
	//! Remove channel.
	void removeChannel( const QString & name );
	//! \return Is channel in use?
	bool isChannelInUse( const QString & name );
	//! Sync sources.
	void syncSources();

private:
	Q_DISABLE_COPY( Scene )

	QScopedPointer< ScenePrivate > d;
}; // class Scene

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__SCENE_HPP__INCLUDED

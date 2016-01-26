
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

#ifndef GLOBE__SCHEME__SCENE_HPP__INCLUDED
#define GLOBE__SCHEME__SCENE_HPP__INCLUDED

// Globe include.
#include <Globe/Scheme/enums.hpp>

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

	//! Load scheme.
	void loadScheme( const QString & fileName );
	//! Save scheme.
	void saveScheme( const QString & fileName );

	//! Add source item.
	void addSource( const QString & channelName, const Como::Source & source,
		const QPointF & pos );

protected:
	void mouseReleaseEvent( QGraphicsSceneMouseEvent * mouseEvent );
	void keyPressEvent( QKeyEvent * keyEvent );

private slots:
	//! Channel was removed.
	void channelRemoved( Channel * channel );
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
	//! Add channel.
	void addChannel( const QString & name );
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

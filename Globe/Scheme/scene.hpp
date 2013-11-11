
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

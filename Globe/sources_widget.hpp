
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

#ifndef GLOBE__SOURCES_WIDGET_HPP__INCLUDED
#define GLOBE__SOURCES_WIDGET_HPP__INCLUDED

// Qt include.
#include <QtGui/QWidget>
#include <QtCore/QScopedPointer>

// Como include.
#include <Como/Source>

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE


namespace Globe {

class SourcesManager;
class ChannelsManager;
class Channel;
class PropertiesManager;


//
// SourcesWidget
//

class SourcesWidgetPrivate;

//! Widget that will display available sources.
class SourcesWidget
	:	public QWidget
{
	Q_OBJECT

signals:
	//! Source was selected.
	void sourceSelected( const Como::Source & );
	//! Channel was selected.
	void channelSelected( const QString & );

public:
	SourcesWidget( SourcesManager * sourcesManager,
		ChannelsManager * channelsManager,
		QWidget * parent = 0, Qt::WindowFlags f = 0 );

	//! \return Name of the current channel.
	QString channelName() const;
	//! Set channel name.
	void setChannelName( const QString & channelName );

	//! Set properties manager.
	void setPropertiesManager( PropertiesManager * propertiesManager );

private:
	//! Init.
	void init();

private slots:
	//! New source.
	void newSource( const Como::Source & source, const QString & channelName );
	//! Channel created.
	void channelCreated( Channel * channel );
	//! Channel removed.
	void channelRemoved( Channel * channel );
	//! Channel selected.
	void selectChannel( const QString & channelName );
	//! Item activated.
	void itemActivated( const QModelIndex & index );

private:
	Q_DISABLE_COPY( SourcesWidget )

	QScopedPointer< SourcesWidgetPrivate > d;
}; // class SourcesWidget

} /* namespace Globe */

#endif // GLOBE__SOURCES_WIDGET_HPP__INCLUDED

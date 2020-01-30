
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

#ifndef GLOBE__SOURCES_WIDGET_HPP__INCLUDED
#define GLOBE__SOURCES_WIDGET_HPP__INCLUDED

// Qt include.
#include <QWidget>
#include <QScopedPointer>

// Como include.
#include <Como/Source>

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE


namespace Globe {

class Channel;


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
	SourcesWidget( QWidget * parent = 0, Qt::WindowFlags f = 0 );
	~SourcesWidget();

	//! \return Name of the current channel.
	QString channelName() const;
	//! Set channel name.
	void setChannelName( const QString & channelName );

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

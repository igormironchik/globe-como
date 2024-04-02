
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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
	SourcesWidget( QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );
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
	void channelCreated( Globe::Channel * channel );
	//! Channel removed.
	void channelRemoved( Globe::Channel * channel );
	//! Channel selected.
	void selectChannel( int index );
	//! Item activated.
	void itemActivated( const QModelIndex & index );

private:
	Q_DISABLE_COPY( SourcesWidget )

	QScopedPointer< SourcesWidgetPrivate > d;
}; // class SourcesWidget

} /* namespace Globe */

#endif // GLOBE__SOURCES_WIDGET_HPP__INCLUDED

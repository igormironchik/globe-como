
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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

#ifndef GLOBE__LOG_SOURCES_SELECTOR_HPP__INCLUDED
#define GLOBE__LOG_SOURCES_SELECTOR_HPP__INCLUDED

// Qt include.
#include <QWidget>
#include <QScopedPointer>
#include <QDateTime>

// Como include.
#include <Como/Source>


namespace Globe {

class SelectQueryNavigation;
class Channel;


//
// LogSourcesSelector
//

class LogSourcesSelectorPrivate;

//! Selector for the event log.
class LogSourcesSelector
	:	public QWidget
{
	Q_OBJECT

public:
	LogSourcesSelector( QWidget * parent = 0, Qt::WindowFlags f = 0 );

	~LogSourcesSelector();

	//! \return Navigation widget.
	SelectQueryNavigation * navigationWidget();

	//! \return Date and time for begin selection from log.
	QDateTime startDateTime() const;

	//! \return Date and time for end slection from log.
	QDateTime endDateTime() const;

	//! \return Channel name.
	QString channelName() const;

	//! \return Type name.
	QString typeName() const;

	//! \return Source name.
	QString sourceName() const;

private slots:
	//! Set start time to the launching app time.
	void setStartTimeToLaunchTime();
	//! Set end time to the current time.
	void setEndTimeToCurrent();
	//! Channel name changed.
	void channelNameChanged( const QString & text );
	//! New channel.
	void chanelCreated( Channel * ch );
	//! Channel removed.
	void channelRemoved( Channel * ch );
	//! New sources available.
	void newSource( const Como::Source & source, const QString & channelName );
	//! Type changed.
	void typeChanged( const QString & text );

private:
	//! Init.
	void init();
	//! Clear types.
	void clearTypes();
	//! Clear names.
	void clearNames();

private:
	Q_DISABLE_COPY( LogSourcesSelector )

	QScopedPointer< LogSourcesSelectorPrivate > d;
}; // class LogSourcesSelector

} /* namespace Globe */

#endif // GLOBE__LOG_SOURCES_SELECTOR_HPP__INCLUDED

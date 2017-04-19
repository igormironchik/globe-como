
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

#ifndef GLOBE__LOG_EVENT_SELECTOR_HPP__INCLUDED
#define GLOBE__LOG_EVENT_SELECTOR_HPP__INCLUDED

// Qt include.
#include <QWidget>
#include <QScopedPointer>
#include <QDateTime>


namespace Globe {

class SelectQueryNavigation;


//
// LogEventSelectorCfg
//

//! Configuration of the event's log selector.
class LogEventSelectorCfg {
public:
	LogEventSelectorCfg();

	//! \return Start date and time.
	const QDateTime & startDateTime() const;
	//! Set start date and time.
	void setStartDateTime( const QDateTime & dt );

	//! \return End date and time.
	const QDateTime & endDateTime() const;
	//! Set end date and time.
	void setEndDateTime( const QDateTime & dt );

private:
	//! Start date and time.
	QDateTime m_startDateTime;
	//! End date and time.
	QDateTime m_endDateTime;
}; // class LogEventSelectorCfg


//
// LogEventSelector
//

class LogEventSelectorPrivate;

//! Selector for the event log.
class LogEventSelector
	:	public QWidget
{
	Q_OBJECT

public:
	LogEventSelector( QWidget * parent = 0, Qt::WindowFlags f = 0 );

	~LogEventSelector();

	//! \return Configuration.
	const LogEventSelectorCfg & cfg() const;

	//! \return Navigation widget.
	SelectQueryNavigation * navigationWidget();

	//! \return Date and time for begin selection from log.
	QDateTime startDateTime() const;

	//! \return Date and time for end slection from log.
	QDateTime endDateTime() const;

private slots:
	//! Start date and time changed.
	void startDateTimeChanged( const QDateTime & dt );
	//! End date and time changed.
	void endDateTimeChanged( const QDateTime & dt );
	//! Set start time to the launching app time.
	void setStartTimeToLaunchTime();
	//! Set end time to the current time.
	void setEndTimeToCurrent();

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( LogEventSelector )

	QScopedPointer< LogEventSelectorPrivate > d;
}; // class LogEventSelector

} /* namespace Globe */

#endif // GLOBE__LOG_EVENT_SELECTOR_HPP__INCLUDED

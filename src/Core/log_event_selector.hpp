
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__LOG_EVENT_SELECTOR_HPP__INCLUDED
#define GLOBE__LOG_EVENT_SELECTOR_HPP__INCLUDED

// Qt include.
#include <QWidget>
#include <QScopedPointer>
#include <QDateTime>

// Globe include.
#include <Core/export.hpp>


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
class CORE_EXPORT LogEventSelector
	:	public QWidget
{
	Q_OBJECT

public:
	LogEventSelector( QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );

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

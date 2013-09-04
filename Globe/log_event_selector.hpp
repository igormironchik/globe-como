
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

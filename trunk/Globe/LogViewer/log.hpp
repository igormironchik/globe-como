
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2014 Igor Mironchik

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

#ifndef LOGVIEWER__LOG_HPP__INCLUDED
#define LOGVIEWER__LOG_HPP__INCLUDED

// Qt include.
#include <QObject>
#include <QScopedPointer>
#include <QSqlQuery>


QT_BEGIN_NAMESPACE
class QDateTime;
QT_END_NAMESPACE


namespace LogViewer {

//
// Log
//

class LogPrivate;

//! Log.
class Log
	:	public QObject
{
	Q_OBJECT

signals:
	//! Emits when error occured.
	void error();
	//! Emits when log is ready.
	void ready();

public:
	//! \return Instance of the log.
	static Log & instance();

	//! \return Date & time as string.
	QString dateTimeToString( const QDateTime & dt );

	//! Read all records from the event's log.
	QSqlQuery readAllEventLog();
	//! Read event's log for the given period of time.
	QSqlQuery readEventLog( const QDateTime & from,
		const QDateTime & to );

	//! Initialize.
	void init();

private:
	Log( QObject * parent = 0 );

	~Log();

private:
	Q_DISABLE_COPY( Log )

	QScopedPointer< LogPrivate > d;
}; // class Log

} /* namespace LogViewer */

#endif // LOGVIEWER__LOG_HPP__INCLUDED

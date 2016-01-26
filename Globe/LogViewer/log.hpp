
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2014 - 2016 Igor Mironchik

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

	static void cleanup();

private:
	Q_DISABLE_COPY( Log )

	QScopedPointer< LogPrivate > d;
}; // class Log

} /* namespace LogViewer */

#endif // LOGVIEWER__LOG_HPP__INCLUDED

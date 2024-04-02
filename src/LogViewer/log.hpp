
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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

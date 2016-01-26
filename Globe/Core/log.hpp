
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

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

#ifndef GLOBE__LOG_HPP__INCLUDED
#define GLOBE__LOG_HPP__INCLUDED

// Qt include.
#include <QObject>
#include <QScopedPointer>
#include <QSqlQuery>

// Como include.
#include <Como/Source>


QT_BEGIN_NAMESPACE
class QDateTime;
class QString;
class QVariant;
QT_END_NAMESPACE


namespace Globe {

class DB;
class MainWindow;
class LogCfg;

//
// LogLevel
//

//! Level of the log.
enum LogLevel {
	//! Info.
	LogLevelInfo = 0,
	//! Warning.
	LogLevelWarning = 1,
	//! Error.
	LogLevelError = 2
}; // enum LogLevel


//
// Log
//

class LogPrivate;

//! Log.
class Log
	:	public QObject
{
	Q_OBJECT

public:
	//! \return Instance of the log.
	static Log & instance();

	//! Write message to the event's log.
	void writeMsgToEventLog( LogLevel level, const QDateTime & dateTime,
		const QString & msg );
	//! Write message to the event's log.
	void writeMsgToEventLog( LogLevel level, const QString & msg );
	//! Write message to the source's log.
	void writeMsgToSourcesLog( const QDateTime & dateTime,
		const QString & channelName,
		Como::Source::Type type,
		const QString & sourceName,
		const QString & typeName,
		const QVariant & value,
		const QString & desc );

	//! Read all records from the event's log.
	QSqlQuery readAllEventLog();
	//! Read event's log for the given period of time.
	QSqlQuery readEventLog( const QDateTime & from,
		const QDateTime & to );
	//! Read event's log from the beginning to the given time.
	QSqlQuery readEventLogTo( const QDateTime & to );
	//! Read event's log from the given time to the end.
	QSqlQuery readEventLogFrom( const QDateTime & from );
	//! Read source's log for the given period of time.
	QSqlQuery readSourcesLog( const QDateTime & from,
		const QDateTime & to,
		const QString & channelName = QString(),
		const QString & sourceName = QString(),
		const QString & typeName = QString() );
	//! Read source's log from the beginning to the given time.
	QSqlQuery readSourcesLogTo( const QDateTime & to,
		const QString & channelName = QString(),
		const QString & sourceName = QString(),
		const QString & typeName = QString() );
	//! Read source's log from the given time to the end.
	QSqlQuery readSourcesLogFrom( const QDateTime & from,
		const QString & channelName = QString(),
		const QString & sourceName = QString(),
		const QString & typeName = QString() );
	//! Read all records from the source's log.
	QSqlQuery readAllSourcesLog( const QString & channelName = QString(),
		const QString & sourceName = QString(),
		const QString & typeName = QString() );

	//! \return Configuration of the log.
	const LogCfg & cfg() const;

	//! Read configuration.
	void readCfg( const QString & fileName );
	//! Save configuration.
	void saveCfg( const QString & fileName );

	//! Init log with default configuration.
	void initWithDefaultCfg();

	//! Enable/disable event's log.
	void enableEventsLog( bool on = true );
	//! Enable/disable source's log.
	void enableSourcesLog( bool on = true );
	//! Set sources' log days.
	void setSourcesLogDays( int days );

	//! Clear all records from event's log.
	void clearEventsLog();
	//! Clear all records from source's log.
	void clearSourcesLog();

private:
	Log( QObject * parent = 0 );

	~Log();

	static void cleanup();

	//! Initialize.
	void init();
	//! Private initialization.
	void privateInit();

	//! Insert record into event's log.
	void insertMsgIntoEventLog( LogLevel level, const QDateTime & dateTime,
		const QString & msg );

private slots:
	//! DB is ready.
	void dbReady();
	//! Error in DB.
	void dbError();
	//! Erase outdated recrods from source's log.
	void eraseSourcesLog();

private:
	Q_DISABLE_COPY( Log )

	QScopedPointer< LogPrivate > d;
};

} /* namespace Globe */

#endif // GLOBE__LOG_HPP__INCLUDED


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

	//! Initialize.
	void init();
	//! Private initialization.
	void privateInit();

	//! Insert record into event's log.
	void insertMsgIntoEventLog( LogLevel level, const QDateTime & dateTime,
		const QString & msg );
	//! Convert QDateTime into string.
	QString dateTimeToString( const QDateTime & dt );

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

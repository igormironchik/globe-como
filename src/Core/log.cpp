
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2020 Igor Mironchik

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

// Qt include.
#include <QDateTime>
#include <QString>
#include <QVariant>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVector>
#include <QTimer>
#include <QCoreApplication>
#include <QFile>
#include <QTextCodec>

// Globe include.
#include <Core/log.hpp>
#include <Core/db.hpp>
#include <Core/log_cfg.hpp>

// cfgfile include.
#include <cfgfile/all.hpp>


namespace Globe {

//
// DBState
//

//! State of the DB.
enum DBState {
	//! Unknown state.
	UnknownDBState = 0,
	//! All is ok in the DB.
	AllIsOkDBState = 1,
	//! Error in the DB.
	ErrorInDBState = 2
}; // enum DBSTate


//
// LogState
//

//! SState of the log.
enum LogState {
	//! Uninitialized.
	UninitializedLogState = 0,
	//! Configuration loaded.
	ConfigurationLoadedLogState = 1,
	//! Log is ready.
	ReadyLogState = 2,
	//! Error in log.
	ErrorLogState = 3
}; // enum LogState


//
// EventLogRecord
//

//! Event's log record.
struct EventLogRecord {
public:
	EventLogRecord()
		:	m_level( LogLevelError )
	{
	}

	EventLogRecord( LogLevel l,
		const QDateTime & dt,
		const QString & msg )
		:	m_level( l )
		,	m_dateTime( dt )
		,	m_message( msg )
	{
	}

	EventLogRecord( const EventLogRecord & other )
		:	m_level( other.m_level )
		,	m_dateTime( other.m_dateTime )
		,	m_message( other.m_message )
	{
	}

	EventLogRecord & operator = ( const EventLogRecord & other )
	{
		if( this != & other )
		{
			m_level = other.m_level;
			m_dateTime = other.m_dateTime;
			m_message = other.m_message;
		}

		return *this;
	}

	//! Log level.
	LogLevel m_level;
	//! Date and time.
	QDateTime m_dateTime;
	//! Message.
	QString m_message;
}; // struct EventLogRecord


//
// dateTimeToString
//

static inline QString dateTimeToString( const QDateTime & dt )
{
	return dt.toString( QLatin1String( "yyyy-MM-dd hh:mm:ss.zzz" ) );
}


//
// LogPrivate
//

class LogPrivate {
public:
	LogPrivate()
		:	m_dbState( UnknownDBState )
		,	m_logState( UninitializedLogState )
		,	m_timer( 0 )
	{
	}

	~LogPrivate()
	{
	}

	//! State of the DB.
	DBState m_dbState;
	//! Configuration.
	LogCfg m_cfg;
	//! State of  the log.
	LogState m_logState;
	//! Deferred event's log messages.
	QVector< EventLogRecord > m_deferredEventMessages;
	//! Timer.
	QTimer * m_timer;
}; // class LogPrivate


//
// Log
//

Log::Log( QObject * parent )
	:	QObject( parent )
	,	d( new LogPrivate )
{
	privateInit();
}

Log::~Log()
{
}

void
Log::init()
{
	QSqlQuery eventLogTableQuery( QLatin1String(
		"CREATE TABLE IF NOT EXISTS eventLog ( level INTEGER, dateTime TEXT, "
		"msg TEXT )" ) );

	eventLogTableQuery.exec();

	QSqlQuery eventLogTableDateTimeIndexQuery( QLatin1String(
		"CREATE INDEX IF NOT EXISTS eventLogDateTimeIdx "
		"ON eventLog ( dateTime )" ) );

	eventLogTableDateTimeIndexQuery.exec();

//	QSqlQuery eventLogTableLevelIndexQuery( QLatin1String(
//		"CREATE INDEX IF NOT EXISTS eventLogLevelIdx "
//		"ON eventLog ( level )" ) );

//	eventLogTableLevelIndexQuery.exec();

	QSqlQuery sourcesLogTableQuery( QLatin1String(
		"CREATE TABLE IF NOT EXISTS sourcesLog( dateTime TEXT, "
		"channelName TEXT, type INTEGER, sourceName TEXT, "
		"typeName TEXT, value TEXT, desc TEXT ) " ) );

	sourcesLogTableQuery.exec();

	QSqlQuery dateTimeIndexQuery( QLatin1String(
		"CREATE INDEX IF NOT EXISTS sourcesLogDateTimeIdx "
		"ON sourcesLog( dateTime )" ) );

	dateTimeIndexQuery.exec();

//	QSqlQuery channelNameIndexQuery( QLatin1String(
//		"CREATE INDEX IF NOT EXISTS sourcesLogChannelNameIdx "
//		"ON sourcesLog( channelName )" ) );

//	channelNameIndexQuery.exec();

//	QSqlQuery typeIndexQuery( QLatin1String(
//		"CREATE INDEX IF NOT EXISTS sourcesLogTypeIdx "
//		"ON sourcesLog( type )" ) );

//	typeIndexQuery.exec();

//	QSqlQuery sourceNameIndexQuery( QLatin1String(
//		"CREATE INDEX IF NOT EXISTS sourcesLogSourceNameIdx "
//		"ON sourcesLog( sourceName )" ) );

//	sourceNameIndexQuery.exec();

//	QSqlQuery typeNameIndexQuery( QLatin1String(
//		"CREATE INDEX IF NOT EXISTS sourcesLogTypeNameIdx "
//		"ON sourcesLog( typeName )" ) );

//	typeNameIndexQuery.exec();

	if( d->m_cfg.isEventLogEnabled() )
	{
		for( int i = 0; i < d->m_deferredEventMessages.size(); ++i )
		{
			insertMsgIntoEventLog(
				d->m_deferredEventMessages.at( i ).m_level,
				d->m_deferredEventMessages.at( i ).m_dateTime,
				d->m_deferredEventMessages.at( i ).m_message );
		}
	}

	d->m_deferredEventMessages.clear();

	d->m_logState = ReadyLogState;

	eraseSourcesLog();
}

void
Log::privateInit()
{
	d->m_timer = new QTimer( this );

	connect( d->m_timer, &QTimer::timeout,
		this, &Log::eraseSourcesLog );

	connect( &DB::instance(), &DB::ready,
		this, &Log::dbReady );

	connect( &DB::instance(), &DB::error,
		this, &Log::dbError );
}

static Log * logInstancePointer = 0;

void
Log::cleanup()
{
	delete logInstancePointer;

	logInstancePointer= 0;
}

Log &
Log::instance()
{
	if( !logInstancePointer )
	{
		logInstancePointer = new Log;

		qAddPostRoutine( &Log::cleanup );
	}

	return *logInstancePointer;
}

void
Log::writeMsgToEventLog( LogLevel level, const QDateTime & dateTime,
	const QString & msg )
{
	if( d->m_cfg.isEventLogEnabled() )
	{
		if( d->m_logState != ReadyLogState &&
			d->m_dbState != ErrorInDBState )
		{
			d->m_deferredEventMessages.push_back(
				EventLogRecord( level, dateTime, msg ) );
		}
		else if( d->m_logState == ReadyLogState &&
			d->m_dbState == AllIsOkDBState )
		{
			insertMsgIntoEventLog( level, dateTime, msg );
		}
	}
}

void
Log::writeMsgToEventLog( LogLevel level, const QString & msg )
{
	writeMsgToEventLog( level, QDateTime::currentDateTime(), msg );
}

void
Log::writeMsgToSourcesLog( const QDateTime & dateTime,
	const QString & channelName,
	Como::Source::Type type,
	const QString & sourceName,
	const QString & typeName,
	const QVariant & value,
	const QString & desc )
{
	if( d->m_cfg.isSourcesLogEnabled() )
	{
		if( d->m_logState == ReadyLogState &&
			d->m_dbState == AllIsOkDBState )
		{
			QSqlQuery insert( QLatin1String(
				"INSERT INTO sourcesLog ( dateTime, channelName, type, "
				"sourceName, typeName, value, desc ) "
				"VALUES ( ?, ?, ?, ?, ?, ?, ? )" ) );

			insert.addBindValue( dateTimeToString( dateTime ) );
			insert.addBindValue( channelName );
			insert.addBindValue( (int) type );
			insert.addBindValue( sourceName );
			insert.addBindValue( typeName );
			insert.addBindValue( value.toString() );
			insert.addBindValue( desc );

			insert.exec();
		}
	}
}

QSqlQuery
Log::readAllEventLog()
{
	QSqlQuery select( QLatin1String(
		"SELECT * FROM eventLog ORDER BY dateTime" ) );

	if( d->m_dbState == AllIsOkDBState )
		select.exec();

	return select;
}

QSqlQuery
Log::readEventLog( const QDateTime & from,
	const QDateTime & to )
{
	QSqlQuery select( QLatin1String(
		"SELECT * FROM eventLog WHERE dateTime BETWEEN "
		"? AND ? ORDER BY dateTime" ) );

	if( d->m_dbState == AllIsOkDBState )
	{
		select.addBindValue( dateTimeToString( from ) );
		select.addBindValue( dateTimeToString( to ) );

		select.exec();
	}

	return select;
}

QSqlQuery
Log::readEventLogTo( const QDateTime & to )
{
	QSqlQuery select( QLatin1String(
		"SELECT * FROM eventLog WHERE dateTime <= ? "
		"ORDER BY dateTime" ) );

	if( d->m_dbState == AllIsOkDBState )
	{
		select.addBindValue( dateTimeToString( to ) );

		select.exec();
	}

	return select;
}

QSqlQuery
Log::readEventLogFrom( const QDateTime & from )
{
	QSqlQuery select( QLatin1String(
		"SELECT * FROM eventLog WHERE dateTime >= ? "
		"ORDER BY dateTime" ) );

	if( d->m_dbState == AllIsOkDBState )
	{
		select.addBindValue( dateTimeToString( from ) );

		select.exec();
	}

	return select;
}

QSqlQuery
Log::readSourcesLog( const QDateTime & from,
	const QDateTime & to,
	const QString & channelName,
	const QString & sourceName,
	const QString & typeName )
{
	if( d->m_dbState == AllIsOkDBState )
	{
		if( !channelName.isEmpty() && !sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime BETWEEN "
				"? AND ? AND channelName = ? AND sourceName = ? "
				"AND typeName = ? ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( from ) );
			select.addBindValue( dateTimeToString( to ) );
			select.addBindValue( channelName );
			select.addBindValue( sourceName );
			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( channelName.isEmpty() && !sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime BETWEEN "
				"? AND ? AND sourceName = ? AND typeName = ? "
				"ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( from ) );
			select.addBindValue( dateTimeToString( to ) );
			select.addBindValue( sourceName );
			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( !channelName.isEmpty() && sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime BETWEEN "
				"? AND ? AND channelName = ? AND typeName = ? "
				"ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( from ) );
			select.addBindValue( dateTimeToString( to ) );
			select.addBindValue( channelName );
			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( !channelName.isEmpty() && !sourceName.isEmpty()
			&& typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime BETWEEN "
				"? AND ? AND channelName = ? AND sourceName = ? "
				"ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( from ) );
			select.addBindValue( dateTimeToString( to ) );
			select.addBindValue( channelName );
			select.addBindValue( sourceName );

			select.exec();

			return select;
		}
		else if( channelName.isEmpty() && sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime BETWEEN "
				"? AND ? AND typeName = ? ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( from ) );
			select.addBindValue( dateTimeToString( to ) );
			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( !channelName.isEmpty() && sourceName.isEmpty()
			&& typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime BETWEEN "
				"? AND ? AND channelName = ? ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( from ) );
			select.addBindValue( dateTimeToString( to ) );
			select.addBindValue( channelName );

			select.exec();

			return select;
		}
		else if( channelName.isEmpty() && !sourceName.isEmpty()
			&& typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime BETWEEN "
				"? AND ? AND sourceName = ? ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( from ) );
			select.addBindValue( dateTimeToString( to ) );
			select.addBindValue( sourceName );

			select.exec();

			return select;
		}
		else
			return QSqlQuery();
	}
	else
		return QSqlQuery();
}

QSqlQuery
Log::readSourcesLogTo( const QDateTime & to,
	const QString & channelName,
	const QString & sourceName,
	const QString & typeName )
{
	if( d->m_dbState == AllIsOkDBState )
	{
		if( !channelName.isEmpty() && !sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime <= ? "
				"AND channelName = ? AND sourceName = ? "
				"AND typeName = ? ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( to ) );
			select.addBindValue( channelName );
			select.addBindValue( sourceName );
			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( channelName.isEmpty() && !sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime <= ? "
				"AND sourceName = ? AND typeName = ? "
				"ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( to ) );
			select.addBindValue( sourceName );
			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( !channelName.isEmpty() && sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime <= ? "
				"AND channelName = ? AND typeName = ? "
				"ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( to ) );
			select.addBindValue( channelName );
			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( !channelName.isEmpty() && !sourceName.isEmpty()
			&& typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime <= ? "
				"AND channelName = ? AND sourceName = ? "
				"ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( to ) );
			select.addBindValue( channelName );
			select.addBindValue( sourceName );

			select.exec();

			return select;
		}
		else if( channelName.isEmpty() && sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime <= ? "
				"AND typeName = ? ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( to ) );
			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( !channelName.isEmpty() && sourceName.isEmpty()
			&& typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime <= ? "
				"AND channelName = ? ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( to ) );
			select.addBindValue( channelName );

			select.exec();

			return select;
		}
		else if( channelName.isEmpty() && !sourceName.isEmpty()
			&& typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime <= ? "
				"AND sourceName = ? ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( to ) );
			select.addBindValue( sourceName );

			select.exec();

			return select;
		}
		else
			return QSqlQuery();
	}
	else
		return QSqlQuery();
}

QSqlQuery
Log::readSourcesLogFrom( const QDateTime & from,
	const QString & channelName,
	const QString & sourceName,
	const QString & typeName )
{
	if( d->m_dbState == AllIsOkDBState )
	{
		if( !channelName.isEmpty() && !sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime >= ? "
				"AND channelName = ? AND sourceName = ? "
				"AND typeName = ? ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( from ) );
			select.addBindValue( channelName );
			select.addBindValue( sourceName );
			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( channelName.isEmpty() && !sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime >= ? "
				"AND sourceName = ? AND typeName = ? "
				"ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( from ) );
			select.addBindValue( sourceName );
			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( !channelName.isEmpty() && sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime >= ? "
				"AND channelName = ? AND typeName = ? "
				"ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( from ) );
			select.addBindValue( channelName );
			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( !channelName.isEmpty() && !sourceName.isEmpty()
			&& typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime >= ? "
				"AND channelName = ? AND sourceName = ? "
				"ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( from ) );
			select.addBindValue( channelName );
			select.addBindValue( sourceName );

			select.exec();

			return select;
		}
		else if( channelName.isEmpty() && sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime >= ? "
				"AND typeName = ? ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( from ) );
			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( !channelName.isEmpty() && sourceName.isEmpty()
			&& typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime >= ? "
				"AND channelName = ? ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( from ) );
			select.addBindValue( channelName );

			select.exec();

			return select;
		}
		else if( channelName.isEmpty() && !sourceName.isEmpty()
			&& typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE dateTime >= ? "
				"AND sourceName = ? ORDER BY dateTime" ) );

			select.addBindValue( dateTimeToString( from ) );
			select.addBindValue( sourceName );

			select.exec();

			return select;
		}
		else
			return QSqlQuery();
	}
	else
		return QSqlQuery();
}

QSqlQuery
Log::readAllSourcesLog( const QString & channelName,
	const QString & sourceName,
	const QString & typeName )
{
	if( d->m_dbState == AllIsOkDBState )
	{
		if( !channelName.isEmpty() && !sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE channelName = ? "
				"AND sourceName = ? AND typeName = ? "
				"ORDER BY dateTime" ) );

			select.addBindValue( channelName );
			select.addBindValue( sourceName );
			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( channelName.isEmpty() && !sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE "
				"AND sourceName = ? AND typeName = ? "
				"ORDER BY dateTime" ) );

			select.addBindValue( sourceName );
			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( !channelName.isEmpty() && sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE channelName = ? "
				"AND typeName = ? ORDER BY dateTime" ) );

			select.addBindValue( channelName );
			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( !channelName.isEmpty() && !sourceName.isEmpty()
			&& typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE channelName = ? "
				"AND sourceName = ? ORDER BY dateTime" ) );

			select.addBindValue( channelName );
			select.addBindValue( sourceName );

			select.exec();

			return select;
		}
		else if( channelName.isEmpty() && sourceName.isEmpty()
			&& !typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE "
				"AND typeName = ? ORDER BY dateTime" ) );

			select.addBindValue( typeName );

			select.exec();

			return select;
		}
		else if( !channelName.isEmpty() && sourceName.isEmpty()
			&& typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE channelName = ? "
				"ORDER BY dateTime" ) );

			select.addBindValue( channelName );

			select.exec();

			return select;
		}
		else if( channelName.isEmpty() && !sourceName.isEmpty()
			&& typeName.isEmpty() )
		{
			QSqlQuery select( QLatin1String(
				"SELECT * FROM sourcesLog WHERE "
				"AND sourceName = ? ORDER BY dateTime" ) );

			select.addBindValue( sourceName );

			select.exec();

			return select;
		}
		else
			return QSqlQuery();
	}
	else
		return QSqlQuery();
}

const LogCfg &
Log::cfg() const
{
	return d->m_cfg;
}

void
Log::initWithDefaultCfg()
{
	d->m_logState = ConfigurationLoadedLogState;

	if( d->m_dbState == AllIsOkDBState )
		init();
}

void
Log::readCfg( const QString & fileName )
{
	LogTag tag;

	QFile file( fileName );

	if( file.open( QIODevice::ReadOnly ) )
	{
		try {
			QTextStream stream( &file );
			stream.setCodec( QTextCodec::codecForName( "UTF-8" ) );

			cfgfile::read_cfgfile( tag, stream, fileName );

			file.close();

			writeMsgToEventLog( LogLevelInfo, QString(
				"Log configuration read from file \"%1\"." )
					.arg( fileName ) );
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			writeMsgToEventLog( LogLevelError, QString(
				"Unable to read log configuration from file \"%1\".\n"
				"%2" )
					.arg( fileName, x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to read log configuration..." ),
				tr( "Unable to read log configuration...\n\n%1" )
					.arg( x.desc() ) );

			d->m_logState = ErrorLogState;

			return;
		}
	}
	else
	{
		writeMsgToEventLog( LogLevelError, QString(
			"Unable to read log configuration from file \"%1\".\n"
			"Unable to open file." )
				.arg( fileName ) );

		QMessageBox::critical( 0,
			tr( "Unable to read log configuration..." ),
			tr( "Unable to read log configuration...\n\n"
				"Unable to open file." ) );

		d->m_logState = ErrorLogState;

		return;
	}

	d->m_cfg = tag.cfg();

	d->m_logState = ConfigurationLoadedLogState;

	if( d->m_dbState == AllIsOkDBState )
		init();
}

void
Log::saveCfg( const QString & fileName )
{
	QFile file( fileName );

	if( file.open( QIODevice::WriteOnly ) )
	{
		try {
			LogTag tag( d->m_cfg );

			QTextStream stream( &file );
			stream.setCodec( QTextCodec::codecForName( "UTF-8" ) );

			cfgfile::write_cfgfile( tag, stream );

			file.close();

			writeMsgToEventLog( LogLevelInfo, QString(
				"Log configuration saved to file \"%1\"." )
					.arg( fileName ) );
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			writeMsgToEventLog( LogLevelError, QString(
				"Unable to save log configuration to file \"%1\".\n"
				"%2" )
					.arg( fileName, x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to save log configuration..." ),
				tr( "Unable to save log configuration...\n\n%1" )
					.arg( x.desc() ) );
		}
	}
	else
	{
		writeMsgToEventLog( LogLevelError, QString(
			"Unable to save log configuration to file \"%1\".\n"
			"Unable to open file." )
				.arg( fileName ) );

		QMessageBox::critical( 0,
			tr( "Unable to save log configuration..." ),
			tr( "Unable to save log configuration...\n\n"
				"Unable to open file." ) );
	}
}

void
Log::enableEventsLog( bool on )
{
	d->m_cfg.setEventLogEnabled( on );
}

void
Log::enableSourcesLog( bool on )
{
	d->m_cfg.setSourcesLogEnabled( on );
}

void
Log::setSourcesLogDays( int days )
{
	d->m_cfg.setSourcesLogDays( days );
}

void
Log::clearEventsLog()
{
	if( d->m_dbState == AllIsOkDBState )
	{
		QSqlQuery deleteQuery( QLatin1String(
			"DELETE FROM eventLog" ) )	;

		deleteQuery.exec();
	}
}

void
Log::clearSourcesLog()
{
	if( d->m_dbState == AllIsOkDBState )
	{
		QSqlQuery deleteQuery( QLatin1String(
			"DELETE FROM sourcesLog" ) )	;

		deleteQuery.exec();
	}
}

void
Log::eraseSourcesLog()
{
	static const int msecsInDay = 24 * 60 * 60 * 1000;

	d->m_timer->stop();

	QDateTime from = QDateTime::currentDateTime();

	if( d->m_cfg.sourcesLogDays() > 0 )
		from = from.addDays( -d->m_cfg.sourcesLogDays() );

	QSqlQuery eraseQuery( QLatin1String(
		"DELETE FROM sourcesLog WHERE dateTime < ?" ) );

	eraseQuery.addBindValue( dateTimeToString( from ) );

	eraseQuery.exec();

	d->m_timer->start( msecsInDay );
}

void
Log::insertMsgIntoEventLog( LogLevel level, const QDateTime & dateTime,
	const QString & msg )
{
	QSqlQuery insert( QLatin1String(
		"INSERT INTO eventLog ( level, dateTime, msg ) "
		"VALUES ( ?, ?, ? )" ) );

	insert.addBindValue( (int) level );
	insert.addBindValue( dateTimeToString( dateTime ) );
	insert.addBindValue( msg );

	insert.exec();
}

void
Log::dbReady()
{
	d->m_dbState = AllIsOkDBState;

	if( d->m_logState == ConfigurationLoadedLogState )
		init();
}

void
Log::dbError()
{
	d->m_dbState = ErrorInDBState;
}

} /* namespace Globe */

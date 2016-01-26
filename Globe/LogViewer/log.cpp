
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

// Qt include.
#include <QDateTime>
#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QVariant>
#include <QCoreApplication>

// LogViewer include.
#include <LogViewer/log.hpp>
#include <LogViewer/configuration.hpp>


namespace LogViewer {


//
// LogPrivate
//

class LogPrivate {
public:
	LogPrivate()
	{
	}

	~LogPrivate()
	{
	}

	//! Connection.
	QSqlDatabase m_connection;
}; // class LogPrivate


//
// Log
//

Log::Log( QObject * parent )
	:	QObject( parent )
	,	d( new LogPrivate )
{
	init();
}

Log::~Log()
{
}

void
Log::init()
{
	d->m_connection.close();

	QFileInfo info( Configuration::instance().dbFileName() );

	if( !info.exists() )
	{
		emit error();

		return;
	}

	d->m_connection = QSqlDatabase::addDatabase( "QSQLITE" );
	d->m_connection.setDatabaseName( Configuration::instance().dbFileName() );

	if( !d->m_connection.open() )
	{
		d->m_connection.close();

		emit error();
	}
	else
		emit ready();
}

static Log * logInstancePointer = 0;

void
Log::cleanup()
{
	delete logInstancePointer;

	logInstancePointer = 0;
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

QString
Log::dateTimeToString( const QDateTime & dt )
{
	return dt.toString( QLatin1String( "yyyy-MM-dd hh:mm:ss.zzz" ) );
}

QSqlQuery
Log::readAllEventLog()
{
	QSqlQuery select( QLatin1String(
		"SELECT * FROM eventLog ORDER BY dateTime" ) );

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

	select.addBindValue( dateTimeToString( from ) );
	select.addBindValue( dateTimeToString( to ) );

	select.exec();

	return select;
}

} /* namespace LogViewer */


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

// Qt include.
#include <QDateTime>
#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QVariant>

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

Log &
Log::instance()
{
	static Log log;

	return log;
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

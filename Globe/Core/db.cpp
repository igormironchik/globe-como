
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

// Globe include.
#include <Globe/Core/db.hpp>
#include <Globe/Core/db_cfg.hpp>
#include <Globe/Core/utils.hpp>
#include <Globe/Core/log.hpp>

// QtConfFile include.
#include <QtConfFile/Utils>

// Qt include.
#include <QMessageBox>
#include <QFileInfo>
#include <QCoreApplication>


namespace Globe {

static const QString defaultDbFile =
	QLatin1String( "./etc/db/globe.db" );


//
// DBPrivate
//

class DBPrivate {
public:
	DBPrivate()
		:	m_isReady( false )
	{
	}

	//! Is DB ready?
	bool m_isReady;
	//! Connection.
	QSqlDatabase m_connection;
	//! File name of the DB file.
	QString m_dbFileName;
}; // class DBPrivate


//
// DB
//

DB::DB( QObject * parent )
	:	QObject( parent )
	,	d( new DBPrivate )
{
}

DB::~DB()
{
	d->m_connection.close();
}

static DB * dbInstancePointer = 0;

void
DB::cleanup()
{
	delete dbInstancePointer;

	dbInstancePointer = 0;
}

DB &
DB::instance()
{
	if( !dbInstancePointer )
	{
		dbInstancePointer = new DB;

		qAddPostRoutine( &DB::cleanup );
	}

	return *dbInstancePointer;
}

bool
DB::isReady() const
{
	return d->m_isReady;
}

const QSqlDatabase &
DB::connection() const
{
	return d->m_connection;
}

void
DB::setCfg( const DBCfg & cfg )
{
	if( !cfg.dbFileName().isEmpty() )
		init( cfg.dbFileName() );
	else
		init( defaultDbFile );
}

void
DB::readCfg( const QString & fileName )
{
	DBTag tag;

	try {
		QtConfFile::readQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo,
			QString( "Database configuration loaded from file \"%1\"." )
				.arg( fileName ) );

		setCfg( tag.cfg() );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError,
			QString( "Unable to read database configuration "
				"from file \"%1\".\n"
				"%2" )
					.arg( fileName )
					.arg( x.whatAsQString() ) );

		QMessageBox::critical( 0,
			tr( "Unable to read DB configuration..." ),
			tr( "Unable to read DB configuration...\n\n"
				"%1\n\n"
				"Default database will be used: \"%2\"." )
					.arg( x.whatAsQString() )
					.arg( defaultDbFile )
		);

		DBCfg cfg;

		cfg.setDbFileName( defaultDbFile );

		setCfg( cfg );
	}
}

void
DB::saveCfg( const QString & fileName )
{
	try {
		DBCfg cfg;
		cfg.setDbFileName( d->m_dbFileName );

		DBTag tag( cfg );

		QtConfFile::writeQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo,
			QString( "Database configuration saved into file \"%1\"." )
				.arg( fileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError,
			QString( "Unable to save database configuration to file "
				"\"%1\".\n"
				"%2" )
					.arg( fileName )
					.arg( x.whatAsQString() ) );

		QMessageBox::critical( 0,
			tr( "Unable to save DB configuration..." ),
			tr( "Unable to save DB configuration...\n\n%1" )
				.arg( x.whatAsQString() ) );
	}
}

void
DB::init( const QString & dbFileName )
{
	d->m_isReady = false;
	d->m_connection.close();

	d->m_dbFileName = dbFileName;

	QFileInfo info( d->m_dbFileName );

	checkPathAndCreateIfNotExists( info.path() );

	d->m_connection = QSqlDatabase::addDatabase( "QSQLITE" );
	d->m_connection.setDatabaseName( d->m_dbFileName );

	if( !d->m_connection.open() )
	{
		d->m_connection.close();

		Log::instance().writeMsgToEventLog( LogLevelError,
			QString( "Unable to initialize databse in file \"%1\"." )
				.arg( dbFileName ) );

		emit error();
	}
	else
	{
		d->m_isReady = true;

		Log::instance().writeMsgToEventLog( LogLevelInfo,
			QString( "Database successfully initialized in file \"%1\"." )
				.arg( dbFileName ) );

		emit ready();
	}
}

} /* namespace Globe */

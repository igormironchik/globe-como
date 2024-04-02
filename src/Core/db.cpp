
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/db.hpp>
#include <Core/db_cfg.hpp>
#include <Core/utils.hpp>
#include <Core/log.hpp>
#include <Core/configuration.hpp>

// cfgfile include.
#include <cfgfile/all.hpp>

// Qt include.
#include <QMessageBox>
#include <QFileInfo>
#include <QCoreApplication>


namespace Globe {

static const QString defaultDbFile =
	QLatin1String( "db/globe.db" );


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

	QFile file( fileName );

	if( file.open( QIODevice::ReadOnly ) )
	{
		try {
			QTextStream stream( &file );

			cfgfile::read_cfgfile( tag, stream, fileName );

			file.close();

			Log::instance().writeMsgToEventLog( LogLevelInfo,
				QString( "Database configuration loaded from file \"%1\"." )
					.arg( fileName ) );

			setCfg( tag.cfg() );
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			Log::instance().writeMsgToEventLog( LogLevelError,
				QString( "Unable to read database configuration "
					"from file \"%1\".\n"
					"%2" )
						.arg( fileName, x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to read DB configuration..." ),
				tr( "%1\n\nDefault database will be used: \"%2\"." )
					.arg( x.desc(), Configuration::instance().path() + defaultDbFile )
			);

			DBCfg cfg;

			cfg.setDbFileName( defaultDbFile );

			setCfg( cfg );
		}
	}
	else
	{
		Log::instance().writeMsgToEventLog( LogLevelError,
			QString( "Unable to read database configuration "
				"from file \"%1\".\n"
				"Unable to open file." )
					.arg( fileName ) );

		QMessageBox::critical( 0,
			tr( "Unable to read DB configuration..." ),
			tr( "Unable to open file \"%1\".\n\n"
				"Default database will be used: \"%2\"." )
					.arg( fileName, Configuration::instance().path() + defaultDbFile )
		);

		DBCfg cfg;

		cfg.setDbFileName( defaultDbFile );

		setCfg( cfg );
	}
}

void
DB::saveCfg( const QString & fileName )
{
	QFile file( fileName );

	if( file.open( QIODevice::WriteOnly ) )
	{
		try {
			DBCfg cfg;
			cfg.setDbFileName( d->m_dbFileName );

			DBTag tag( cfg );

			QTextStream stream( &file );

			cfgfile::write_cfgfile( tag, stream );

			file.close();

			Log::instance().writeMsgToEventLog( LogLevelInfo,
				QString( "Database configuration saved into file \"%1\"." )
					.arg( fileName ) );
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			Log::instance().writeMsgToEventLog( LogLevelError,
				QString( "Unable to save database configuration to file "
					"\"%1\".\n"
					"%2" )
						.arg( fileName, x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to save DB configuration..." ),
				x.desc() );
		}
	}
	else
	{
		Log::instance().writeMsgToEventLog( LogLevelError,
			QString( "Unable to save database configuration to file "
				"\"%1\".\n"
				"Unable to open file." )
					.arg( fileName ) );

		QMessageBox::critical( 0,
			tr( "Unable to save DB configuration..." ),
			tr( "Unable to open file \"%1\"." ).arg( fileName ) );
	}
}

void
DB::init( const QString & dbFileName )
{
	d->m_isReady = false;
	d->m_connection.close();

	d->m_dbFileName = dbFileName;

	QFileInfo info( Configuration::instance().path() + d->m_dbFileName );

	checkPathAndCreateIfNotExists( info.path() );

	d->m_connection = QSqlDatabase::addDatabase( "QSQLITE" );
	d->m_connection.setDatabaseName( Configuration::instance().path() + d->m_dbFileName );

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

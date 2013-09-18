
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

// Globe include.
#include <Globe/db.hpp>
#include <Globe/mainwindow.hpp>
#include <Globe/db_cfg.hpp>
#include <Globe/utils.hpp>
#include <Globe/log.hpp>

// QtConfFile include.
#include <QtConfFile/Utils>

// Qt include.
#include <QMessageBox>
#include <QFileInfo>


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
		,	m_mainWindow( 0 )
	{
	}

	//! Is DB ready?
	bool m_isReady;
	//! Connection.
	QSqlDatabase m_connection;
	//! Main window.
	MainWindow * m_mainWindow;
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

		QMessageBox::critical( d->m_mainWindow,
			tr( "Unable to read DB configuration..." ),
			QString( "%1\n"
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

		QMessageBox::critical( d->m_mainWindow,
			tr( "Unable to save DB configuration..." ),
			x.whatAsQString() );
	}
}

void
DB::setMainWindow( MainWindow * mainWindow )
{
	d->m_mainWindow = mainWindow;
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
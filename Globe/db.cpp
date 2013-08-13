
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

// QtConfFile include.
#include <QtConfFile/Utils>

// Qt include.
#include <QMessageBox>


namespace Globe {

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
	init( cfg.dbFileName() );
}

void
DB::readCfg( const QString & fileName )
{
	DBTag tag;

	try {
		QtConfFile::readQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		QMessageBox::critical( d->m_mainWindow,
			tr( "Unable to read DB configuration..." ),
			x.whatAsQString() );

		return;
	}

	setCfg( tag.cfg() );
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
	}
	catch( const QtConfFile::Exception & x )
	{
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

	d->m_connection = QSqlDatabase::addDatabase( "QSQLITE" );
	d->m_connection.setDatabaseName( d->m_dbFileName );

	if( !d->m_connection.open() )
	{
		d->m_connection.close();

		emit error();
	}
	else
	{
		d->m_isReady = true;

		emit ready();
	}
}

} /* namespace Globe */

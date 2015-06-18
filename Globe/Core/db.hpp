
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

#ifndef GLOBE__DB_HPP__INCLUDED
#define GLOBE__DB_HPP__INCLUDED

// Qt include.
#include <QObject>
#include <QScopedPointer>
#include <QSqlDatabase>


namespace Globe {

class DBCfg;


//
// DB
//

class DBPrivate;

//! Database interface.
class DB
	:	public QObject
{
	Q_OBJECT

signals:
	//! DB is ready.
	void ready();
	//! Error with DB.
	void error();

private:
	DB( QObject * parent = 0 );

	~DB();

	static void cleanup();

public:
	//! \return Instance.
	static DB & instance();

	//! \return Is DB ready?
	bool isReady() const;

	//! \return Connection.
	const QSqlDatabase & connection() const;

	//! Set configuration of the DB.
	void setCfg( const DBCfg & cfg );

	//! Read configuration.
	void readCfg( const QString & fileName );
	//! Write configuration.
	void saveCfg( const QString & fileName );

private:
	//! Init DB.
	void init( const QString & dbFileName );

private:
	Q_DISABLE_COPY( DB )

	QScopedPointer< DBPrivate > d;
}; // class DB

} /* namespace Globe */

#endif // GLOBE__DB_HPP__INCLUDED

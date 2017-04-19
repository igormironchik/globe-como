
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__DB_CFG_HPP__INCLUDED
#define GLOBE__DB_CFG_HPP__INCLUDED

// cfgfile include.
#include <cfgfile/all.hpp>

// Globe include.
#include <Core/export.hpp>


namespace Globe {

//
// DBCfg
//

//! Configuration of the DB.
class CORE_EXPORT DBCfg {
public:
	DBCfg();

	DBCfg( const DBCfg & other );

	DBCfg & operator = ( const DBCfg & other );

	//! \return Name of the DB file.
	const QString & dbFileName() const;
	//! Set name of the DB file.
	void setDbFileName( const QString & fileName );

private:
	//! Name of the DB file.
	QString m_dbFileName;
}; // class DBCfg


//
// DBTag
//

//! Tag with configuration of the DB.
class CORE_EXPORT DBTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	DBTag();

	explicit DBTag( const DBCfg & cfg );

	//! \return Configuration of the DB.
	DBCfg cfg() const;

private:
	//! Name of the DB file.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_dbFileName;
}; // class DBTag

} /* namespace Globe */

#endif // GLOBE__DB_CFG_HPP__INCLUDED

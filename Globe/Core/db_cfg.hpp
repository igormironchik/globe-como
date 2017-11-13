
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

#ifndef GLOBE__DB_CFG_HPP__INCLUDED
#define GLOBE__DB_CFG_HPP__INCLUDED

// cfgfile include.
#include <cfgfile/all.hpp>

// Globe include.
#include <Globe/Core/export.hpp>


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

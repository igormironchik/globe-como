
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

// Globe include.
#include <Globe/Core/db_cfg.hpp>


namespace Globe {

//
// DBCfg
//

DBCfg::DBCfg()
{
}

DBCfg::DBCfg( const DBCfg & other )
	:	m_dbFileName( other.dbFileName() )
{
}

DBCfg &
DBCfg::operator =( const DBCfg & other )
{
	if( this != &other )
	{
		m_dbFileName = other.dbFileName();
	}

	return *this;
}

const QString &
DBCfg::dbFileName() const
{
	return m_dbFileName;
}

void
DBCfg::setDbFileName( const QString & fileName )
{
	m_dbFileName = fileName;
}


//
// DBTag
//

DBTag::DBTag()
	:	QtConfFile::TagNoValue( QLatin1String( "dbCfg" ), true )
	,	m_dbFileName( *this, QLatin1String( "dbFileName" ), true )
{
}

DBTag::DBTag( const DBCfg & cfg )
	:	QtConfFile::TagNoValue( QLatin1String( "dbCfg" ), true )
	,	m_dbFileName( *this, QLatin1String( "dbFileName" ), true )
{
	m_dbFileName.setValue( cfg.dbFileName() );

	setDefined();
}

DBCfg
DBTag::cfg() const
{
	DBCfg cfg;

	cfg.setDbFileName( m_dbFileName.value() );

	return cfg;
}

} /* namespace Globe */

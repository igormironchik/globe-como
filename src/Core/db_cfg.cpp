
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/db_cfg.hpp>


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
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "dbCfg" ), true )
	,	m_dbFileName( *this, QLatin1String( "dbFileName" ), true )
{
}

DBTag::DBTag( const DBCfg & cfg )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "dbCfg" ), true )
	,	m_dbFileName( *this, QLatin1String( "dbFileName" ), true )
{
	m_dbFileName.set_value( cfg.dbFileName() );

	set_defined();
}

DBCfg
DBTag::cfg() const
{
	DBCfg cfg;

	cfg.setDbFileName( m_dbFileName.value() );

	return cfg;
}

} /* namespace Globe */

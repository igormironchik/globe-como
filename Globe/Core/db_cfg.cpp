
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

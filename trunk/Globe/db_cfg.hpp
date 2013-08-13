
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

#ifndef GLOBE__DB_CFG_HPP__INCLUDED
#define GLOBE__DB_CFG_HPP__INCLUDED

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>


namespace Globe {

//
// DBCfg
//

//! Configuration of the DB.
class DBCfg {
public:
	DBCfg();

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
class DBTag
	:	public QtConfFile::TagNoValue
{
public:
	DBTag();

	explicit DBTag( const DBCfg & cfg );

	//! \return Configuration of the DB.
	DBCfg cfg() const;

private:
	//! Name of the DB file.
	QtConfFile::TagScalar< QString > m_dbFileName;
}; // class DBTag

} /* namespace Globe */

#endif // GLOBE__DB_CFG_HPP__INCLUDED

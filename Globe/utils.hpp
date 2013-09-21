
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

#ifndef GLOBE__UTILS_HPP__INCLUDED
#define GLOBE__UTILS_HPP__INCLUDED

// Qt include.
#include <QString>

// Como include.
#include <Como/Source>


namespace Globe {

//
// relativeFilePath
//

//! \return Path to the specified file.
QString relativeFilePath( const QString & fileName,
	const QString & path = QLatin1String( "./" ) );


//
// checkDirAndCreateIfNotExists
//

//!	Checks is directory exists and create one if not.
void checkDirAndCreateIfNotExists( const QString & path,
	const QString & dirName );


//
// checkPathAndCreateIfNotExists
//

//! Checks is path exists and create one if not.
void checkPathAndCreateIfNotExists( const QString & path );


//
// Como source type string representation constants.
//

static const QString comoSourceIntType = QLatin1String( "int" );
static const QString comoSourceUIntType = QLatin1String( "uint" );
static const QString comoSourceLongLongType = QLatin1String( "longlong" );
static const QString comoSourceULongLongType = QLatin1String( "ulonglong" );
static const QString comoSourceStringType = QLatin1String( "string" );
static const QString comoSourceDoubleType = QLatin1String( "double" );
static const QString comoSourceDateTimeType = QLatin1String( "datetime" );
static const QString comoSourceTimeType = QLatin1String( "time" );
static const QString comoSourceUnknownType = QLatin1String( "unknown" );


//
// comoSourceTypeToString
//

//! Convert Como source type to string.
QString comoSourceTypeToString( Como::Source::Type type );


//
// stringToComoSourceType
//

//! Convert string to Como source type.
Como::Source::Type stringToComoSourceType( const QString & type );

} /* namespace Globe */

#endif // GLOBE__UTILS_HPP__INCLUDED

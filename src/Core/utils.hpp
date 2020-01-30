
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2020 Igor Mironchik

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

#ifndef GLOBE__UTILS_HPP__INCLUDED
#define GLOBE__UTILS_HPP__INCLUDED

// Qt include.
#include <QString>

// Como include.
#include <Como/Source>

// Globe include.
#include <Core/export.hpp>


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
void CORE_EXPORT checkDirAndCreateIfNotExists( const QString & path,
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


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
#include <Globe/Core/utils.hpp>

//  Globe include.
#include <QWidget>
#include <QDir>


namespace Globe {

//
// relativeFilePath
//

QString relativeFilePath( const QString & fileName, const QString & path )
{
	QDir dir( path );

	return dir.relativeFilePath( fileName );
}


//
// checkDirAndCreateIfNotExists
//

void checkDirAndCreateIfNotExists( const QString & path,
	const QString & dirName )
{
	QDir dir( path );

	if( !dir.exists( dirName ) )
		dir.mkdir( dirName );
}


//
// checkPathAndCreateIfNotExists
//

void checkPathAndCreateIfNotExists( const QString & path )
{
	QDir dir( QLatin1String( "." ) );

	dir.mkpath( path );
}


//
// comoSourceTypeToString
//

QString comoSourceTypeToString( Como::Source::Type type )
{
	switch( type )
	{
		case Como::Source::Int : return comoSourceIntType;
		case Como::Source::UInt : return comoSourceUIntType;
		case Como::Source::LongLong : return comoSourceLongLongType;
		case Como::Source::ULongLong : return comoSourceULongLongType;
		case Como::Source::String : return comoSourceStringType;
		case Como::Source::Double : return comoSourceDoubleType;
		case Como::Source::DateTime : return comoSourceDateTimeType;
		case Como::Source::Time : return comoSourceTimeType;
		default : return comoSourceUnknownType;
	}
}


//
// stringToComoSourceType
//

Como::Source::Type stringToComoSourceType( const QString & type )
{
	if( type == comoSourceIntType )
		return Como::Source::Int;
	else if( type == comoSourceUIntType )
		return Como::Source::UInt;
	else if( type == comoSourceLongLongType )
		return Como::Source::LongLong;
	else if( type == comoSourceULongLongType )
		return Como::Source::ULongLong;
	else if( type == comoSourceStringType )
		return Como::Source::String;
	else if( type == comoSourceDoubleType )
		return Como::Source::Double;
	else if( type == comoSourceDateTimeType )
		return Como::Source::DateTime;
	else if( type == comoSourceTimeType )
		return Como::Source::Time;
	else
		return Como::Source::String;
}

} /* namespace Globe */


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


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/utils.hpp>

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

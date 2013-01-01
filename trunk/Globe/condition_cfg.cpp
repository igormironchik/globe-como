
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
#include <Globe/condition_cfg.hpp>


namespace Globe {

//
// IfStatementTag
//

IfStatementTag::IfStatementTag( QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagScalar< QString > ( owner, name, isMandatory )
{
}

IfStatementTag::IfStatementTag( const QVariant & value, QtConfFile::Tag & owner,
	const QString & name, bool isMandatory )
	:	QtConfFile::TagScalar< QString > ( owner, name, isMandatory )
{
	setValue( value.toString() );
}

QString
IfStatementTag::value() const
{
	return QtConfFile::TagScalar< QString >::value();
}


//
// ConditionTag
//

static const QString critical = QLatin1String( "critical" );
static const QString error = QLatin1String( "error" );
static const QString warning = QLatin1String( "warning" );
static const QString debug = QLatin1String( "debug" );
static const QString info = QLatin1String( "info" );
static const QString none = QLatin1String( "none" );

ConditionTag::ConditionTag( const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_greaterOrEqual( *this, QLatin1String( ">=" ), false )
	,	m_greater( *this, QLatin1String( ">" ), false )
	,	m_equal( *this, QLatin1String( "==" ), false )
	,	m_less( *this, QLatin1String( "<" ), false )
	,	m_lessOrEqual( *this, QLatin1String( "<=" ), false )
	,	m_level( *this, QLatin1String( "level" ), true )
	,	m_message( *this, QLatin1String( "message" ), false )
{
	m_levelConstraint.addValue( critical );
	m_levelConstraint.addValue( error );
	m_levelConstraint.addValue( warning );
	m_levelConstraint.addValue( debug );
	m_levelConstraint.addValue( info );
	m_levelConstraint.addValue( none );

	m_level.setConstraint( &m_levelConstraint );
}

static inline QString levelToString( Level l )
{
	switch( l )
	{
		case Critical : return critical;
		case Error : return error;
		case Warning : return warning;
		case Debug : return debug;
		case Info : return info;
		case None : return none;
		default : return QString();
	}
}

static inline Level levelFromString( const QString & str )
{
	if( str == critical )
		return Critical;
	else if( str == error )
		return Error;
	else if( str == warning )
		return Warning;
	else if( str == debug )
		return Debug;
	else if( str == info )
		return Info;
	else if( str == none )
		return None;
	else
		return Critical;
}

ConditionTag::ConditionTag( const Condition & cond, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_greaterOrEqual( *this, QLatin1String( ">=" ), false )
	,	m_greater( *this, QLatin1String( ">" ), false )
	,	m_equal( *this, QLatin1String( "==" ), false )
	,	m_less( *this, QLatin1String( "<" ), false )
	,	m_lessOrEqual( *this, QLatin1String( "<=" ), false )
	,	m_level( *this, QLatin1String( "level" ), true )
	,	m_message( *this, QLatin1String( "message" ), false )
{
	m_levelConstraint.addValue( critical );
	m_levelConstraint.addValue( error );
	m_levelConstraint.addValue( warning );
	m_levelConstraint.addValue( debug );
	m_levelConstraint.addValue( info );
	m_levelConstraint.addValue( none );

	m_level.setConstraint( &m_levelConstraint );

	switch( cond.type() )
	{
		case IfLessOrEqual : m_lessOrEqual.setValue( cond.value().toString() );
			break;
		case IfLess : m_less.setValue( cond.value().toString() );
			break;
		case IfEqual : m_equal.setValue( cond.value().toString() );
			break;
		case IfGreater : m_greater.setValue( cond.value().toString() );
			break;
		case IfGreaterOrEqual : m_greaterOrEqual.setValue( cond.value().toString() );
			break;
	}

	m_level.setValue( levelToString( cond.level() ) );

	if( !cond.message().isEmpty() )
		m_message.setValue( cond.message() );

	setDefined();
}

Condition
ConditionTag::condition() const
{
	Condition c;

	if( m_lessOrEqual.isDefined() )
	{
		c.setType( IfLessOrEqual );
		c.setValue( m_lessOrEqual.value() );
	}
	else if( m_less.isDefined() )
	{
		c.setType( IfLess );
		c.setValue( m_less.value() );
	}
	else if( m_equal.isDefined() )
	{
		c.setType( IfEqual );
		c.setValue( m_equal.value() );
	}
	else if( m_greater.isDefined() )
	{
		c.setType( IfGreater );
		c.setValue( m_greater.value() );
	}
	else if( m_greaterOrEqual.isDefined() )
	{
		c.setType( IfGreaterOrEqual );
		c.setValue( m_greaterOrEqual.value() );
	}

	c.setLevel( levelFromString( m_level.value() ) );

	if( m_message.isDefined() )
		c.setMessage( m_message.value() );

	return c;
}

void
ConditionTag::onFinish( const QtConfFile::ParserInfo & info )
{
	bool relationDefined = false;
	bool moreThanOneRelationDefined = false;

	if( m_lessOrEqual.isDefined() )
	{
		if( relationDefined )
			moreThanOneRelationDefined = true;

		relationDefined = true;
	}

	if( m_less.isDefined() )
	{
		if( relationDefined )
			moreThanOneRelationDefined = true;

		relationDefined = true;
	}

	if( m_equal.isDefined() )
	{
		if( relationDefined )
			moreThanOneRelationDefined = true;

		relationDefined = true;
	}

	if( m_greater.isDefined() )
	{
		if( relationDefined )
			moreThanOneRelationDefined = true;

		relationDefined = true;
	}

	if( m_greaterOrEqual.isDefined() )
	{
		if( relationDefined )
			moreThanOneRelationDefined = true;

		relationDefined = true;
	}

	if( !relationDefined )
		throw QtConfFile::Exception( QString( "Undefined tag with logical relation. "
			"Where parent is \"%1\". In file \"%2\" on line %3." )
				.arg( name() )
				.arg( info.fileName() )
				.arg( info.lineNumber() ) );
	else if( moreThanOneRelationDefined )
		throw QtConfFile::Exception( QString( "More than one logical relation defined. "
			"Where parent is \"%1\". In file \"%2\" on line %3." )
				.arg( name() )
				.arg( info.fileName() )
				.arg( info.lineNumber() ) );

	QtConfFile::TagNoValue::onFinish( info );
}


//
// OtherwiseTag
//

OtherwiseTag::OtherwiseTag( QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_level( *this, QLatin1String( "level" ), true )
	,	m_message( *this, QLatin1String( "message" ), false )
{
	m_levelConstraint.addValue( critical );
	m_levelConstraint.addValue( error );
	m_levelConstraint.addValue( warning );
	m_levelConstraint.addValue( debug );
	m_levelConstraint.addValue( info );
	m_levelConstraint.addValue( none );

	m_level.setConstraint( &m_levelConstraint );
}

OtherwiseTag::OtherwiseTag( const Condition & cond, QtConfFile::Tag & owner,
	const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_level( *this, QLatin1String( "level" ), true )
	,	m_message( *this, QLatin1String( "message" ), false )
{
	m_levelConstraint.addValue( critical );
	m_levelConstraint.addValue( error );
	m_levelConstraint.addValue( warning );
	m_levelConstraint.addValue( debug );
	m_levelConstraint.addValue( info );
	m_levelConstraint.addValue( none );

	m_level.setConstraint( &m_levelConstraint );

	m_level.setValue( levelToString( cond.level() ) );

	if( !cond.message().isEmpty() )
		m_message.setValue( cond.message() );

	setDefined();
}

Condition
OtherwiseTag::value() const
{
	Condition c;

	c.setLevel( levelFromString( m_level.value() ) );

	if( m_message.isDefined() )
		c.setMessage( m_message.value() );

	return c;
}

} /* namespace Globe */


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

#ifndef GLOBE__CONDITION_CFG_HPP__INCLUDED
#define GLOBE__CONDITION_CFG_HPP__INCLUDED

// Globe include.
#include <Globe/Core/condition.hpp>

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>
#include <QtConfFile/ConstraintOneOf>
#include <QtConfFile/Exceptions>


namespace Globe {

//
// IfStatementTag
//

//! Tag with logical relation.
template< class T >
class IfStatementTag
	:	public QtConfFile::TagScalar< QString >
{
public:
	IfStatementTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory )
		:	QtConfFile::TagScalar< QString > ( owner, name, isMandatory )
	{
	}

	IfStatementTag( const QVariant & value, QtConfFile::Tag & owner,
		const QString & name, bool isMandatory )
		:	QtConfFile::TagScalar< QString > ( owner, name, isMandatory )
	{
		setValue( value.toString() );
	}

	void onFinish( const QtConfFile::ParserInfo & info )
	{
		initValue( info );

		QtConfFile::TagScalar< QString >::onFinish( info );
	}

	QVariant value() const
	{
		return QVariant( m_value );
	}

private:
	//! Initialize value.
	void initValue( const QtConfFile::ParserInfo & info );

private:
	//! Value.
	T m_value;
}; // class IfStatementTag

inline
void
IfStatementTag< int >::initValue( const QtConfFile::ParserInfo & info )
{
	const QString str = QtConfFile::TagScalar< QString >::value();

	bool ok = false;

	m_value = str.toInt( &ok );

	if( !ok )
		throw QtConfFile::Exception( QString(
			"Invalid value in file \"%1\" on line %2.\n"
			"Can't convert \"%3\" to integer." )
				.arg( info.fileName() )
				.arg( info.lineNumber() )
				.arg( str ) );
}

inline
void
IfStatementTag< uint >::initValue( const QtConfFile::ParserInfo & info )
{
	const QString str = QtConfFile::TagScalar< QString >::value();

	bool ok = false;

	m_value = str.toUInt( &ok );

	if( !ok )
		throw QtConfFile::Exception( QString(
			"Invalid value in file \"%1\" on line %2.\n"
			"Can't convert \"%3\" to unsigned integer." )
				.arg( info.fileName() )
				.arg( info.lineNumber() )
				.arg( str ) );
}

inline
void
IfStatementTag< qlonglong >::initValue( const QtConfFile::ParserInfo & info )
{
	const QString str = QtConfFile::TagScalar< QString >::value();

	bool ok = false;

	m_value = str.toLongLong( &ok );

	if( !ok )
		throw QtConfFile::Exception( QString(
			"Invalid value in file \"%1\" on line %2.\n"
			"Can't convert \"%3\" to long long." )
				.arg( info.fileName() )
				.arg( info.lineNumber() )
				.arg( str ) );
}

inline
void
IfStatementTag< qulonglong >::initValue( const QtConfFile::ParserInfo & info )
{
	const QString str = QtConfFile::TagScalar< QString >::value();

	bool ok = false;

	m_value = str.toULongLong( &ok );

	if( !ok )
		throw QtConfFile::Exception( QString(
			"Invalid value in file \"%1\" on line %2.\n"
			"Can't convert \"%3\" to unsigned long long." )
				.arg( info.fileName() )
				.arg( info.lineNumber() )
				.arg( str ) );
}

inline
void
IfStatementTag< double >::initValue( const QtConfFile::ParserInfo & info )
{
	const QString str = QtConfFile::TagScalar< QString >::value();

	bool ok = false;

	m_value = str.toDouble( &ok );

	if( !ok )
		throw QtConfFile::Exception( QString(
			"Invalid value in file \"%1\" on line %2.\n"
			"Can't convert \"%3\" to double." )
				.arg( info.fileName() )
				.arg( info.lineNumber() )
				.arg( str ) );
}

inline
void
IfStatementTag< QString >::initValue( const QtConfFile::ParserInfo & info )
{
	Q_UNUSED( info )

	m_value = QtConfFile::TagScalar< QString >::value();
}

inline
void
IfStatementTag< QDateTime >::initValue( const QtConfFile::ParserInfo & info )
{
	const QString str = QtConfFile::TagScalar< QString >::value();

	m_value = QDateTime::fromString( str );

	if( !m_value.isValid() )
		throw QtConfFile::Exception( QString(
			"Invalid value in file \"%1\" on line %2.\n"
			"Can't convert \"%3\" to date and time." )
				.arg( info.fileName() )
				.arg( info.lineNumber() )
				.arg( str ) );
}

inline
void
IfStatementTag< QTime >::initValue( const QtConfFile::ParserInfo & info )
{
	const QString str = QtConfFile::TagScalar< QString >::value();

	m_value = QTime::fromString( str );

	if( !m_value.isValid() )
		throw QtConfFile::Exception( QString(
			"Invalid value in file \"%1\" on line %2.\n"
			"Can't convert \"%3\" to time." )
				.arg( info.fileName() )
				.arg( info.lineNumber() )
				.arg( str ) );
}


//
// ConditionTag
//

static const QString criticalLevelString = QLatin1String( "critical" );
static const QString errorLevelString = QLatin1String( "error" );
static const QString warningLevelString = QLatin1String( "warning" );
static const QString debugLevelString = QLatin1String( "debug" );
static const QString infoLevelString = QLatin1String( "info" );
static const QString noneLevelString = QLatin1String( "none" );

static inline QString levelToString( Level l )
{
	switch( l )
	{
		case Critical : return criticalLevelString;
		case Error : return errorLevelString;
		case Warning : return warningLevelString;
		case Debug : return debugLevelString;
		case Info : return infoLevelString;
		case None : return noneLevelString;
		default : return QString();
	}
}

static inline Level levelFromString( const QString & str )
{
	if( str == criticalLevelString )
		return Critical;
	else if( str == errorLevelString )
		return Error;
	else if( str == warningLevelString )
		return Warning;
	else if( str == debugLevelString )
		return Debug;
	else if( str == infoLevelString )
		return Info;
	else if( str == noneLevelString )
		return None;
	else
		return Critical;
}

//! Configuration's tag for condition.
template< class T >
class ConditionTag
	:	public QtConfFile::TagNoValue
{
public:
	explicit ConditionTag( const QString & name, bool isMandatory = false )
		:	QtConfFile::TagNoValue( name, isMandatory )
		,	m_greaterOrEqual( *this, QLatin1String( ">=" ), false )
		,	m_greater( *this, QLatin1String( ">" ), false )
		,	m_equal( *this, QLatin1String( "==" ), false )
		,	m_less( *this, QLatin1String( "<" ), false )
		,	m_lessOrEqual( *this, QLatin1String( "<=" ), false )
		,	m_level( *this, QLatin1String( "level" ), true )
		,	m_message( *this, QLatin1String( "message" ), false )
	{
		m_levelConstraint.addValue( criticalLevelString );
		m_levelConstraint.addValue( errorLevelString );
		m_levelConstraint.addValue( warningLevelString );
		m_levelConstraint.addValue( debugLevelString );
		m_levelConstraint.addValue( infoLevelString );
		m_levelConstraint.addValue( noneLevelString );

		m_level.setConstraint( &m_levelConstraint );
	}

	ConditionTag( const Condition & cond, const QString & name,
		bool isMandatory = false )
		:	QtConfFile::TagNoValue( name, isMandatory )
		,	m_greaterOrEqual( *this, QLatin1String( ">=" ), false )
		,	m_greater( *this, QLatin1String( ">" ), false )
		,	m_equal( *this, QLatin1String( "==" ), false )
		,	m_less( *this, QLatin1String( "<" ), false )
		,	m_lessOrEqual( *this, QLatin1String( "<=" ), false )
		,	m_level( *this, QLatin1String( "level" ), true )
		,	m_message( *this, QLatin1String( "message" ), false )
	{
		m_levelConstraint.addValue( criticalLevelString );
		m_levelConstraint.addValue( errorLevelString );
		m_levelConstraint.addValue( warningLevelString );
		m_levelConstraint.addValue( debugLevelString );
		m_levelConstraint.addValue( infoLevelString );
		m_levelConstraint.addValue( noneLevelString );

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

	//! Called when tag parsing finished.
	void onFinish( const QtConfFile::ParserInfo & info )
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

	//! \return Condition.
	Condition condition() const
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

private:
	//! If greater or equal.
	IfStatementTag< T > m_greaterOrEqual;
	//! If greater.
	IfStatementTag< T > m_greater;
	//! If equal.
	IfStatementTag< T > m_equal;
	//! If less.
	IfStatementTag< T > m_less;
	//! If less or equal.
	IfStatementTag< T > m_lessOrEqual;
	//! Level.
	QtConfFile::TagScalar< QString > m_level;
	//! Constraint for level.
	QtConfFile::ConstraintOneOf< QString > m_levelConstraint;
	//! Message.
	QtConfFile::TagScalar< QString > m_message;
}; // class ConditionTag


//
// OtherwiseTag
//

//! Configuration's tag for otherwise condition.
class OtherwiseTag
	:	public QtConfFile::TagNoValue
{
public:
	OtherwiseTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	OtherwiseTag( const Condition & cond, QtConfFile::Tag & owner,
		const QString & name, bool isMandatory = false );

	//! \return Condition.
	Condition value() const;

private:
	//! Level.
	QtConfFile::TagScalar< QString > m_level;
	//! Constraint for level.
	QtConfFile::ConstraintOneOf< QString > m_levelConstraint;
	//! Message.
	QtConfFile::TagScalar< QString > m_message;
}; // class OtherwiseTag

} /* namespace Globe */

#endif // GLOBE__CONDITION_CFG_HPP__INCLUDED

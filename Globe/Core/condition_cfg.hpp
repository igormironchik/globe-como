
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

#ifndef GLOBE__CONDITION_CFG_HPP__INCLUDED
#define GLOBE__CONDITION_CFG_HPP__INCLUDED

// Globe include.
#include <Globe/Core/condition.hpp>

// cfgfile include.
#include <cfgfile/all.hpp>


namespace Globe {

//
// IfStatementTag
//

//! Tag with logical relation.
template< class T >
class IfStatementTag
	:	public cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t >
{
public:
	IfStatementTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory )
		:	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > (
				owner, name, isMandatory )
	{
	}

	IfStatementTag( const QVariant & value,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory )
		:	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > (
				owner, name, isMandatory )
	{
		set_value( value.toString() );
	}

	void on_finish( const cfgfile::parser_info_t< cfgfile::qstring_trait_t > & info )
	{
		initValue( info );

		cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t >::on_finish( info );
	}

	QVariant value() const
	{
		return QVariant( m_value );
	}

private:
	//! Initialize value.
	void initValue( const cfgfile::parser_info_t< cfgfile::qstring_trait_t > & info );

private:
	//! Value.
	T m_value;
}; // class IfStatementTag

template<>
inline void
IfStatementTag< int >::initValue( const cfgfile::parser_info_t< cfgfile::qstring_trait_t > & info )
{
	const QString str =
		cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t >::value();

	bool ok = false;

	m_value = str.toInt( &ok );

	if( !ok )
		throw cfgfile::exception_t< cfgfile::qstring_trait_t >( QString(
			"Invalid value in file \"%1\" on line %2.\n"
			"Can't convert \"%3\" to integer." )
				.arg( info.file_name() )
				.arg( info.line_number() )
				.arg( str ) );
}

template<>
inline void
IfStatementTag< uint >::initValue( const cfgfile::parser_info_t< cfgfile::qstring_trait_t > & info )
{
	const QString str =
		cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t >::value();

	bool ok = false;

	m_value = str.toUInt( &ok );

	if( !ok )
		throw cfgfile::exception_t< cfgfile::qstring_trait_t >( QString(
			"Invalid value in file \"%1\" on line %2.\n"
			"Can't convert \"%3\" to unsigned integer." )
				.arg( info.file_name() )
				.arg( info.line_number() )
				.arg( str ) );
}

template<>
inline void
IfStatementTag< qlonglong >::initValue( const cfgfile::parser_info_t< cfgfile::qstring_trait_t > & info )
{
	const QString str =
		cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t >::value();

	bool ok = false;

	m_value = str.toLongLong( &ok );

	if( !ok )
		throw cfgfile::exception_t< cfgfile::qstring_trait_t >( QString(
			"Invalid value in file \"%1\" on line %2.\n"
			"Can't convert \"%3\" to long long." )
				.arg( info.file_name() )
				.arg( info.line_number() )
				.arg( str ) );
}

template<>
inline void
IfStatementTag< qulonglong >::initValue( const cfgfile::parser_info_t< cfgfile::qstring_trait_t > & info )
{
	const QString str =
		cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t >::value();

	bool ok = false;

	m_value = str.toULongLong( &ok );

	if( !ok )
		throw cfgfile::exception_t< cfgfile::qstring_trait_t >( QString(
			"Invalid value in file \"%1\" on line %2.\n"
			"Can't convert \"%3\" to unsigned long long." )
				.arg( info.file_name() )
				.arg( info.line_number() )
				.arg( str ) );
}

template<>
inline void
IfStatementTag< double >::initValue( const cfgfile::parser_info_t< cfgfile::qstring_trait_t > & info )
{
	const QString str =
		cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t >::value();

	bool ok = false;

	m_value = str.toDouble( &ok );

	if( !ok )
		throw cfgfile::exception_t< cfgfile::qstring_trait_t >( QString(
			"Invalid value in file \"%1\" on line %2.\n"
			"Can't convert \"%3\" to double." )
				.arg( info.file_name() )
				.arg( info.line_number() )
				.arg( str ) );
}

template<>
inline void
IfStatementTag< QString >::initValue( const cfgfile::parser_info_t< cfgfile::qstring_trait_t > & info )
{
	Q_UNUSED( info )

	m_value =
		cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t >::value();
}

template<>
inline void
IfStatementTag< QDateTime >::initValue( const cfgfile::parser_info_t< cfgfile::qstring_trait_t > & info )
{
	const QString str =
		cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t >::value();

	m_value = QDateTime::fromString( str );

	if( !m_value.isValid() )
		throw cfgfile::exception_t< cfgfile::qstring_trait_t >( QString(
			"Invalid value in file \"%1\" on line %2.\n"
			"Can't convert \"%3\" to date and time." )
				.arg( info.file_name() )
				.arg( info.line_number() )
				.arg( str ) );
}

template<>
inline void
IfStatementTag< QTime >::initValue( const cfgfile::parser_info_t< cfgfile::qstring_trait_t > & info )
{
	const QString str =
		cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t >::value();

	m_value = QTime::fromString( str );

	if( !m_value.isValid() )
		throw cfgfile::exception_t< cfgfile::qstring_trait_t >( QString(
			"Invalid value in file \"%1\" on line %2.\n"
			"Can't convert \"%3\" to time." )
				.arg( info.file_name() )
				.arg( info.line_number() )
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
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	explicit ConditionTag( const QString & name, bool isMandatory = false )
		:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > ( name, isMandatory )
		,	m_greaterOrEqual( *this, QLatin1String( ">=" ), false )
		,	m_greater( *this, QLatin1String( ">" ), false )
		,	m_equal( *this, QLatin1String( "==" ), false )
		,	m_less( *this, QLatin1String( "<" ), false )
		,	m_lessOrEqual( *this, QLatin1String( "<=" ), false )
		,	m_level( *this, QLatin1String( "level" ), true )
		,	m_message( *this, QLatin1String( "message" ), false )
	{
		m_levelConstraint.add_value( criticalLevelString );
		m_levelConstraint.add_value( errorLevelString );
		m_levelConstraint.add_value( warningLevelString );
		m_levelConstraint.add_value( debugLevelString );
		m_levelConstraint.add_value( infoLevelString );
		m_levelConstraint.add_value( noneLevelString );

		m_level.set_constraint( &m_levelConstraint );
	}

	ConditionTag( const Condition & cond, const QString & name,
		bool isMandatory = false )
		:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > ( name, isMandatory )
		,	m_greaterOrEqual( *this, QLatin1String( ">=" ), false )
		,	m_greater( *this, QLatin1String( ">" ), false )
		,	m_equal( *this, QLatin1String( "==" ), false )
		,	m_less( *this, QLatin1String( "<" ), false )
		,	m_lessOrEqual( *this, QLatin1String( "<=" ), false )
		,	m_level( *this, QLatin1String( "level" ), true )
		,	m_message( *this, QLatin1String( "message" ), false )
	{
		m_levelConstraint.add_value( criticalLevelString );
		m_levelConstraint.add_value( errorLevelString );
		m_levelConstraint.add_value( warningLevelString );
		m_levelConstraint.add_value( debugLevelString );
		m_levelConstraint.add_value( infoLevelString );
		m_levelConstraint.add_value( noneLevelString );

		m_level.set_constraint( &m_levelConstraint );

		switch( cond.type() )
		{
			case IfLessOrEqual : m_lessOrEqual.set_value( cond.value().toString() );
				break;
			case IfLess : m_less.set_value( cond.value().toString() );
				break;
			case IfEqual : m_equal.set_value( cond.value().toString() );
				break;
			case IfGreater : m_greater.set_value( cond.value().toString() );
				break;
			case IfGreaterOrEqual : m_greaterOrEqual.set_value( cond.value().toString() );
				break;
		}

		m_level.set_value( levelToString( cond.level() ) );

		if( !cond.message().isEmpty() )
			m_message.set_value( cond.message() );

		set_defined();
	}

	//! Called when tag parsing finished.
	void on_finish( const cfgfile::parser_info_t< cfgfile::qstring_trait_t > & info )
	{
		bool relationDefined = false;
		bool moreThanOneRelationDefined = false;

		if( m_lessOrEqual.is_defined() )
		{
			if( relationDefined )
				moreThanOneRelationDefined = true;

			relationDefined = true;
		}

		if( m_less.is_defined() )
		{
			if( relationDefined )
				moreThanOneRelationDefined = true;

			relationDefined = true;
		}

		if( m_equal.is_defined() )
		{
			if( relationDefined )
				moreThanOneRelationDefined = true;

			relationDefined = true;
		}

		if( m_greater.is_defined() )
		{
			if( relationDefined )
				moreThanOneRelationDefined = true;

			relationDefined = true;
		}

		if( m_greaterOrEqual.is_defined() )
		{
			if( relationDefined )
				moreThanOneRelationDefined = true;

			relationDefined = true;
		}

		if( !relationDefined )
			throw cfgfile::exception_t< cfgfile::qstring_trait_t >(
				QString( "Undefined tag with logical relation. "
					"Where parent is \"%1\". In file \"%2\" on line %3." )
						.arg( name() )
						.arg( info.file_name() )
						.arg( info.line_number() ) );
		else if( moreThanOneRelationDefined )
			throw cfgfile::exception_t< cfgfile::qstring_trait_t >(
				QString( "More than one logical relation defined. "
					"Where parent is \"%1\". In file \"%2\" on line %3." )
						.arg( name() )
						.arg( info.file_name() )
						.arg( info.line_number() ) );

		cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >::on_finish( info );
	}

	//! \return Condition.
	Condition condition() const
	{
		Condition c;

		if( m_lessOrEqual.is_defined() )
		{
			c.setType( IfLessOrEqual );
			c.setValue( m_lessOrEqual.value() );
		}
		else if( m_less.is_defined() )
		{
			c.setType( IfLess );
			c.setValue( m_less.value() );
		}
		else if( m_equal.is_defined() )
		{
			c.setType( IfEqual );
			c.setValue( m_equal.value() );
		}
		else if( m_greater.is_defined() )
		{
			c.setType( IfGreater );
			c.setValue( m_greater.value() );
		}
		else if( m_greaterOrEqual.is_defined() )
		{
			c.setType( IfGreaterOrEqual );
			c.setValue( m_greaterOrEqual.value() );
		}

		c.setLevel( levelFromString( m_level.value() ) );

		if( m_message.is_defined() )
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
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_level;
	//! Constraint for level.
	cfgfile::constraint_one_of_t< QString > m_levelConstraint;
	//! Message.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_message;
}; // class ConditionTag


//
// OtherwiseTag
//

//! Configuration's tag for otherwise condition.
class OtherwiseTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	OtherwiseTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	OtherwiseTag( const Condition & cond,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	//! \return Condition.
	Condition value() const;

private:
	//! Level.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_level;
	//! Constraint for level.
	cfgfile::constraint_one_of_t< QString > m_levelConstraint;
	//! Message.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_message;
}; // class OtherwiseTag

} /* namespace Globe */

#endif // GLOBE__CONDITION_CFG_HPP__INCLUDED

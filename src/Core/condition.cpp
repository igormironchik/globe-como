
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

// Globe include.
#include <Core/condition.hpp>


namespace Globe {

//
// Condition
//

Condition::Condition()
	:	m_exprType( IfEqual )
	,	m_level( None )
{
}

Condition::Condition( const Condition & other )
	:	m_exprType( other.type() )
	,	m_value( other.value() )
	,	m_level( other.level() )
	,	m_message( other.message() )
{
}

Condition &
Condition::operator = ( const Condition & other )
{
	if( this != &other )
	{
		m_exprType = other.type();
		m_value = other.value();
		m_level = other.level();
		m_message = other.message();
	}

	return *this;
}

template< class T >
bool checkIfStatement( const T & a, const T & b, Expression expr )
{
	switch( expr )
	{
		case IfLessOrEqual : return a <= b;
		case IfLess : return a < b;
		case IfEqual : return a == b;
		case IfGreater : return a > b;
		case IfGreaterOrEqual : return a >= b;
		default : return false;
	}
}

bool
Condition::check( const QVariant & val, Como::Source::Type valueType ) const
{
	switch( valueType )
	{
		case Como::Source::Int :
			{
				bool ok = false;

				const int a = m_value.toInt( &ok );

				if( !ok )
					return false;

				const int b = val.toInt( &ok );

				if( !ok )
					return false;

				return checkIfStatement< int > ( b, a, m_exprType );
			}
			break;
		case Como::Source::UInt :
			{
				bool ok = false;

				const uint a = m_value.toUInt( &ok );

				if( !ok )
					return false;

				const uint b = val.toUInt( &ok );

				if( !ok )
					return false;

				return checkIfStatement< uint > ( b, a, m_exprType );
			}
			break;
		case Como::Source::LongLong :
			{
				bool ok = false;

				const qlonglong a = m_value.toLongLong( &ok );

				if( !ok )
					return false;

				const qlonglong b = val.toLongLong( &ok );

				if( !ok )
					return false;

				return checkIfStatement< qlonglong > ( b, a, m_exprType );
			}
			break;
		case Como::Source::ULongLong :
			{
				bool ok = false;

				const qulonglong a = m_value.toULongLong( &ok );

				if( !ok )
					return false;

				const qulonglong b = val.toULongLong( &ok );

				if( !ok )
					return false;

				return checkIfStatement< qulonglong > ( b, a, m_exprType );
			}
			break;
		case Como::Source::Double :
			{
				bool ok = false;

				const double a = m_value.toDouble( &ok );

				if( !ok )
					return false;

				const double b = val.toDouble( &ok );

				if( !ok )
					return false;

				return checkIfStatement< double > ( b, a, m_exprType );
			}
			break;
		case Como::Source::String :
			{
				return checkIfStatement< QString > ( val.toString(),
					m_value.toString(), m_exprType );
			}
			break;
		case Como::Source::DateTime :
			{
				return checkIfStatement< QDateTime > ( val.toDateTime(),
					m_value.toDateTime(), m_exprType );
			}
			break;
		case Como::Source::Time :
			{
				return checkIfStatement< QTime > ( val.toTime(),
					m_value.toTime(), m_exprType );
			}
		default :
			{
				return checkIfStatement< QString > ( val.toString(),
					m_value.toString(), m_exprType );
			}
			break;
	}
}

Expression
Condition::type() const
{
	return m_exprType;
}

void
Condition::setType( Expression expr )
{
	m_exprType = expr;
}

const QVariant &
Condition::value() const
{
	return m_value;
}

void
Condition::setValue( const QVariant & v )
{
	m_value = v;
}

Level
Condition::level() const
{
	return m_level;
}

void
Condition::setLevel( Level l )
{
	m_level = l;
}

const QString &
Condition::message() const
{
	return m_message;
}

void
Condition::setMessage( const QString & msg )
{
	m_message = msg;
}

bool
Condition::isValid() const
{
	return ( m_level != None || !m_message.isEmpty() );
}

} /* namespace Globe */

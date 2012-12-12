
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 Igor Mironchik

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
#include <Globe/condition.hpp>


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
	if( valueType = Como::Source::Int )
	{
		bool ok = false;

		const int a = m_value.toInt( &ok );

		if( !ok )
			return false;

		const int b = val.toInt( &ok );

		if( !ok )
			return false;

		return checkIfStatement< int > ( a, b, m_exprType );
	}
	else if( valueType = Como::Source::Double )
	{
		bool ok = false;

		const double a = m_value.toDouble( &ok );

		if( !ok )
			return false;

		const double b = val.toDouble( &ok );

		if( !ok )
			return false;

		return checkIfStatement< double > ( a, b, m_exprType );
	}
	else
		return checkIfStatement< QString > ( m_value.toString(),
			val.toString(), m_exprType );
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

} /* namespace Globe */


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
#include <Core/properties.hpp>


namespace Globe {

//
// Properties
//

Properties::Properties()
	:	m_priority( 0 )
{
}

Properties::Properties( const Properties & other )
	:	m_priority( other.priority() )
	,	m_conditions( other.m_conditions )
	,	m_otherwise( other.m_otherwise )
{
}

Properties &
Properties::operator = ( const Properties & other )
{
	if( this != &other )
	{
		m_priority = other.priority();
		m_conditions = other.m_conditions;
		m_otherwise = other.m_otherwise;
	}

	return *this;
}

int
Properties::priority() const
{
	return m_priority;
}

void
Properties::setPriority( int p )
{
	m_priority = p;
}

int
Properties::conditionsAmount() const
{
	return m_conditions.count();
}

Condition &
Properties::conditionAt( int index )
{
	return m_conditions[ index ];
}

const Condition &
Properties::conditionAt( int index ) const
{
	return m_conditions.at( index );
}

Condition &
Properties::otherwise()
{
	return m_otherwise;
}

const Condition &
Properties::otherwise() const
{
	return m_otherwise;
}

void
Properties::insertCondition( const Condition & cond, int index )
{
	m_conditions.insert( index, cond );
}

void
Properties::removeCondition( int index )
{
	m_conditions.removeAt( index );
}

void
Properties::swapConditions( int i, int j )
{
	m_conditions.swapItemsAt( i, j );
}

const Condition &
Properties::checkConditions( const QVariant & value,
	Como::Source::Type valueType ) const
{
	foreach( const Condition & c, m_conditions )
	{
		if( c.check( value, valueType ) )
			return c;
	}

	return m_otherwise;
}


//
// readPropertiesConfiguration
//

void readPropertiesConfiguration( const QString & fileName,
	Properties & p, Como::Source::Type t )
{
	switch( t )
	{
		case Como::Source::Int :
			readPropertiesConfigurationTemplate< int > ( fileName, p );
			break;
		case Como::Source::UInt :
			readPropertiesConfigurationTemplate< uint > ( fileName, p );
			break;
		case Como::Source::LongLong :
			readPropertiesConfigurationTemplate< qlonglong > ( fileName, p );
			break;
		case Como::Source::ULongLong :
			readPropertiesConfigurationTemplate< qulonglong > ( fileName, p );
			break;
		case Como::Source::String :
			readPropertiesConfigurationTemplate< QString > ( fileName, p );
			break;
		case Como::Source::Double :
			readPropertiesConfigurationTemplate< double > ( fileName, p );
			break;
		case Como::Source::DateTime :
			readPropertiesConfigurationTemplate< QDateTime > ( fileName, p );
			break;
		case Como::Source::Time :
			readPropertiesConfigurationTemplate< QTime > ( fileName, p );
			break;
	}
}


//
// savePropertiesConfiguration
//

void savePropertiesConfiguration( const QString & fileName,
	const Properties & p, Como::Source::Type t )
{
	switch( t )
	{
		case Como::Source::Int :
			savePropertiesConfigurationTemplate< int > ( fileName, p );
			break;
		case Como::Source::UInt :
			savePropertiesConfigurationTemplate< uint > ( fileName, p );
			break;
		case Como::Source::LongLong :
			savePropertiesConfigurationTemplate< qlonglong > ( fileName, p );
			break;
		case Como::Source::ULongLong :
			savePropertiesConfigurationTemplate< qulonglong > ( fileName, p );
			break;
		case Como::Source::String :
			savePropertiesConfigurationTemplate< QString > ( fileName, p );
			break;
		case Como::Source::Double :
			savePropertiesConfigurationTemplate< double > ( fileName, p );
			break;
		case Como::Source::DateTime :
			savePropertiesConfigurationTemplate< QDateTime > ( fileName, p );
			break;
		case Como::Source::Time :
			savePropertiesConfigurationTemplate< QTime > ( fileName, p );
			break;
	}
}

} /* namespace Globe */

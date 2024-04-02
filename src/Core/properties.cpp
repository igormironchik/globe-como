
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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

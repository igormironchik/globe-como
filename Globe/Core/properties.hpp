
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

#ifndef GLOBE__PROPERTIES_HPP__INLCUDED
#define GLOBE__PROPERTIES_HPP__INLCUDED

// Como include.
#include <Como/Source>

// Qt include.
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

// Globe include.
#include <Globe/Core/condition.hpp>
#include <Globe/Core/condition_cfg.hpp>

// cfgfile include.
#include <cfgfile/all.hpp>


namespace Globe {

//
// Properties
//

//! Properties of the source.
class Properties {
public:
	Properties();

	Properties( const Properties & other );

	Properties & operator = ( const Properties & other );

	//! \return Priority of the source.
	int priority() const;
	//! Set priority of the source.
	void setPriority( int p );

	//! \return Amount of conditions.
	int conditionsAmount() const;
	//! \return Condition with the given index.
	Condition & conditionAt( int index );
	//! \return Condition with the given index.
	const Condition & conditionAt( int index ) const;
	//! \return Otherwise condition.
	Condition & otherwise();
	//! \return Otherwise condition.
	const Condition & otherwise() const;
	//! Insert new condition to the new place with index.
	void insertCondition( const Condition & cond, int index );
	//! Remove condition with the index.
	void removeCondition( int index );
	//! Swap to conditions in the list.
	void swapConditions( int i, int j );
	//! \return Condition for the given value.
	const Condition & checkConditions( const QVariant & value,
		Como::Source::Type valueType ) const;

private:
	//! Priority of the source.
	int m_priority;
	//! List of conditions for this source.
	QList< Condition > m_conditions;
	//! Otherwise condition.
	Condition m_otherwise;
}; // class Properties


//
// PropertiesTag
//

//! Tag for properties of the source.
template< class T >
class PropertiesTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	PropertiesTag()
		:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
				QLatin1String( "properties" ), true )
		,	m_priority( *this, QLatin1String( "priority" ), false )
		,	m_conditions( *this, QLatin1String( "if" ), false )
		,	m_otherwise( *this, QLatin1String( "otherwise" ), false )
		,	m_priorityConstraint( 0, 999 )
	{
		m_priority.set_constraint( &m_priorityConstraint );
	}

	PropertiesTag( const Properties & properties )
		:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
				QLatin1String( "properties" ), true )
		,	m_priority( *this, QLatin1String( "priority" ), false )
		,	m_conditions( *this, QLatin1String( "if" ), false )
		,	m_otherwise( properties.otherwise(), *this,
				QLatin1String( "otherwise" ), false )
		,	m_priorityConstraint( 0, 999 )
	{
		m_priority.set_constraint( &m_priorityConstraint );

		if( properties.priority() > 0 )
			m_priority.set_value( properties.priority() );

		for( int i = 0; i < properties.conditionsAmount(); ++i )
		{
			typename cfgfile::tag_vector_of_tags_t< ConditionTag< T >,
				cfgfile::qstring_trait_t >::ptr_to_tag_t tag(
					new ConditionTag< T >( properties.conditionAt( i ),
						QLatin1String( "if" ), true ) );

			m_conditions.set_value( tag );
		}

		set_defined();
	}

	Properties properties() const
	{
		Properties p;

		if( m_priority.is_defined() )
			p.setPriority( m_priority.value() );

		if( m_conditions.is_defined() )
		{
			for( std::size_t i = 0; i < m_conditions.size(); ++i )
				p.insertCondition( m_conditions.at( i ).condition(),
					static_cast< int > ( i ) );
		}

		if( m_otherwise.is_defined() )
			p.otherwise() = m_otherwise.value();

		return p;
	}

private:
	//! Priority.
	cfgfile::tag_scalar_t< int, cfgfile::qstring_trait_t > m_priority;
	//! Conditions.
	cfgfile::tag_vector_of_tags_t< ConditionTag< T >,
		cfgfile::qstring_trait_t > m_conditions;
	//! Otherwise condition.
	OtherwiseTag m_otherwise;
	//! Constraint for the priority.
	cfgfile::constraint_min_max_t< int > m_priorityConstraint;
}; // class PropertiesTag


//
// readPropertiesConfigurationTemplate
//

template< class T >
void
readPropertiesConfigurationTemplate( const QString & fileName, Properties & p )
{
	PropertiesTag< T > tag;

	QFile file( fileName );

	if( file.open( QIODevice::ReadOnly ) )
	{
		QTextStream stream( &file );
		stream.setCodec( QTextCodec::codecForName( "UTF-8" ) );

		try {
			cfgfile::read_cfgfile( tag, stream, fileName );

			file.close();
		}
		catch( ... )
		{
			file.close();

			throw;
		}

		p = tag.properties();
	}
}


//
// savePropertiesConfigurationTemplate
//

template< class T >
void
savePropertiesConfigurationTemplate( const QString & fileName,
	const Properties & p )
{
	PropertiesTag< T > tag( p );

	QFile file( fileName );

	if( file.open( QIODevice::WriteOnly ) )
	{
		QTextStream stream( &file );
		stream.setCodec( QTextCodec::codecForName( "UTF-8" ) );

		try {
			cfgfile::write_cfgfile( tag, stream );

			file.close();
		}
		catch( ... )
		{
			file.close();

			throw;
		}
	}
}


//
// readPropertiesConfiguration
//

void readPropertiesConfiguration( const QString & fileName,
	Properties & p, Como::Source::Type t );


//
// savePropertiesConfiguration
//

void savePropertiesConfiguration( const QString & fileName,
	const Properties & p, Como::Source::Type t );

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_HPP__INLCUDED

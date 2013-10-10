
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

#ifndef GLOBE__PROPERTIES_HPP__INLCUDED
#define GLOBE__PROPERTIES_HPP__INLCUDED

// Como include.
#include <Como/Source>

// Qt include.
#include <QList>

// Globe include.
#include <Globe/condition.hpp>
#include <Globe/condition_cfg.hpp>

// QtConfFile include.
#include <QtConfFile/Utils>
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagVectorOfTags>
#include <QtConfFile/TagScalar>
#include <QtConfFile/ConstraintMinMax>
#include <QtConfFile/ConstraintOneOf>


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
	//! Insert new condition to the new place with \arg index.
	void insertCondition( const Condition & cond, int index );
	//! Remove condition with the \arg index.
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
	:	public QtConfFile::TagNoValue
{
public:
	PropertiesTag()
		:	QtConfFile::TagNoValue( QLatin1String( "properties" ), true )
		,	m_priority( *this, QLatin1String( "priority" ), false )
		,	m_conditions( *this, QLatin1String( "if" ), false )
		,	m_otherwise( *this, QLatin1String( "otherwise" ), false )
		,	m_priorityConstraint( 0, 999 )
	{
		m_priority.setConstraint( &m_priorityConstraint );
	}

	PropertiesTag( const Properties & properties )
		:	QtConfFile::TagNoValue( QLatin1String( "properties" ), true )
		,	m_priority( *this, QLatin1String( "priority" ), false )
		,	m_conditions( *this, QLatin1String( "if" ), false )
		,	m_otherwise( properties.otherwise(), *this,
				QLatin1String( "otherwise" ), false )
		,	m_priorityConstraint( 0, 999 )
	{
		m_priority.setConstraint( &m_priorityConstraint );

		if( properties.priority() > 0 )
			m_priority.setValue( properties.priority() );

		for( int i = 0; i < properties.conditionsAmount(); ++i )
		{
			QtConfFile::TagVectorOfTags< ConditionTag< T > >::PointerToTag tag(
				new ConditionTag< T >( properties.conditionAt( i ),
					QLatin1String( "if" ), true ) );

			m_conditions.setValue( tag );
		}

		setDefined();
	}

	Properties properties() const
	{
		Properties p;

		if( m_priority.isDefined() )
			p.setPriority( m_priority.value() );

		if( m_conditions.isDefined() )
		{
			for( int i = 0; i < m_conditions.size(); ++i )
				p.insertCondition( m_conditions.at( i ).condition(), i );
		}

		if( m_otherwise.isDefined() )
			p.otherwise() = m_otherwise.value();

		return p;
	}

private:
	//! Priority.
	QtConfFile::TagScalar< int > m_priority;
	//! Conditions.
	QtConfFile::TagVectorOfTags< ConditionTag< T > > m_conditions;
	//! Otherwise condition.
	OtherwiseTag m_otherwise;
	//! Constraint for the priority.
	QtConfFile::ConstraintMinMax< int > m_priorityConstraint;
}; // class PropertiesTag


//
// readPropertiesConfigurationTemplate
//

template< class T >
void
readPropertiesConfigurationTemplate( const QString & fileName, Properties & p )
{
	PropertiesTag< T > tag;

	QtConfFile::readQtConfFile( tag, fileName,
		QTextCodec::codecForName( "UTF-8" ) );

	p = tag.properties();
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

	QtConfFile::writeQtConfFile( tag, fileName,
		QTextCodec::codecForName( "UTF-8" ) );
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

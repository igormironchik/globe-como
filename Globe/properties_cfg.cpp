
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
#include <Globe/properties_cfg.hpp>


namespace Globe {


//
// PropertiesTag
//

PropertiesTag::PropertiesTag()
	:	QtConfFile::TagNoValue( QLatin1String( "properties" ), true )
	,	m_priority( *this, QLatin1String( "priority" ), false )
	,	m_conditions( *this, QLatin1String( "if" ), false )
	,	m_otherwise( *this, QLatin1String( "otherwise" ), false )
	,	m_priorityConstraint( 0, 999 )
{
	m_priority.setConstraint( &m_priorityConstraint );
}

PropertiesTag::PropertiesTag( const Properties & properties )
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
		QtConfFile::TagVectorOfTags< ConditionTag >::PointerToTag tag(
			new ConditionTag( properties.conditionAt( i ),
				QLatin1String( "if" ), true ) );

		m_conditions.setValue( tag );
	}

	setDefined();
}


Properties
PropertiesTag::properties() const
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


//
// PropertiesMapRecordTag
//

const QString intTypeName = QLatin1String( "int" );
const QString doubleTypeName = QLatin1String( "double" );
const QString stringTypeName = QLatin1String( "string" );

static inline QString valueTypeToString( Como::Source::Type type )
{
	if( type == Como::Source::Int )
		return intTypeName;
	else if( type == Como::Source::Double )
		return doubleTypeName;
	else
		return stringTypeName;
}

static inline Como::Source::Type valueTypeFromString( const QString & type )
{
	if( type == intTypeName )
		return Como::Source::Int;
	else if( type == doubleTypeName )
		return Como::Source::Double;
	else
		return Como::Source::String;
}

PropertiesMapRecordTag::PropertiesMapRecordTag( const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_sourceName( *this, QLatin1String( "sourceName" ), false )
	,	m_typeName( *this, QLatin1String( "sourceTypeName" ), true )
	,	m_channelName( *this, QLatin1String( "channelName" ), false )
	,	m_valueType( *this, QLatin1String( "valueType" ), true )
	,	m_confFileName( *this, QLatin1String( "confFileName" ), true )
{
	m_valueTypeConstraint.addValue( intTypeName );
	m_valueTypeConstraint.addValue( doubleTypeName );
	m_valueTypeConstraint.addValue( stringTypeName );

	m_valueType.setConstraint( &m_valueTypeConstraint );
}

PropertiesMapRecordTag::PropertiesMapRecordTag( const PropertiesKey & key,
	const PropertiesValue & value, const QString & name )
	:	QtConfFile::TagNoValue( name, false )
	,	m_sourceName( *this, QLatin1String( "sourceName" ), false )
	,	m_typeName( *this, QLatin1String( "sourceTypeName" ), true )
	,	m_channelName( *this, QLatin1String( "channelName" ), false )
	,	m_valueType( *this, QLatin1String( "valueType" ), true )
	,	m_confFileName( *this, QLatin1String( "confFileName" ), true )
{
	m_valueTypeConstraint.addValue( intTypeName );
	m_valueTypeConstraint.addValue( doubleTypeName );
	m_valueTypeConstraint.addValue( stringTypeName );

	m_valueType.setConstraint( &m_valueTypeConstraint );

	if( !key.name().isEmpty() )
		m_sourceName.setValue( key.name() );

	m_typeName.setValue( key.typeName() );

	if( !key.channelName().isEmpty() )
		m_channelName.setValue( key.channelName() );

	m_valueType.setValue( valueTypeToString( value.valueType() ) );
	m_confFileName.setValue( value.confFileName() );

	setDefined();
}

PropertiesKey
PropertiesMapRecordTag::key() const
{
	return PropertiesKey(
		m_sourceName.isDefined() ? m_sourceName.value() : QString(),
		m_typeName.value(),
		m_channelName.isDefined() ? m_channelName.value() : QString() );
}

PropertiesValue
PropertiesMapRecordTag::value() const
{
	Properties props;

	return PropertiesValue( m_confFileName.value(),
		valueTypeFromString( m_valueType.value() ),
		props );
}


//
// PropertiesManagerTag
//

PropertiesManagerTag::PropertiesManagerTag()
	:	QtConfFile::TagNoValue( QLatin1String( "propertiesManager" ), true )
	,	m_directory( *this, QLatin1String( "confDirectory" ), true )
	,	m_map( *this, QLatin1String( "record" ), false )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
{
}

PropertiesManagerTag::PropertiesManagerTag( const QString & propsPath,
	const PropertiesMap & map, const WindowStateCfg & windowState )
	:	QtConfFile::TagNoValue( QLatin1String( "propertiesManager" ), true )
	,	m_directory( *this, QLatin1String( "confDirectory" ), true )
	,	m_map( *this, QLatin1String( "record" ), false )
	,	m_windowState( windowState, *this, QLatin1String( "windowState" ), true )
{
	m_directory.setValue( propsPath );

	for( PropertiesMap::ConstIterator it = map.begin(),
		last = map.end(); it != last; ++it )
	{
		QtConfFile::TagVectorOfTags< PropertiesMapRecordTag >::PointerToTag p(
			new PropertiesMapRecordTag( it.key(), it.value(),
				QLatin1String( "record" ) ) );

		m_map.setValue( p );
	}

	setDefined();
}

QString
PropertiesManagerTag::propertiesDirectory() const
{
	return m_directory.value();
}

PropertiesMap
PropertiesManagerTag::propertiesMap() const
{
	PropertiesMap map;

	const int propsSize = m_map.size();

	for( int i = 0; i < propsSize; ++i )
	{
		const PropertiesMapRecordTag & tag = m_map.at( i );

		const PropertiesKey key = tag.key();
		const PropertiesValue value = tag.value();

		map.insert( key, value );
	}

	return map;
}

WindowStateCfg
PropertiesManagerTag::windowState() const
{
	return m_windowState.cfg();
}

} /* namespace Globe */

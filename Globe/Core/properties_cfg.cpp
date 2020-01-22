
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
#include <Globe/Core/properties_cfg.hpp>
#include <Globe/Core/utils.hpp>


namespace Globe {

//
// PropertiesMapRecordTag
//

PropertiesMapRecordTag::PropertiesMapRecordTag( const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			name, isMandatory )
	,	m_sourceName( *this, QLatin1String( "sourceName" ), false )
	,	m_typeName( *this, QLatin1String( "sourceTypeName" ), true )
	,	m_channelName( *this, QLatin1String( "channelName" ), false )
	,	m_valueType( *this, QLatin1String( "valueType" ), true )
	,	m_confFileName( *this, QLatin1String( "confFileName" ), true )
{
	m_valueTypeConstraint.add_value( comoSourceIntType );
	m_valueTypeConstraint.add_value( comoSourceUIntType );
	m_valueTypeConstraint.add_value( comoSourceLongLongType );
	m_valueTypeConstraint.add_value( comoSourceULongLongType );
	m_valueTypeConstraint.add_value( comoSourceDoubleType );
	m_valueTypeConstraint.add_value( comoSourceStringType );
	m_valueTypeConstraint.add_value( comoSourceDateTimeType );
	m_valueTypeConstraint.add_value( comoSourceTimeType );

	m_valueType.set_constraint( &m_valueTypeConstraint );
}

PropertiesMapRecordTag::PropertiesMapRecordTag( const PropertiesKey & key,
	const PropertiesValue & value, const QString & name )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > ( name, false )
	,	m_sourceName( *this, QLatin1String( "sourceName" ), false )
	,	m_typeName( *this, QLatin1String( "sourceTypeName" ), true )
	,	m_channelName( *this, QLatin1String( "channelName" ), false )
	,	m_valueType( *this, QLatin1String( "valueType" ), true )
	,	m_confFileName( *this, QLatin1String( "confFileName" ), true )
{
	m_valueTypeConstraint.add_value( comoSourceIntType );
	m_valueTypeConstraint.add_value( comoSourceUIntType );
	m_valueTypeConstraint.add_value( comoSourceLongLongType );
	m_valueTypeConstraint.add_value( comoSourceULongLongType );
	m_valueTypeConstraint.add_value( comoSourceDoubleType );
	m_valueTypeConstraint.add_value( comoSourceStringType );
	m_valueTypeConstraint.add_value( comoSourceDateTimeType );
	m_valueTypeConstraint.add_value( comoSourceTimeType );

	m_valueType.set_constraint( &m_valueTypeConstraint );

	if( !key.name().isEmpty() )
		m_sourceName.set_value( key.name() );

	m_typeName.set_value( key.typeName() );

	if( !key.channelName().isEmpty() )
		m_channelName.set_value( key.channelName() );

	m_valueType.set_value( comoSourceTypeToString( value.valueType() ) );
	m_confFileName.set_value( value.confFileName() );

	set_defined();
}

PropertiesKey
PropertiesMapRecordTag::key() const
{
	return PropertiesKey(
		m_sourceName.is_defined() ? m_sourceName.value() : QString(),
		m_typeName.value(),
		m_channelName.is_defined() ? m_channelName.value() : QString() );
}

PropertiesValue
PropertiesMapRecordTag::value() const
{
	Properties props;

	return PropertiesValue( m_confFileName.value(),
		stringToComoSourceType( m_valueType.value() ),
		props );
}


//
// PropertiesManagerTag
//

PropertiesManagerTag::PropertiesManagerTag()
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "propertiesManager" ), true )
	,	m_directory( *this, QLatin1String( "confDirectory" ), true )
	,	m_map( *this, QLatin1String( "record" ), false )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
{
}

PropertiesManagerTag::PropertiesManagerTag( const QString & propsPath,
	const PropertiesMap & exactlyThisSourceMap,
	const PropertiesMap & exactlyThisSourceInAnyChannelMap,
	const PropertiesMap & exactlyThisTypeOfSourceMap,
	const PropertiesMap & exactlyThisTypeOfSourceInAnyChannelMap,
	const WindowStateCfg & windowState )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "propertiesManager" ), true )
	,	m_directory( *this, QLatin1String( "confDirectory" ), true )
	,	m_map( *this, QLatin1String( "record" ), false )
	,	m_windowState( windowState, *this, QLatin1String( "windowState" ), true )
{
	m_directory.set_value( propsPath );

	for( PropertiesMap::ConstIterator it = exactlyThisSourceMap.begin(),
		last = exactlyThisSourceMap.end(); it != last; ++it )
	{
		cfgfile::tag_vector_of_tags_t< PropertiesMapRecordTag,
			cfgfile::qstring_trait_t >::ptr_to_tag_t p(
				new PropertiesMapRecordTag( it.key(), it.value(),
					QLatin1String( "record" ) ) );

		m_map.set_value( p );
	}

	for( PropertiesMap::ConstIterator it = exactlyThisSourceInAnyChannelMap.begin(),
		last = exactlyThisSourceInAnyChannelMap.end(); it != last; ++it )
	{
		cfgfile::tag_vector_of_tags_t< PropertiesMapRecordTag,
			cfgfile::qstring_trait_t >::ptr_to_tag_t p(
				new PropertiesMapRecordTag( it.key(), it.value(),
					QLatin1String( "record" ) ) );

		m_map.set_value( p );
	}

	for( PropertiesMap::ConstIterator it = exactlyThisTypeOfSourceMap.begin(),
		last = exactlyThisTypeOfSourceMap.end(); it != last; ++it )
	{
		cfgfile::tag_vector_of_tags_t< PropertiesMapRecordTag,
			cfgfile::qstring_trait_t >::ptr_to_tag_t p(
				new PropertiesMapRecordTag( it.key(), it.value(),
					QLatin1String( "record" ) ) );

		m_map.set_value( p );
	}

	for( PropertiesMap::ConstIterator it = exactlyThisTypeOfSourceInAnyChannelMap.begin(),
		last = exactlyThisTypeOfSourceInAnyChannelMap.end(); it != last; ++it )
	{
		cfgfile::tag_vector_of_tags_t< PropertiesMapRecordTag,
			cfgfile::qstring_trait_t >::ptr_to_tag_t p(
				new PropertiesMapRecordTag( it.key(), it.value(),
					QLatin1String( "record" ) ) );

		m_map.set_value( p );
	}

	set_defined();
}

QString
PropertiesManagerTag::propertiesDirectory() const
{
	return m_directory.value();
}

PropertiesMap
PropertiesManagerTag::exactlyThisSourceMap() const
{
	PropertiesMap map;

	const int propsSize = static_cast< int > ( m_map.size() );

	for( int i = 0; i < propsSize; ++i )
	{
		const PropertiesMapRecordTag & tag = m_map.at( i );

		const PropertiesKey key = tag.key();

		if( key.keyType() == ExactlyThisSource )
			map.insert( key, tag.value() );
	}

	return map;
}

PropertiesMap
PropertiesManagerTag::exactlyThisSourceInAnyChannelMap() const
{
	PropertiesMap map;

	const int propsSize = static_cast< int > ( m_map.size() );

	for( int i = 0; i < propsSize; ++i )
	{
		const PropertiesMapRecordTag & tag = m_map.at( i );

		const PropertiesKey key = tag.key();

		if( key.keyType() == ExactlyThisSourceInAnyChannel )
			map.insert( key, tag.value() );
	}

	return map;
}

PropertiesMap
PropertiesManagerTag::exactlyThisTypeOfSourceMap() const
{
	PropertiesMap map;

	const int propsSize = static_cast< int > ( m_map.size() );

	for( int i = 0; i < propsSize; ++i )
	{
		const PropertiesMapRecordTag & tag = m_map.at( i );

		const PropertiesKey key = tag.key();

		if( key.keyType() == ExactlyThisTypeOfSource )
			map.insert( key, tag.value() );
	}

	return map;
}

PropertiesMap
PropertiesManagerTag::exactlyThisTypeOfSourceInAnyChannelMap() const
{
	PropertiesMap map;

	const int propsSize = static_cast< int > ( m_map.size() );

	for( int i = 0; i < propsSize; ++i )
	{
		const PropertiesMapRecordTag & tag = m_map.at( i );

		const PropertiesKey key = tag.key();

		if( key.keyType() == ExactlyThisTypeOfSourceInAnyChannel )
			map.insert( key, tag.value() );
	}

	return map;
}

WindowStateCfg
PropertiesManagerTag::windowState() const
{
	return m_windowState.cfg();
}

} /* namespace Globe */

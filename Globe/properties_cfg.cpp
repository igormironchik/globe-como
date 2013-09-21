
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
#include <Globe/utils.hpp>


namespace Globe {

//
// PropertiesMapRecordTag
//

PropertiesMapRecordTag::PropertiesMapRecordTag( const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_sourceName( *this, QLatin1String( "sourceName" ), false )
	,	m_typeName( *this, QLatin1String( "sourceTypeName" ), true )
	,	m_channelName( *this, QLatin1String( "channelName" ), false )
	,	m_valueType( *this, QLatin1String( "valueType" ), true )
	,	m_confFileName( *this, QLatin1String( "confFileName" ), true )
{
	m_valueTypeConstraint.addValue( comoSourceIntType );
	m_valueTypeConstraint.addValue( comoSourceUIntType );
	m_valueTypeConstraint.addValue( comoSourceLongLongType );
	m_valueTypeConstraint.addValue( comoSourceULongLongType );
	m_valueTypeConstraint.addValue( comoSourceDoubleType );
	m_valueTypeConstraint.addValue( comoSourceStringType );
	m_valueTypeConstraint.addValue( comoSourceDateTimeType );
	m_valueTypeConstraint.addValue( comoSourceTimeType );

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
	m_valueTypeConstraint.addValue( comoSourceIntType );
	m_valueTypeConstraint.addValue( comoSourceUIntType );
	m_valueTypeConstraint.addValue( comoSourceLongLongType );
	m_valueTypeConstraint.addValue( comoSourceULongLongType );
	m_valueTypeConstraint.addValue( comoSourceDoubleType );
	m_valueTypeConstraint.addValue( comoSourceStringType );
	m_valueTypeConstraint.addValue( comoSourceDateTimeType );
	m_valueTypeConstraint.addValue( comoSourceTimeType );

	m_valueType.setConstraint( &m_valueTypeConstraint );

	if( !key.name().isEmpty() )
		m_sourceName.setValue( key.name() );

	m_typeName.setValue( key.typeName() );

	if( !key.channelName().isEmpty() )
		m_channelName.setValue( key.channelName() );

	m_valueType.setValue( comoSourceTypeToString( value.valueType() ) );
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
		stringToComoSourceType( m_valueType.value() ),
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
	const PropertiesMap & exactlyThisSourceMap,
	const PropertiesMap & exactlyThisSourceInAnyChannelMap,
	const PropertiesMap & exactlyThisTypeOfSourceMap,
	const PropertiesMap & exactlyThisTypeOfSourceInAnyChannelMap,
	const WindowStateCfg & windowState )
	:	QtConfFile::TagNoValue( QLatin1String( "propertiesManager" ), true )
	,	m_directory( *this, QLatin1String( "confDirectory" ), true )
	,	m_map( *this, QLatin1String( "record" ), false )
	,	m_windowState( windowState, *this, QLatin1String( "windowState" ), true )
{
	m_directory.setValue( propsPath );

	for( PropertiesMap::ConstIterator it = exactlyThisSourceMap.begin(),
		last = exactlyThisSourceMap.end(); it != last; ++it )
	{
		QtConfFile::TagVectorOfTags< PropertiesMapRecordTag >::PointerToTag p(
			new PropertiesMapRecordTag( it.key(), it.value(),
				QLatin1String( "record" ) ) );

		m_map.setValue( p );
	}

	for( PropertiesMap::ConstIterator it = exactlyThisSourceInAnyChannelMap.begin(),
		last = exactlyThisSourceInAnyChannelMap.end(); it != last; ++it )
	{
		QtConfFile::TagVectorOfTags< PropertiesMapRecordTag >::PointerToTag p(
			new PropertiesMapRecordTag( it.key(), it.value(),
				QLatin1String( "record" ) ) );

		m_map.setValue( p );
	}

	for( PropertiesMap::ConstIterator it = exactlyThisTypeOfSourceMap.begin(),
		last = exactlyThisTypeOfSourceMap.end(); it != last; ++it )
	{
		QtConfFile::TagVectorOfTags< PropertiesMapRecordTag >::PointerToTag p(
			new PropertiesMapRecordTag( it.key(), it.value(),
				QLatin1String( "record" ) ) );

		m_map.setValue( p );
	}

	for( PropertiesMap::ConstIterator it = exactlyThisTypeOfSourceInAnyChannelMap.begin(),
		last = exactlyThisTypeOfSourceInAnyChannelMap.end(); it != last; ++it )
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
PropertiesManagerTag::exactlyThisSourceMap() const
{
	PropertiesMap map;

	const int propsSize = m_map.size();

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

	const int propsSize = m_map.size();

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

	const int propsSize = m_map.size();

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

	const int propsSize = m_map.size();

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

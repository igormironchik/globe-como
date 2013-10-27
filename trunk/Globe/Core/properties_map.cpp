
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
#include <Globe/Core/properties_map.hpp>


namespace Globe {

//
// PropertiesKey
//

PropertiesKey::PropertiesKey()
	:	m_keyType( NotDefinedKeyType )
{
}

PropertiesKey::PropertiesKey( const QString & name,
	const QString & typeName, const QString & channelName )
	:	m_name( name )
	,	m_typeName( typeName )
	,	m_channelName( channelName )
	,	m_keyType( NotDefinedKeyType )
{
	if( m_channelName.isEmpty() && m_name.isEmpty() )
		m_keyType = ExactlyThisTypeOfSourceInAnyChannel;
	else if( m_name.isEmpty() )
		m_keyType = ExactlyThisTypeOfSource;
	else if( m_channelName.isEmpty() )
		m_keyType = ExactlyThisSourceInAnyChannel;
	else
		m_keyType = ExactlyThisSource;
}

PropertiesKey::PropertiesKey( const PropertiesKey & other )
	:	m_name( other.name() )
	,	m_typeName( other.typeName() )
	,	m_channelName( other.channelName() )
	,	m_keyType( other.keyType() )
{
}

PropertiesKey &
PropertiesKey::operator = ( const PropertiesKey & other )
{
	if( this != &other )
	{
		m_name = other.name();
		m_typeName = other.typeName();
		m_channelName = other.channelName();
		m_keyType = other.keyType();
	}

	return *this;
}

const QString &
PropertiesKey::name() const
{
	return m_name;
}

const QString &
PropertiesKey::typeName() const
{
	return m_typeName;
}

const QString &
PropertiesKey::channelName() const
{
	return m_channelName;
}

PropertiesKeyType
PropertiesKey::keyType() const
{
	return m_keyType;
}

bool operator < ( const PropertiesKey & k1, const PropertiesKey & k2 )
{
	switch( k1.keyType() )
	{
		case ExactlyThisSource :
			return ( ( k1.name() + k1.typeName() + k1.channelName() ) <
				( k2.name() + k2.typeName() + k2.channelName() ) );
		case ExactlyThisSourceInAnyChannel :
			return ( ( k1.name() + k1.typeName() ) <
			( k2.name() + k2.typeName() ) );
		case ExactlyThisTypeOfSource :
			return ( ( k1.typeName() + k1.channelName() ) <
			( k2.typeName() + k2.channelName() ) );
		case ExactlyThisTypeOfSourceInAnyChannel :
			return ( k1.typeName() < k2.typeName() );

		default : return false;
	}
}

bool operator == ( const PropertiesKey & k1, const PropertiesKey & k2 )
{
	return ( k1.name() == k2.name() &&
		k1.typeName() == k2.typeName() &&
		k1.channelName() == k2.channelName() );
}


//
// PropertiesValue
//

PropertiesValue::PropertiesValue()
	:	m_valueType( Como::Source::String )
{
}

PropertiesValue::PropertiesValue( const QString & confFileName,
	const Como::Source::Type & type,
	const Properties & props )
	:	m_confFileName( confFileName )
	,	m_valueType( type )
	,	m_properties( props )
{
}

PropertiesValue::PropertiesValue( const PropertiesValue & other )
	:	m_confFileName( other.confFileName() )
	,	m_valueType( other.valueType() )
	,	m_properties( other.properties() )
{
}

PropertiesValue &
PropertiesValue::operator = ( const PropertiesValue & other )
{
	if( this != &other )
	{
		m_confFileName = other.confFileName();
		m_valueType = other.valueType();
		m_properties = other.properties();
	}

	return *this;
}

const QString &
PropertiesValue::confFileName() const
{
	return m_confFileName;
}

Como::Source::Type
PropertiesValue::valueType() const
{
	return m_valueType;
}

Properties &
PropertiesValue::properties()
{
	return m_properties;
}

const Properties &
PropertiesValue::properties() const
{
	return m_properties;
}

} /* namespace Globe */


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
#include <Globe/sounds_disabled_cfg.hpp>
#include <Globe/utils.hpp>


namespace Globe {

//
// DisabledSoundsCfg
//

DisabledSoundsCfg::DisabledSoundsCfg()
{
}

DisabledSoundsCfg::DisabledSoundsCfg( const DisabledSoundsCfg & other )
	:	m_map( other.map() )
{
}

DisabledSoundsCfg &
DisabledSoundsCfg::operator = ( const DisabledSoundsCfg & other )
{
	if( this != &other )
	{
		m_map = other.map();
	}

	return *this;
}

const DisabledSoundsMap &
DisabledSoundsCfg::map() const
{
	return m_map;
}

void
DisabledSoundsCfg::setMap( const DisabledSoundsMap & m )
{
	m_map = m;
}


//
// DateTimeTag
//


DateTimeTag::DateTimeTag( QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_year( *this, QLatin1String( "year" ), true )
	,	m_yearConstraint( 1, 9999 )
	,	m_month( *this, QLatin1String( "month" ), true )
	,	m_monthConstraint( 1, 12 )
	,	m_day( *this, QLatin1String( "day" ), true )
	,	m_dayConstraint( 1, 31 )
	,	m_hour( *this, QLatin1String( "haour" ), true )
	,	m_hourConstraint( 0, 23 )
	,	m_minute( *this, QLatin1String( "minute" ), true )
	,	m_minuteConstraint( 0, 59 )
{
	m_year.setConstraint( &m_yearConstraint );
	m_month.setConstraint( &m_monthConstraint );
	m_day.setConstraint( &m_dayConstraint );
	m_hour.setConstraint( &m_hourConstraint );
	m_minute.setConstraint( &m_minuteConstraint );
}

DateTimeTag::DateTimeTag( const QDateTime & dt,
	QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_year( *this, QLatin1String( "year" ), true )
	,	m_yearConstraint( 1, 9999 )
	,	m_month( *this, QLatin1String( "month" ), true )
	,	m_monthConstraint( 1, 12 )
	,	m_day( *this, QLatin1String( "day" ), true )
	,	m_dayConstraint( 1, 31 )
	,	m_hour( *this, QLatin1String( "haour" ), true )
	,	m_hourConstraint( 0, 23 )
	,	m_minute( *this, QLatin1String( "minute" ), true )
	,	m_minuteConstraint( 0, 59 )
{
	m_year.setConstraint( &m_yearConstraint );
	m_month.setConstraint( &m_monthConstraint );
	m_day.setConstraint( &m_dayConstraint );
	m_hour.setConstraint( &m_hourConstraint );
	m_minute.setConstraint( &m_minuteConstraint );

	m_year.setValue( dt.date().year() );
	m_month.setValue( dt.date().month() );
	m_day.setValue( dt.date().day() );
	m_hour.setValue( dt.time().hour() );
	m_minute.setValue( dt.time().minute() );

	setDefined();
}

QDateTime
DateTimeTag::dateTime() const
{
	const QDate date( m_year.value(), m_month.value(), m_day.value() );
	const QTime time( m_hour.value(), m_minute.value() );

	return QDateTime( date, time );
}


//
// SourceAndDateTimeTag
//

SourceAndDateTimeTag::SourceAndDateTimeTag( const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_type( *this, QLatin1String( "type" ), true )
	,	m_name( *this, QLatin1String( "name" ), true )
	,	m_typeName( *this, QLatin1String( "typeName" ), true )
	,	m_dt( *this, QLatin1String( "dateTime" ), true )
{
	m_typeConstraint.addValue( comoSourceIntType );
	m_typeConstraint.addValue( comoSourceDoubleType );
	m_typeConstraint.addValue( comoSourceStringType );

	m_type.setConstraint( &m_typeConstraint );
}

SourceAndDateTimeTag::SourceAndDateTimeTag( const DisabledSoundsData & data,
	const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_type( *this, QLatin1String( "type" ), true )
	,	m_name( *this, QLatin1String( "name" ), true )
	,	m_typeName( *this, QLatin1String( "typeName" ), true )
	,	m_dt( data.dateTime(), *this, QLatin1String( "dateTime" ), true )
{
	m_typeConstraint.addValue( comoSourceIntType );
	m_typeConstraint.addValue( comoSourceDoubleType );
	m_typeConstraint.addValue( comoSourceStringType );

	m_type.setConstraint( &m_typeConstraint );

	m_type.setValue( comoSourceTypeToString( data.source().type() ) );
	m_name.setValue( data.source().name() );
	m_typeName.setValue( data.source().typeName() );

	setDefined();
}

DisabledSoundsData
SourceAndDateTimeTag::data() const
{
	const Como::Source source( stringToComoSourceType( m_type.value() ),
		m_name.value(), m_typeName.value(), QVariant(), QString() );

	return DisabledSoundsData( source, m_dt.dateTime() );
}



//
// DisabledSoundsInChannelTag
//

DisabledSoundsInChannelTag::DisabledSoundsInChannelTag( const QString & name,
	bool isMandatory )
	:	QtConfFile::TagScalar< QString > ( name, isMandatory )
	,	m_disabledSounds( *this, QLatin1String( "disabled" ), false )
{
}

DisabledSoundsInChannelTag::DisabledSoundsInChannelTag(
	const QString & channelName,
	const DisabledSoundsList & disabledSounds,
	const QString & name,
	bool isMandatory )
	:	QtConfFile::TagScalar< QString > ( name, isMandatory )
	,	m_disabledSounds( *this, QLatin1String( "disabledSound" ), false )
{
	foreach( const DisabledSoundsData & data, disabledSounds )
	{
		QtConfFile::TagVectorOfTags< SourceAndDateTimeTag >::PointerToTag p(
			new SourceAndDateTimeTag( data,
				QLatin1String( "disabledSound" ), true ) );

		m_disabledSounds.setValue( p );
	}

	setValue( channelName );
}

DisabledSoundsList
DisabledSoundsInChannelTag::disabledSounds() const
{
	DisabledSoundsList list;

	if( m_disabledSounds.isDefined() )
	{
		for( int i = 0; i < m_disabledSounds.size(); ++i )
			list.append( m_disabledSounds.at( i ).data() );
	}

	return list;
}

QString
DisabledSoundsInChannelTag::channelName() const
{
	return value();
}



//
// DisabledSoundsCfgTag
//

DisabledSoundsCfgTag::DisabledSoundsCfgTag()
	:	QtConfFile::TagNoValue( QLatin1String( "disabledSoundsCfg" ), true )
	,	m_map( *this, QLatin1String( "channel" ), false )
{
}

DisabledSoundsCfgTag::DisabledSoundsCfgTag( const DisabledSoundsCfg & cfg )
	:	QtConfFile::TagNoValue( QLatin1String( "disabledSoundsCfg" ), true )
	,	m_map( *this, QLatin1String( "channel" ), false )
{
	for( DisabledSoundsMap::ConstIterator it = cfg.map().begin(),
		last = cfg.map().end(); it != last; ++it )
	{
		QtConfFile::TagVectorOfTags< DisabledSoundsInChannelTag >::PointerToTag p(
			new DisabledSoundsInChannelTag( it.key(), it.value(),
				QLatin1String( "channel" ), true ) );

		m_map.setValue( p );
	}

	setDefined();
}

DisabledSoundsCfg
DisabledSoundsCfgTag::cfg() const
{
	DisabledSoundsCfg cfg;

	if( m_map.isDefined() )
	{
		DisabledSoundsMap map;

		for( int i = 0; i < m_map.size(); ++i )
			map.insert( m_map.at( i ).channelName(),
				m_map.at( i ).disabledSounds() );

		cfg.setMap( map );
	}

	return cfg;
}


} /* namespace Globe */

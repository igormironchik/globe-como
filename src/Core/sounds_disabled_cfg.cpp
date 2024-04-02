
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/sounds_disabled_cfg.hpp>
#include <Core/utils.hpp>


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


DateTimeTag::DateTimeTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
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
	m_year.set_constraint( &m_yearConstraint );
	m_month.set_constraint( &m_monthConstraint );
	m_day.set_constraint( &m_dayConstraint );
	m_hour.set_constraint( &m_hourConstraint );
	m_minute.set_constraint( &m_minuteConstraint );
}

DateTimeTag::DateTimeTag( const QDateTime & dt,
	cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
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
	m_year.set_constraint( &m_yearConstraint );
	m_month.set_constraint( &m_monthConstraint );
	m_day.set_constraint( &m_dayConstraint );
	m_hour.set_constraint( &m_hourConstraint );
	m_minute.set_constraint( &m_minuteConstraint );

	m_year.set_value( dt.date().year() );
	m_month.set_value( dt.date().month() );
	m_day.set_value( dt.date().day() );
	m_hour.set_value( dt.time().hour() );
	m_minute.set_value( dt.time().minute() );

	set_defined();
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
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > ( name, isMandatory )
	,	m_type( *this, QLatin1String( "type" ), true )
	,	m_name( *this, QLatin1String( "name" ), true )
	,	m_typeName( *this, QLatin1String( "typeName" ), true )
	,	m_dt( *this, QLatin1String( "dateTime" ), true )
{
	m_typeConstraint.add_value( comoSourceIntType );
	m_typeConstraint.add_value( comoSourceUIntType );
	m_typeConstraint.add_value( comoSourceLongLongType );
	m_typeConstraint.add_value( comoSourceULongLongType );
	m_typeConstraint.add_value( comoSourceDoubleType );
	m_typeConstraint.add_value( comoSourceStringType );
	m_typeConstraint.add_value( comoSourceDateTimeType );
	m_typeConstraint.add_value( comoSourceTimeType );

	m_type.set_constraint( &m_typeConstraint );
}

SourceAndDateTimeTag::SourceAndDateTimeTag( const DisabledSoundsData & data,
	const QString & name, bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > ( name, isMandatory )
	,	m_type( *this, QLatin1String( "type" ), true )
	,	m_name( *this, QLatin1String( "name" ), true )
	,	m_typeName( *this, QLatin1String( "typeName" ), true )
	,	m_dt( data.dateTime(), *this, QLatin1String( "dateTime" ), true )
{
	m_typeConstraint.add_value( comoSourceIntType );
	m_typeConstraint.add_value( comoSourceUIntType );
	m_typeConstraint.add_value( comoSourceLongLongType );
	m_typeConstraint.add_value( comoSourceULongLongType );
	m_typeConstraint.add_value( comoSourceDoubleType );
	m_typeConstraint.add_value( comoSourceStringType );
	m_typeConstraint.add_value( comoSourceDateTimeType );
	m_typeConstraint.add_value( comoSourceTimeType );

	m_type.set_constraint( &m_typeConstraint );

	m_type.set_value( comoSourceTypeToString( data.source().type() ) );
	m_name.set_value( data.source().name() );
	m_typeName.set_value( data.source().typeName() );

	set_defined();
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
	:	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > ( name, isMandatory )
	,	m_disabledSounds( *this, QLatin1String( "disabledSound" ), false )
{
}

DisabledSoundsInChannelTag::DisabledSoundsInChannelTag(
	const QString & channelName,
	const DisabledSoundsList & disabledSounds,
	const QString & name,
	bool isMandatory )
	:	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > ( name, isMandatory )
	,	m_disabledSounds( *this, QLatin1String( "disabledSound" ), false )
{
	foreach( const DisabledSoundsData & data, disabledSounds )
	{
		cfgfile::tag_vector_of_tags_t< SourceAndDateTimeTag,
			cfgfile::qstring_trait_t >::ptr_to_tag_t p(
				new SourceAndDateTimeTag( data,
					QLatin1String( "disabledSound" ), true ) );

		m_disabledSounds.set_value( p );
	}

	set_value( channelName );
}

DisabledSoundsList
DisabledSoundsInChannelTag::disabledSounds() const
{
	DisabledSoundsList list;

	if( m_disabledSounds.is_defined() )
	{
		for( std::size_t i = 0; i < m_disabledSounds.size(); ++i )
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
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "disabledSoundsCfg" ), true )
	,	m_map( *this, QLatin1String( "channel" ), false )
{
}

DisabledSoundsCfgTag::DisabledSoundsCfgTag( const DisabledSoundsCfg & cfg )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "disabledSoundsCfg" ), true )
	,	m_map( *this, QLatin1String( "channel" ), false )
{
	for( DisabledSoundsMap::ConstIterator it = cfg.map().begin(),
		last = cfg.map().end(); it != last; ++it )
	{
		cfgfile::tag_vector_of_tags_t< DisabledSoundsInChannelTag,
			cfgfile::qstring_trait_t >::ptr_to_tag_t p(
				new DisabledSoundsInChannelTag( it.key(), it.value(),
					QLatin1String( "channel" ), true ) );

		m_map.set_value( p );
	}

	set_defined();
}

DisabledSoundsCfg
DisabledSoundsCfgTag::cfg() const
{
	DisabledSoundsCfg cfg;

	if( m_map.is_defined() )
	{
		DisabledSoundsMap map;

		for( std::size_t i = 0; i < m_map.size(); ++i )
			map.insert( m_map.at( i ).channelName(),
				m_map.at( i ).disabledSounds() );

		cfg.setMap( map );
	}

	return cfg;
}


} /* namespace Globe */

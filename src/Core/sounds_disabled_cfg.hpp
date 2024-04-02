
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SOUNDS_DISABLED_CFG_HPP__INCLUDED
#define GLOBE__SOUNDS_DISABLED_CFG_HPP__INCLUDED

// Globe include.
#include <Core/sounds_disabled_data.hpp>

// cfgfile include.
#include <cfgfile/all.hpp>


namespace Globe {

//
// DisabledSoundsCfg
//

//! Configuration of the disabled sounds.
class DisabledSoundsCfg {
public:
	DisabledSoundsCfg();

	DisabledSoundsCfg( const DisabledSoundsCfg & other );

	DisabledSoundsCfg & operator = ( const DisabledSoundsCfg & other );

	//! \return Map of disabled sounds.
	const DisabledSoundsMap & map() const;
	//! Set map of disabled sounds.
	void setMap( const DisabledSoundsMap & m );

private:
	//! Map of disabled sounds.
	DisabledSoundsMap m_map;
}; // class DisabledSoundsCfg


//
// DateTimeTag
//

//! Tag with date and time.
class DateTimeTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	DateTimeTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	DateTimeTag( const QDateTime & dt,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
		bool isMandatory = false );

	//! \return Date and time.
	QDateTime dateTime() const;

private:
	//! Year.
	cfgfile::tag_scalar_t< int, cfgfile::qstring_trait_t > m_year;
	//! Year's constraint.
	cfgfile::constraint_min_max_t< int > m_yearConstraint;
	//! Month.
	cfgfile::tag_scalar_t< int, cfgfile::qstring_trait_t > m_month;
	//! Month's constraint.
	cfgfile::constraint_min_max_t< int > m_monthConstraint;
	//! Day.
	cfgfile::tag_scalar_t< int, cfgfile::qstring_trait_t > m_day;
	//! Day's constraint.
	cfgfile::constraint_min_max_t< int > m_dayConstraint;
	//! Hour.
	cfgfile::tag_scalar_t< int, cfgfile::qstring_trait_t > m_hour;
	//! Hour's constraint.
	cfgfile::constraint_min_max_t< int > m_hourConstraint;
	//! Minute.
	cfgfile::tag_scalar_t< int, cfgfile::qstring_trait_t > m_minute;
	//! Minute's constraint.
	cfgfile::constraint_min_max_t< int > m_minuteConstraint;
}; // class DateTimeTag


//
// SourceAndDateTimeTag
//

//! Tag with Como source and date and time.
class SourceAndDateTimeTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	explicit SourceAndDateTimeTag( const QString & name,
		bool isMandatory = false );

	SourceAndDateTimeTag( const DisabledSoundsData & data,
		const QString & name, bool isMandatory = false );

	//! \return Data.
	DisabledSoundsData data() const;

private:
	//! Type of the source.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_type;
	//! Type of the source constraint.
	cfgfile::constraint_one_of_t< QString > m_typeConstraint;
	//! Name of the source.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_name;
	//! Type name of the source.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_typeName;
	//! Date and time.
	DateTimeTag m_dt;
}; // class SourceAndDateTimeTag


//
// DisabledSoundsInChannelTag
//

//! Disabled sounds in specified channel.
class DisabledSoundsInChannelTag
	:	public cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t >
{
public:
	explicit DisabledSoundsInChannelTag( const QString & name,
		bool isMandatory = false );

	DisabledSoundsInChannelTag( const QString & channelName,
		const DisabledSoundsList & disabledSounds,
		const QString & name,
		bool isMandatory = false );

	//! \return List of disabled sounds.
	DisabledSoundsList disabledSounds() const;

	//! \return Name of the channel.
	QString channelName() const;

private:
	//! Disabled sounds in channel.
	cfgfile::tag_vector_of_tags_t< SourceAndDateTimeTag,
		cfgfile::qstring_trait_t > m_disabledSounds;
}; // class DisabledSoundsInChannelTag


//
// DisabledSoundsCfgTag
//

//! Tag with configuration of disabled sounds.
class DisabledSoundsCfgTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	DisabledSoundsCfgTag();

	explicit DisabledSoundsCfgTag( const DisabledSoundsCfg & cfg );

	//! \return Configuration.
	DisabledSoundsCfg cfg() const;

private:
	//! Disabled sounds.
	cfgfile::tag_vector_of_tags_t< DisabledSoundsInChannelTag,
		cfgfile::qstring_trait_t > m_map;
}; // class DisabledSoundsCfgTag

} /* namespace Globe */

#endif // GLOBE__SOUNDS_DISABLED_CFG_HPP__INCLUDED


/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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

#ifndef GLOBE__SOUNDS_DISABLED_CFG_HPP__INCLUDED
#define GLOBE__SOUNDS_DISABLED_CFG_HPP__INCLUDED

// Globe include.
#include <Globe/Core/sounds_disabled_data.hpp>

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>
#include <QtConfFile/ConstraintMinMax>
#include <QtConfFile/TagVectorOfTags>
#include <QtConfFile/ConstraintOneOf>


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
	:	public QtConfFile::TagNoValue
{
public:
	DateTimeTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	DateTimeTag( const QDateTime & dt,
		QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	//! \return Date and time.
	QDateTime dateTime() const;

private:
	//! Year.
	QtConfFile::TagScalar< int > m_year;
	//! Year's constraint.
	QtConfFile::ConstraintMinMax< int > m_yearConstraint;
	//! Month.
	QtConfFile::TagScalar< int > m_month;
	//! Month's constraint.
	QtConfFile::ConstraintMinMax< int > m_monthConstraint;
	//! Day.
	QtConfFile::TagScalar< int > m_day;
	//! Day's constraint.
	QtConfFile::ConstraintMinMax< int > m_dayConstraint;
	//! Hour.
	QtConfFile::TagScalar< int > m_hour;
	//! Hour's constraint.
	QtConfFile::ConstraintMinMax< int > m_hourConstraint;
	//! Minute.
	QtConfFile::TagScalar< int > m_minute;
	//! Minute's constraint.
	QtConfFile::ConstraintMinMax< int > m_minuteConstraint;
}; // class DateTimeTag


//
// SourceAndDateTimeTag
//

//! Tag with Como source and date and time.
class SourceAndDateTimeTag
	:	public QtConfFile::TagNoValue
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
	QtConfFile::TagScalar< QString > m_type;
	//! Type of the source constraint.
	QtConfFile::ConstraintOneOf< QString > m_typeConstraint;
	//! Name of the source.
	QtConfFile::TagScalar< QString > m_name;
	//! Type name of the source.
	QtConfFile::TagScalar< QString > m_typeName;
	//! Date and time.
	DateTimeTag m_dt;
}; // class SourceAndDateTimeTag


//
// DisabledSoundsInChannelTag
//

//! Disabled sounds in specified channel.
class DisabledSoundsInChannelTag
	:	public QtConfFile::TagScalar< QString >
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
	QtConfFile::TagVectorOfTags< SourceAndDateTimeTag > m_disabledSounds;
}; // class DisabledSoundsInChannelTag


//
// DisabledSoundsCfgTag
//

//! Tag with configuration of disabled sounds.
class DisabledSoundsCfgTag
	:	public QtConfFile::TagNoValue
{
public:
	DisabledSoundsCfgTag();

	explicit DisabledSoundsCfgTag( const DisabledSoundsCfg & cfg );

	//! \return Configuration.
	DisabledSoundsCfg cfg() const;

private:
	//! Disabled sounds.
	QtConfFile::TagVectorOfTags< DisabledSoundsInChannelTag > m_map;
}; // class DisabledSoundsCfgTag

} /* namespace Globe */

#endif // GLOBE__SOUNDS_DISABLED_CFG_HPP__INCLUDED

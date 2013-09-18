
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

#ifndef GLOBE__SOUNDS_DISABLED_CFG_HPP__INCLUDED
#define GLOBE__SOUNDS_DISABLED_CFG_HPP__INCLUDED

// Globe include.
#include <Globe/sounds_disabled_data.hpp>

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


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/sounds_disabled_data.hpp>


namespace Globe {

//
// DisabledSoundsData
//

DisabledSoundsData::DisabledSoundsData()
{
}

DisabledSoundsData::DisabledSoundsData( const Como::Source & source,
	const QDateTime & dt )
	:	m_source( source )
	,	m_dt( dt )
{
}

DisabledSoundsData::DisabledSoundsData( const Como::Source & source )
	:	m_source( source )
{
}

DisabledSoundsData::DisabledSoundsData( const DisabledSoundsData & other )
	:	m_source( other.m_source )
	,	m_dt( other.m_dt )
{
}

DisabledSoundsData &
DisabledSoundsData::operator = ( const DisabledSoundsData & other )
{
	if( this != &other )
	{
		m_source = other.m_source;
		m_dt = other.m_dt;
	}

	return *this;
}

Como::Source &
DisabledSoundsData::source()
{
	return m_source;
}

const Como::Source &
DisabledSoundsData::source() const
{
	return m_source;
}

QDateTime &
DisabledSoundsData::dateTime()
{
	return m_dt;
}

const QDateTime &
DisabledSoundsData::dateTime() const
{
	return m_dt;
}

bool operator == ( const DisabledSoundsData & d1,
	const DisabledSoundsData & d2 )
{
	return ( d1.m_source == d2.m_source );
}

} /* namespace Globe */

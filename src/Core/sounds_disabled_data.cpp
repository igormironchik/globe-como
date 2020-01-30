
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

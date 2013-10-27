
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
#include <Globe/Core/sounds_disabled_data.hpp>


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

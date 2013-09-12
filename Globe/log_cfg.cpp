
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
#include <Globe/log_cfg.hpp>


namespace Globe {

//
// LogCfg
//

LogCfg::LogCfg()
	:	m_isEventLogEnabled( true )
	,	m_isSourcesLogEnabled( false )
	,	m_sourcesLogDays( 0 )
{
}

LogCfg::LogCfg( const LogCfg & other )
	:	m_isEventLogEnabled( other.isEventLogEnabled() )
	,	m_isSourcesLogEnabled( other.isSourcesLogEnabled() )
	,	m_sourcesLogDays( other.sourcesLogDays() )
{
}

LogCfg &
LogCfg::operator = ( const LogCfg & other )
{
	if( this != &other )
	{
		m_isEventLogEnabled = other.isEventLogEnabled();
		m_isSourcesLogEnabled = other.isSourcesLogEnabled();
		m_sourcesLogDays = other.sourcesLogDays();
	}

	return *this;
}

bool
LogCfg::isEventLogEnabled() const
{
	return m_isEventLogEnabled;
}

void
LogCfg::setEventLogEnabled( bool on )
{
	m_isEventLogEnabled = on;
}

bool
LogCfg::isSourcesLogEnabled() const
{
	return m_isSourcesLogEnabled;
}

void
LogCfg::setSourcesLogEnabled( bool on )
{
	m_isSourcesLogEnabled = on;
}

int
LogCfg::sourcesLogDays() const
{
	return m_sourcesLogDays;
}

void
LogCfg::setSourcesLogDays( int days )
{
	m_sourcesLogDays = days;
}


//
// LogTag
//

LogTag::LogTag()
	:	QtConfFile::TagNoValue( QLatin1String( "logCfg" ), true )
	,	m_isEventLogEnabled( *this, QLatin1String( "isEventLogEnabled" ), true )
	,	m_isSourcesLogEnabled( *this, QLatin1String( "isSourcesLogEnabled" ), true )
	,	m_sourcesLogDays( *this, QLatin1String( "sourcesLogDays" ), false )
{
}

LogTag::LogTag( const LogCfg & cfg )
	:	QtConfFile::TagNoValue( QLatin1String( "logCfg" ), true )
	,	m_isEventLogEnabled( *this, QLatin1String( "isEventLogEnabled" ), true )
	,	m_isSourcesLogEnabled( *this, QLatin1String( "isSourcesLogEnabled" ), true )
	,	m_sourcesLogDays( *this, QLatin1String( "sourcesLogDays" ), false )
{
	m_isEventLogEnabled.setValue( cfg.isEventLogEnabled() );
	m_isSourcesLogEnabled.setValue( cfg.isSourcesLogEnabled() );

	if( cfg.isSourcesLogEnabled() )
		m_sourcesLogDays.setValue( cfg.sourcesLogDays() );

	setDefined();
}

LogCfg
LogTag::cfg() const
{
	LogCfg cfg;

	cfg.setEventLogEnabled( m_isEventLogEnabled.value() );
	cfg.setSourcesLogEnabled( m_isSourcesLogEnabled.value() );

	if( cfg.isSourcesLogEnabled() )
		cfg.setSourcesLogDays( m_sourcesLogDays.value() );

	return cfg;
}

} /* namespace Globe */

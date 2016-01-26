
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

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
#include <Globe/Core/log_cfg.hpp>


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

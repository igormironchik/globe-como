
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/log_cfg.hpp>


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
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "logCfg" ), true )
	,	m_isEventLogEnabled( *this, QLatin1String( "isEventLogEnabled" ), true )
	,	m_isSourcesLogEnabled( *this, QLatin1String( "isSourcesLogEnabled" ), true )
	,	m_sourcesLogDays( *this, QLatin1String( "sourcesLogDays" ), false )
{
}

LogTag::LogTag( const LogCfg & cfg )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "logCfg" ), true )
	,	m_isEventLogEnabled( *this, QLatin1String( "isEventLogEnabled" ), true )
	,	m_isSourcesLogEnabled( *this, QLatin1String( "isSourcesLogEnabled" ), true )
	,	m_sourcesLogDays( *this, QLatin1String( "sourcesLogDays" ), false )
{
	m_isEventLogEnabled.set_value( cfg.isEventLogEnabled() );
	m_isSourcesLogEnabled.set_value( cfg.isSourcesLogEnabled() );

	if( cfg.isSourcesLogEnabled() )
		m_sourcesLogDays.set_value( cfg.sourcesLogDays() );

	set_defined();
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

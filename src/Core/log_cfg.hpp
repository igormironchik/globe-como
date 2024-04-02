
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__LOG_CFG_HPP__INCLUDED
#define GLOBE__LOG_CFG_HPP__INCLUDED

// cfgfile include.
#include <cfgfile/all.hpp>


namespace Globe {

//
// LogCfg
//

//! Configuration of the log.
class LogCfg {
public:
	LogCfg();

	LogCfg( const LogCfg & other );

	LogCfg & operator = ( const LogCfg & other );

	//! \return Is event's log enabled?
	bool isEventLogEnabled() const;
	//! Set is event's log enabled.
	void setEventLogEnabled( bool on = true );

	//! \return Is source's log enabled?
	bool isSourcesLogEnabled() const;
	//! Set is source's log enabled.
	void setSourcesLogEnabled( bool on = true );

	//! \return Number of days of the source's log.
	int sourcesLogDays() const;
	//! Set number of the source's log days.
	void setSourcesLogDays( int days );

private:
	//! Is event's log enabled?
	bool m_isEventLogEnabled;
	//! Is source's log enabled?
	bool m_isSourcesLogEnabled;
	//! Number of days of the source's log.
	//! 0 = ongoing log.
	int m_sourcesLogDays;
}; // class LogCfg


//
// LogTag
//

//! Tag with configuration of the log.
class LogTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	LogTag();

	explicit LogTag( const LogCfg & cfg );

	//! \return Configuration of the log.
	LogCfg cfg() const;

private:
	//! Is event's log enabled tag?
	cfgfile::tag_scalar_t< bool, cfgfile::qstring_trait_t > m_isEventLogEnabled;
	//! Is source's log enabled?
	cfgfile::tag_scalar_t< bool, cfgfile::qstring_trait_t > m_isSourcesLogEnabled;
	//! Number of days of the source's log.
	cfgfile::tag_scalar_t< int, cfgfile::qstring_trait_t > m_sourcesLogDays;
}; // class LogTag

} /* namespace Globe */

#endif // GLOBE__LOG_CFG_HPP__INCLUDED

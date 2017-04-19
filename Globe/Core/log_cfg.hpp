
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

#ifndef GLOBE__LOG_CFG_HPP__INCLUDED
#define GLOBE__LOG_CFG_HPP__INCLUDED

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>


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
	:	public QtConfFile::TagNoValue
{
public:
	LogTag();

	explicit LogTag( const LogCfg & cfg );

	//! \return Configuration of the log.
	LogCfg cfg() const;

private:
	//! Is event's log enabled tag?
	QtConfFile::TagScalar< bool > m_isEventLogEnabled;
	//! Is source's log enabled?
	QtConfFile::TagScalar< bool > m_isSourcesLogEnabled;
	//! Number of days of the source's log.
	QtConfFile::TagScalar< int > m_sourcesLogDays;
}; // class LogTag

} /* namespace Globe */

#endif // GLOBE__LOG_CFG_HPP__INCLUDED

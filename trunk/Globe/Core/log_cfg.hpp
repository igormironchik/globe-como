
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

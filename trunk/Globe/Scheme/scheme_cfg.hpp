
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

#ifndef GLOBE__SCHEME__SCHEME_CFG__INCLUDED
#define GLOBE__SCHEME__SCHEME_CFG__INCLUDED

// Globe include.
#include <Globe/Scheme/source_cfg.hpp>

// Qt include.
#include <QList>

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagVectorOfTags>


namespace Globe {

namespace Scheme {

//
// SchemeCfg
//

//! Scheme configuration.
class SchemeCfg {
public:
	SchemeCfg();

	SchemeCfg( const QList< SourceCfg > & sources );

	SchemeCfg( const SchemeCfg & other );

	SchemeCfg & operator = ( const SchemeCfg & other );

	//! \return Sources.
	const QList< SourceCfg > & sources() const;
	//! Set sources.
	void setSources( const QList< SourceCfg > & s );

private:
	//! Sources.
	QList< SourceCfg > m_sources;
}; // class SchemeCfg


//
// SchemeCfgTag
//

//! Tag with scheme configuration.
class SchemeCfgTag
	:	public QtConfFile::TagNoValue
{
public:
	SchemeCfgTag();

	explicit SchemeCfgTag( const SchemeCfg & cfg );

	//! \return Configuration.
	SchemeCfg cfg() const;

private:
	//! Sources.
	QtConfFile::TagVectorOfTags< SourceCfgTag > m_sources;
}; // class SchemeCfgTag

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__SCHEME_CFG__INCLUDED

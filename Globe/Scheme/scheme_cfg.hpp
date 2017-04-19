
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

#ifndef GLOBE__SCHEME__SCHEME_CFG__INCLUDED
#define GLOBE__SCHEME__SCHEME_CFG__INCLUDED

// Globe include.
#include <Globe/Scheme/source_cfg.hpp>
#include <Globe/Scheme/text_cfg.hpp>

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

	SchemeCfg( const QList< SourceCfg > & sources,
		const QList< TextCfg > & texts );

	SchemeCfg( const SchemeCfg & other );

	SchemeCfg & operator = ( const SchemeCfg & other );

	//! \return Sources.
	const QList< SourceCfg > & sources() const;
	//! Set sources.
	void setSources( const QList< SourceCfg > & s );

	//! \return Texts.
	const QList< TextCfg > & texts() const;
	//! Set texts.
	void setTexts( const QList< TextCfg > & t );

private:
	//! Sources.
	QList< SourceCfg > m_sources;
	//! Texts.
	QList< TextCfg > m_texts;
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
	//! Texts.
	QtConfFile::TagVectorOfTags< TextCfgTag > m_texts;
}; // class SchemeCfgTag

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__SCHEME_CFG__INCLUDED

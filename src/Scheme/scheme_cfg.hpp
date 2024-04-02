
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SCHEME__SCHEME_CFG__INCLUDED
#define GLOBE__SCHEME__SCHEME_CFG__INCLUDED

// Globe include.
#include <Scheme/source_cfg.hpp>
#include <Scheme/text_cfg.hpp>
#include <Scheme/item_base_cfg.hpp>

// Como include.
#include <Como/Source>

// Qt include.
#include <QList>

// cfgfile include.
#include <cfgfile/all.hpp>


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

	//! \return Name.
	const QString & name() const;
	//! Set name.
	void setName( const QString & n );

	//! \return Position of the item.
	const QPointF & pos() const;
	//! Set position of the item.
	void setPos( const QPointF & pos );

	//! \return Size of the item.
	const QSizeF & size() const;
	//! Set size of the item.
	void setSize( const QSizeF & size );

	//! \return Sources.
	const QList< SourceCfg > & sources() const;
	//! Set sources.
	void setSources( const QList< SourceCfg > & s );

	//! \return Texts.
	const QList< TextCfg > & texts() const;
	//! Set texts.
	void setTexts( const QList< TextCfg > & t );

	//! \return Aggregates.
	const QList< SchemeCfg > & aggregates() const;
	//! Set aggregates.
	void setAggregates( const QList< SchemeCfg > & a );

	//! \return List of all sources on the scheme.
	QList< QPair< Como::Source, QString > > availableSources() const;

private:
	//! Sources.
	QList< SourceCfg > m_sources;
	//! Texts.
	QList< TextCfg > m_texts;
	//! Aggregates.
	QList< SchemeCfg > m_aggregates;
	//! Name.
	QString m_name;
	//! Position.
	QPointF m_pos;
	//! Size.
	QSizeF m_size;
}; // class SchemeCfg


//
// SchemeCfgTag
//

//! Tag with scheme configuration.
class SchemeCfgTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	SchemeCfgTag();

	explicit SchemeCfgTag( const SchemeCfg & cfg );

	SchemeCfgTag( const QString & name, bool isMandatory );

	SchemeCfgTag( const SchemeCfg & cfg, const QString & name,
		bool isMandatory = true );

	//! \return Configuration.
	SchemeCfg cfg() const;

private:
	//! Init from configuration.
	void initFromCfg( const SchemeCfg & cfg );

private:
	//! Sources.
	cfgfile::tag_vector_of_tags_t< SourceCfgTag,
		cfgfile::qstring_trait_t > m_sources;
	//! Texts.
	cfgfile::tag_vector_of_tags_t< TextCfgTag,
		cfgfile::qstring_trait_t > m_texts;
	//! Aggregates.
	cfgfile::tag_vector_of_tags_t< SchemeCfgTag,
		cfgfile::qstring_trait_t > m_aggregates;
	//! Name.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_name;
	//! Pos.
	QPointFTag m_pos;
	//! Size.
	QSizeFTag m_size;
}; // class SchemeCfgTag

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__SCHEME_CFG__INCLUDED

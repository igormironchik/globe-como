
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SCHEME__SOURCE_CFG_HPP__INCLUDED
#define GLOBE__SCHEME__SOURCE_CFG_HPP__INCLUDED

// cfgfile include.
#include <cfgfile/all.hpp>

// Globe include.
#include <Scheme/item_base_cfg.hpp>

// Como include.
#include <Como/Source>


namespace Globe {

namespace Scheme {

//
// SourceCfg
//

//! Configuration of the source item on the scheme.
class SourceCfg
	:	public ItemBaseCfg
{
public:
	SourceCfg();

	SourceCfg( Como::Source::Type type, const QString & channelName,
		const QString & typeName, const QString & sourceName,
		const QPointF & pos, const QSizeF & size,
		const QFont & font );

	explicit SourceCfg( const ItemBaseCfg & cfg );

	SourceCfg( const SourceCfg & other );

	SourceCfg & operator = ( const SourceCfg & other );

	virtual ~SourceCfg();

	//! \return Type.
	Como::Source::Type type() const;
	//! Set type.
	void setType( Como::Source::Type t );

	//! \return Channel name.
	const QString & channelName() const;
	//! Set channel name.
	void setChannelName( const QString & name );

	//! \return Type name.
	const QString & typeName() const;
	//! Set type name.
	void setTypeName( const QString & name );

	//! \return Source name.
	const QString & sourceName() const;
	//! Set source name.
	void setSourceName( const QString & name );

private:
	//! Type.
	Como::Source::Type m_type;
	//! Channel name.
	QString m_channelName;
	//! Type name.
	QString m_typeName;
	//! Source name.
	QString m_sourceName;
}; // class SourceCfg


//
// SourceCfgTag
//

//! Tag with source item configuration.
class SourceCfgTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	SourceCfgTag( const QString & name, bool isMandatory = false );

	SourceCfgTag( const SourceCfg & cfg, const QString & name,
		bool isMandatory = false );

	//! \return Configuration.
	SourceCfg sourceCfg() const;

private:
	//! Type.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_type;
	//! Type constraint.
	cfgfile::constraint_one_of_t< QString > m_typeConstraint;
	//! Channel name.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_channelName;
	//! Type name.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_typeName;
	//! Source name.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_sourceName;
	//! Item base cfg.
	ItemBaseCfgTag m_baseCfg;
}; // class SourceCfgTag

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__SOURCE_CFG_HPP__INCLUDED

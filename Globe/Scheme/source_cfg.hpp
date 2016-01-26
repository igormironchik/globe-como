
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

#ifndef GLOBE__SCHEME__SOURCE_CFG_HPP__INCLUDED
#define GLOBE__SCHEME__SOURCE_CFG_HPP__INCLUDED

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>
#include <QtConfFile/ConstraintOneOf>

// Globe include.
#include <Globe/Scheme/item_base_cfg.hpp>

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
	:	public QtConfFile::TagNoValue
{
public:
	SourceCfgTag( const QString & name, bool isMandatory = false );

	SourceCfgTag( const SourceCfg & cfg, const QString & name,
		bool isMandatory = false );

	//! \return Configuration.
	SourceCfg sourceCfg() const;

private:
	//! Type.
	QtConfFile::TagScalar< QString > m_type;
	//! Type constraint.
	QtConfFile::ConstraintOneOf< QString > m_typeConstraint;
	//! Channel name.
	QtConfFile::TagScalar< QString > m_channelName;
	//! Type name.
	QtConfFile::TagScalar< QString > m_typeName;
	//! Source name.
	QtConfFile::TagScalar< QString > m_sourceName;
	//! Item base cfg.
	ItemBaseCfgTag m_baseCfg;
}; // class SourceCfgTag

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__SOURCE_CFG_HPP__INCLUDED

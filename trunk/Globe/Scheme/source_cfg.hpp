
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
		bool isMandatory() = false );

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

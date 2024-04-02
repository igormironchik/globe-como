
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__PROPERTIES_CFG_HPP__INCLUDED
#define GLOBE__PROPERTIES_CFG_HPP__INCLUDED

// cfgfile include.
#include <cfgfile/all.hpp>

// Globe include.
#include <Core/properties_map.hpp>
#include <Core/window_state_cfg.hpp>


namespace Globe {

//
// PropertiesMapRecordTag
//

//! Tag with one record of the properties map.
class PropertiesMapRecordTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	explicit PropertiesMapRecordTag( const QString & name,
		bool isMandatory = false );

	PropertiesMapRecordTag( const PropertiesKey & key,
		const PropertiesValue & value, const QString & name );

	//! \return Key of the record.
	PropertiesKey key() const;

	//! \return Value of the record.
	PropertiesValue value() const;

private:
	//! Source's name.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_sourceName;
	//! Source's type name.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_typeName;
	//! Channel's name.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_channelName;
	//! Type of the value of the source.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_valueType;
	//! Constraint for the type of the value of the source.
	cfgfile::constraint_one_of_t< QString > m_valueTypeConstraint;
	//! Configuration file of the properties.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_confFileName;
}; // class PropertiesMapRecordTag


//
// PropertiesManagerTag
//

//! Tag with configuration of the properties manager.
class PropertiesManagerTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	PropertiesManagerTag();

	PropertiesManagerTag( const QString & propsPath,
		const PropertiesMap & exactlyThisSourceMap,
		const PropertiesMap & exactlyThisSourceInAnyChannelMap,
		const PropertiesMap & exactlyThisTypeOfSourceMap,
		const PropertiesMap & exactlyThisTypeOfSourceInAnyChannelMap,
		const WindowStateCfg & windowState );

	//! \return Directory with properties configuration files.
	QString propertiesDirectory() const;

	//! \return Map of the properties for "ExactlyThisSource".
	PropertiesMap exactlyThisSourceMap() const;

	//! \return Map of the properties for "ExactlyThisSourceInAnyChannel".
	PropertiesMap exactlyThisSourceInAnyChannelMap() const;

	//! \return Map of the properties for "ExactlyThisTypeOfSource".
	PropertiesMap exactlyThisTypeOfSourceMap() const;

	//! \return Map of the properties for "ExactlyThisTypeOfSourceInAnyChannel".
	PropertiesMap exactlyThisTypeOfSourceInAnyChannelMap() const;

	//! \return Window state.
	WindowStateCfg windowState() const;

private:
	//! Directory with properties configuration files.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_directory;
	//! Map of the properties.
	cfgfile::tag_vector_of_tags_t< PropertiesMapRecordTag,
		cfgfile::qstring_trait_t > m_map;
	//! State of the window of the properties manager.
	WindowStateCfgTag m_windowState;
}; // class PropertiesManagerTag

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_CFG_HPP__INCLUDED

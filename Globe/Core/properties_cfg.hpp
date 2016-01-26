
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

#ifndef GLOBE__PROPERTIES_CFG_HPP__INCLUDED
#define GLOBE__PROPERTIES_CFG_HPP__INCLUDED

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagVectorOfTags>
#include <QtConfFile/TagScalar>
#include <QtConfFile/ConstraintOneOf>

// Globe include.
#include <Globe/Core/properties_map.hpp>
#include <Globe/Core/window_state_cfg.hpp>


namespace Globe {

//
// PropertiesMapRecordTag
//

//! Tag with one record of the properties map.
class PropertiesMapRecordTag
	:	public QtConfFile::TagNoValue
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
	QtConfFile::TagScalar< QString > m_sourceName;
	//! Source's type name.
	QtConfFile::TagScalar< QString > m_typeName;
	//! Channel's name.
	QtConfFile::TagScalar< QString > m_channelName;
	//! Type of the value of the source.
	QtConfFile::TagScalar< QString > m_valueType;
	//! Constraint for the type of the value of the source.
	QtConfFile::ConstraintOneOf< QString > m_valueTypeConstraint;
	//! Configuration file of the properties.
	QtConfFile::TagScalar< QString > m_confFileName;
}; // class PropertiesMapRecordTag


//
// PropertiesManagerTag
//

//! Tag with configuration of the properties manager.
class PropertiesManagerTag
	:	public QtConfFile::TagNoValue
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
	QtConfFile::TagScalar< QString > m_directory;
	//! Map of the properties.
	QtConfFile::TagVectorOfTags< PropertiesMapRecordTag > m_map;
	//! State of the window of the properties manager.
	WindowStateCfgTag m_windowState;
}; // class PropertiesManagerTag

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_CFG_HPP__INCLUDED

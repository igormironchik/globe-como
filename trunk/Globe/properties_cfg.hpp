
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

#ifndef GLOBE__PROPERTIES_CFG_HPP__INCLUDED
#define GLOBE__PROPERTIES_CFG_HPP__INCLUDED

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagVectorOfTags>
#include <QtConfFile/TagScalar>
#include <QtConfFile/ConstraintOneOf>

// Globe include.
#include <Globe/properties_map.hpp>
#include <Globe/window_state_cfg.hpp>


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

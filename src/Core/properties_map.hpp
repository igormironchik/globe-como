
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__PROPERTIES_MAP_HPP__INLCUDED
#define GLOBE__PROPERTIES_MAP_HPP__INLCUDED

// Como include.
#include <Como/Source>

// Globe include.
#include <Core/properties.hpp>

// Qt include.
#include <QMap>


namespace Globe {

//
// PropertiesKeyType
//

//! Enum with properties key type.
enum PropertiesKeyType {
	//! Not defined.
	NotDefinedKeyType,
	//! Exactly this source.
	ExactlyThisSource,
	//! Exactly this source but from any channel.
	ExactlyThisSourceInAnyChannel,
	//! Exactly this type of source with any name.
	ExactlyThisTypeOfSource,
	//! Exactly this type of source with any name from any channel.
	ExactlyThisTypeOfSourceInAnyChannel
}; // enum PropertiesKeyType


//
// PropertiesKey
//

/*!
	The key for the map of properties.

	Name of the type can't be empty.

	If defined only name of type then this key points to the properties
	for all sources with the given type in any channel.

	If defined name of the type and name of the channel then this key
	points to the properties for all sources with the given type in the
	given channel.

	If defined name of the source and name of the type then this key
	points to the properties for the sources with the given name and type
	in any channel.

	If defined and name and type and channel's name then this key points
	to the properties for the source with the given name and type from the
	given channel.
*/
class PropertiesKey {
public:
	PropertiesKey();

	PropertiesKey( const QString & name,
		const QString & typeName, const QString & channelName );

	PropertiesKey( const PropertiesKey & other );

	PropertiesKey & operator = ( const PropertiesKey & other );

	//! \return Name of the source.
	const QString & name() const;

	//! \return Type name of the source.
	const QString & typeName() const;

	//! \return Channel's name.
	const QString & channelName() const;

	//! \return Type of the key.
	PropertiesKeyType keyType() const;

private:
	//! Source's name.
	QString m_name;
	//! Source's type name.
	QString m_typeName;
	//! Channel's name.
	QString m_channelName;
	//! Key type.
	PropertiesKeyType m_keyType;
}; // class PropertiesKey

bool operator < ( const PropertiesKey & k1, const PropertiesKey & k2 );
bool operator == ( const PropertiesKey & k1, const PropertiesKey & k2 );


//
// PropertiesValue
//

//! The value for the map of properties.
class PropertiesValue {
public:
	PropertiesValue();

	PropertiesValue( const QString & confFileName,
		const Como::Source::Type & type,
		const Properties & props );

	PropertiesValue( const PropertiesValue & other );

	PropertiesValue & operator = ( const PropertiesValue & other );

	//! \return Configuration's file name.
	const QString & confFileName() const;

	//! \return Type of the value of the source.
	Como::Source::Type valueType() const;

	//! \return Properties.
	Properties & properties();

	//! \return Properties.
	const Properties & properties() const;

private:
	//! Configuration's file name.
	QString m_confFileName;
	//!Type of the value of the source.
	Como::Source::Type m_valueType;
	//! Properties.
	Properties m_properties;
}; // class PropertiesValue


//! Type of the map of properties.
typedef QMap< PropertiesKey, PropertiesValue > PropertiesMap;

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_MAP_HPP__INLCUDED

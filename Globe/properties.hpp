
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 Igor Mironchik

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

#ifndef GLOBE__PROPERTIES_HPP__INCLUDED
#define GLOBE__PROPERTIES_HPP__INCLUDED

// Como include.
#include <Como/Source>

// Qt include.
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QScopedPointer>
#include <QtGui/QMainWindow>

// Globe include.
#include <Globe/condition.hpp>


namespace Globe {

class ToolWindowObject;
class SourcesManager;
class ChannelsManager;


//
// Properties
//

//! Properties of the source.
class Properties {
public:
	Properties();

	Properties( const Properties & other );

	Properties & operator = ( const Properties & other );

	//! \return Priority of the source.
	int priority() const;
	//! Set priority of the source.
	void setPriority( int p );

	//! \return Amount of conditions.
	int conditionsAmount() const;
	//! \return Condition with the given index.
	Condition & conditionAt( int index );
	//! \return Condition with the given index.
	const Condition & conditionAt( int index ) const;
	//! \return Otherwise condition.
	Condition & otherwise();
	//! \return Otherwise condition.
	const Condition & otherwise() const;
	//! Insert new condition to the new place with \arg index.
	void insertCondition( const Condition & cond, int index );
	//! Remove condition with the \arg index.
	void removeCondition( int index );
	//! Swap to conditions in the list.
	void swapConditions( int i, int j );
	//! \return Condition for the given value.
	const Condition & checkConditions( const QVariant & value,
		Como::Source::Type valueType ) const;

	// Save properties configuration.
	void saveConfiguration( const QString & fileName ) const;
	//! Read properties configuration.
	void readConfiguration( const QString & fileName );

private:
	//! Priority of the source.
	int m_priority;
	//! List of conditions for this source.
	QList< Condition > m_conditions;
	//! Otherwise condition.
	Condition m_otherwise;
}; // class Properties


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

private:
	//! Source's name.
	QString m_name;
	//! Source's type name.
	QString m_typeName;
	//! Channel's name.
	QString m_channelName;
}; // class PropertiesKey

bool operator < ( const PropertiesKey & k1, const PropertiesKey & k2 );
bool operator == ( const PropertiesKey & k1, const PropertiesKey & k2 );


//
// PropertiesValue
//

//! The value for the map of properties.
class PropertiesValue {
public:
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


//
// PropertiesManager
//

class PropertiesManagerPrivate;

//! Manager of all properties in application.
class PropertiesManager
	:	public QMainWindow
{
	Q_OBJECT

public:
	PropertiesManager( SourcesManager * sourcesManager,
		ChannelsManager * channelsManager,
		QWidget * parent = 0, Qt::WindowFlags flags = 0 );

	~PropertiesManager();

	/*!
		\return Properties for the given source.
		\retval NULL if there is no properties for the given source.
	*/
	const Properties * findProperties( const Como::Source & source,
		const QString & channelName ) const;
	/*!
		\return Properties for the given key.
		\retval NULL if there is no properties for the given key.
	*/
	const Properties * findProperties( const PropertiesKey & key ) const;
	//! Add new properties.
	void addProperties( const PropertiesKey & key, const Properties & props,
		const Como::Source::Type & type,
		const QString & cfgFileName );
	//! Remove properties for the given \arg source source.
	void removeProperties( const PropertiesKey & key );

	//! Save properties manager configuration.
	void saveConfiguration( const QString & fileName );
	//! Read properties manager configuration.
	void readConfiguration( const QString & fileName );

	//! \return Tool window object.
	ToolWindowObject * toolWindowObject();

protected:
	friend class MainWindow;

	//! Init tools menu.
	void initToolsMenu( const QList< ToolWindowObject* > & toolWindows );

protected:
	void closeEvent( QCloseEvent * event );

private:
	//! Init.
	void init();
	//! Init model.
	void initModelAndView();

private:
	Q_DISABLE_COPY( PropertiesManager )

	QScopedPointer< PropertiesManagerPrivate > d;
}; // class PropertiesManager

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_HPP__INCLUDED

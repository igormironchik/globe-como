
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__PROPERTIES_MANAGER_HPP__INCLUDED
#define GLOBE__PROPERTIES_MANAGER_HPP__INCLUDED

// Qt include.
#include <QScopedPointer>
#include <QMainWindow>

// Globe include.
#include <Core/tool_window.hpp>
#include <Core/properties_map.hpp>
#include <Core/export.hpp>

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE


namespace Globe {

//
// PropertiesManager
//

class PropertiesManagerPrivate;

//! Manager of all properties in application.
class CORE_EXPORT PropertiesManager
	:	public QMainWindow
	,	public ToolWindow
{
	Q_OBJECT

signals:
	//! Emits everu time when properties changed.
	void propertiesChanged();

private:
	PropertiesManager( QWidget * parent = 0, Qt::WindowFlags flags = Qt::WindowFlags() );

	~PropertiesManager();

	static void cleanup();

public:
	//! \return Instance.
	static PropertiesManager & instance();

	/*!
		\return Properties for the given source.
		\retval NULL if there is no properties for the given source.
	*/
	const Properties * findProperties( const Como::Source & source,
		const QString & channelName, PropertiesKey * resultedkey ) const;
	//! Add new properties.
	void addProperties( const Como::Source & source,
		const QString & channelName, QWidget * parent = 0 );
	//! Remove properties for the given source.
	void removeProperties( const PropertiesKey & key, QWidget * parent = 0 );
	//! Edit properties.
	void editProperties( const PropertiesKey & key, QWidget * parent = 0 );
	//! Promote properties to the new one.
	void promoteProperties( const PropertiesKey & key, QWidget * parent = 0 );

	//! Save properties manager configuration.
	void saveConfiguration( const QString & fileName );
	//! Read properties manager configuration.
	void readConfiguration( const QString & fileName );

	//! Init with default configuration.
	void initWithDefaultCfg();

	//! \return Tool window object.
	ToolWindowObject * toolWindowObject();

	//! Init menu.
	void initMenu( const Menu & menu );

protected:
	void closeEvent( QCloseEvent * event );

private:
	//! Init.
	void init();
	//! Init model.
	void initModelAndView();
	//! Read properties configurations.
	void readPropertiesConfigs( PropertiesMap & map );

private slots:
	//! Add propertie.
	void addProperties();
	//! Remove properties.
	void removeProperties();
	//! Item selected.
	void itemSelected( const QModelIndex & index );
	//! Edit properties.
	void editProperties();
	//! Promote properties.
	void promoteProperties();

private:
	Q_DISABLE_COPY( PropertiesManager )

	QScopedPointer< PropertiesManagerPrivate > d;
}; // class PropertiesManager

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_MANAGER_HPP__INCLUDED

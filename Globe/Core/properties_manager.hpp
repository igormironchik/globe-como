
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

#ifndef GLOBE__PROPERTIES_MANAGER_HPP__INCLUDED
#define GLOBE__PROPERTIES_MANAGER_HPP__INCLUDED

// Qt include.
#include <QScopedPointer>
#include <QMainWindow>

// Globe include.
#include <Globe/Core/tool_window.hpp>
#include <Globe/Core/properties_map.hpp>

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE


namespace Globe {

//
// PropertiesManager
//

class PropertiesManagerPrivate;

//! Manager of all properties in application.
class PropertiesManager
	:	public QMainWindow
	,	public ToolWindow
{
	Q_OBJECT

signals:
	//! Emits everu time when properties changed.
	void propertiesChanged();

private:
	PropertiesManager( QWidget * parent = 0, Qt::WindowFlags flags = 0 );

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
	//! Remove properties for the given \arg source source.
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

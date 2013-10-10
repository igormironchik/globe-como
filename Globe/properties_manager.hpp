
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

#ifndef GLOBE__PROPERTIES_MANAGER_HPP__INCLUDED
#define GLOBE__PROPERTIES_MANAGER_HPP__INCLUDED

// Qt include.
#include <QScopedPointer>
#include <QMainWindow>

// Globe include.
#include <Globe/tool_window.hpp>
#include <Globe/properties_map.hpp>

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

private:
	PropertiesManager( QWidget * parent = 0, Qt::WindowFlags flags = 0 );

	~PropertiesManager();

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

private:
	Q_DISABLE_COPY( PropertiesManager )

	QScopedPointer< PropertiesManagerPrivate > d;
}; // class PropertiesManager

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_MANAGER_HPP__INCLUDED

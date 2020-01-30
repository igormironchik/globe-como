
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2020 Igor Mironchik

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

#ifndef GLOBE__PROPERTIES_MANAGER_VIEW_HPP__INCLUDED
#define GLOBE__PROPERTIES_MANAGER_VIEW_HPP__INCLUDED

// Qt include.
#include <QTreeView>
#include <QScopedPointer>


QT_BEGIN_NAMESPACE
class QAction;
QT_END_NAMESPACE


namespace Globe {

//
// PropertiesManagerView
//

class PropertiesManagerViewPrivate;

/*!
	View in the properties manager.
*/
class PropertiesManagerView
	:	public QTreeView
{
	Q_OBJECT

public:
	explicit PropertiesManagerView( QWidget * parent = 0 );
	virtual ~PropertiesManagerView();

	//! Set actions.
	void setActions( QAction * add, QAction * edit,
		QAction * del, QAction * promote );

protected:
	virtual void contextMenuEvent( QContextMenuEvent * e );

private:
	Q_DISABLE_COPY( PropertiesManagerView )

	QScopedPointer< PropertiesManagerViewPrivate > d;
}; // class PropertiesManagerView

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_MANAGER_VIEW_HPP__INCLUDED

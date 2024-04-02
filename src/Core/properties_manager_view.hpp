
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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

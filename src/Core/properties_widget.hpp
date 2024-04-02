
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__PROPERTIES_WIDGET_HPP__INCLUDED
#define GLOBE__PROPERTIES_WIDGET_HPP__INCLUDED

// Qt include.
#include <QTreeView>
#include <QWidget>
#include <QScopedPointer>

// Globe include.
#include <Core/properties.hpp>


namespace Globe {

class PropertiesList;


//
// PropertiesWidget
//

class PropertiesWidgetPrivate;

//! Widget with properties.
class PropertiesWidget
	:	public QWidget
{
	Q_OBJECT

signals:
	//! Wrong properties.
	void wrongProperties();
	//! Changed.
	void changed();

public:
	explicit PropertiesWidget( Como::Source::Type valueType,
		QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );
	~PropertiesWidget();

	//! \return Properties.
	Properties properties() const;
	//! Set properties.
	void setProperties( const Properties & p );

	//! \return List with conditions.
	PropertiesList * conditionsList();

private slots:
	//! Properties changed.
	void propertiesChanged();
	//! Wrong properties.
	void propertiesWrong();
	//! Priority changed.
	void priorityChanged( int p );

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( PropertiesWidget )

	QScopedPointer< PropertiesWidgetPrivate > d;
}; // class PropertiesWidget


//
// PropertiesList
//

class PropertiesListPrivate;

//! Widget with list of conditions.
class PropertiesList
	:	public QTreeView
{
	Q_OBJECT

	friend class PropertiesWidget;

signals:
	//! Wrong properties.
	void wrongProperties();
	//! Changed.
	void changed();

public:
	explicit PropertiesList( Como::Source::Type valueType,
		QWidget * parent = 0 );
	~PropertiesList();

	//! Set properties.
	void setProperties( const Properties & p );

	//! \return Index of the current item.
	int currentItemIndex() const;
	//! \return Count of items.
	int itemsCount() const;
	//! \return Is otherwise condition exists?
	bool isOtherwiseConditionExists() const;
	//! \return Is all properties set.
	bool isPropertiesOk() const;

public slots:
	//! Move current item up.
	void moveCurrentUp();
	//! Move current item down.
	void moveCurrentDown();
	//! Delete current item.
	void deleteCurrent();
	//! Add new condition.
	void addCondition();
	//! Add otherwise condition.
	void addOtherwiseCondition();

private slots:
	//! Properties changed.
	void propertiesChanged();
	//! Wrong properties.
	void propertiesWrong();
	//! Move under cursor up.
	void moveUnderCursorUp();
	//! Move under cursor down.
	void moveUnderCursorDown();
	//! Delete under cursor.
	void deleteUnderCursor();
	//! Section resized.
	void sectionResized( int section, int, int );

protected:
	//! Context menu event.
	void contextMenuEvent( QContextMenuEvent * event );

	//! \return Properties.
	Properties properties() const;

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( PropertiesList )

	QScopedPointer< PropertiesListPrivate > d;
}; // class PropertiesList

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_WIDGET_HPP__INCLUDED

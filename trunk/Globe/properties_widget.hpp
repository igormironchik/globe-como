
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

#ifndef GLOBE__PROPERTIES_WIDGET_HPP__INCLUDED
#define GLOBE__PROPERTIES_WIDGET_HPP__INCLUDED

// Qt include.
#include <QtGui/QTreeView>
#include <QtGui/QWidget>
#include <QtCore/QScopedPointer>

// Globe include.
#include <Globe/properties.hpp>


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
		QWidget * parent = 0, Qt::WindowFlags f = 0 );
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

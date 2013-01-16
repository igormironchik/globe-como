
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
#include <QtCore/QScopedPointer>

// Globe include.
#include <Globe/properties.hpp>
#include <Globe/scrolled_widget.hpp>


namespace Globe {

//
// PropertiesList
//

class PropertiesListPrivate;

/*!
	Widget with list of condition widgets.
	This widget is used in PropertiesList to present
	list of condition widgets.
*/
class PropertiesList
	:	public ScrolledWidget
{
	Q_OBJECT

signals:
	//! Wrong properties.
	void wrongProperties();
	//! Changed.
	void changed();

public:
	explicit PropertiesList( Como::Source::Type valueType,
		QWidget * parent = 0, Qt::WindowFlags f = 0 );
	~PropertiesList();

	//! \return Properties.
	Properties properties() const;
	//! Set properties.
	void setProperties( const Properties & p );

	//! \return Index of the current frame.
	int currentFrameIndex() const;
	//! \return Count of frames.
	int framesCount() const;
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
	//! There is wrong condition.
	void wrongCondition();
	//! Condition changed.
	void conditionChanged();
	//! Otherwise condition changed.
	void otherwiseConditionChanged();
	//! Move under cursor up.
	void moveUnderCursorUp();
	//! Move under cursor down.
	void moveUnderCursorDown();
	//! Delete under cursor.
	void deleteUnderCursor();

protected:
	//! Mouse press event.
	void mousePressEvent( QMouseEvent * event );
	//! Mouse move event.
	void mouseMoveEvent( QMouseEvent * event );
	//! Context menu event.
	void contextMenuEvent( QContextMenuEvent * event );
	//! Resize widget.
	void resizeWidget( const QSize & size );

private:
	Q_DISABLE_COPY( PropertiesList )

	QScopedPointer< PropertiesListPrivate > d;
}; // class PropertiesList

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_WIDGET_HPP__INCLUDED

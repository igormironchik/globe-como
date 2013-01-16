
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

#ifndef GLOBE__CONDITION_WIDGET_HPP__INCLUDED
#define GLOBE__CONDITION_WIDGET_HPP__INCLUDED

// Qt include.
#include <QtGui/QWidget>
#include <QtCore/QScopedPointer>

// Globe include.
#include <Globe/condition.hpp>

// Como include.
#include <Como/Source>


namespace Globe {

//
// ConditionWidget
//

class ConditionWidgetPrivate;

//! Widget that displays condition.
class ConditionWidget
	:	public QWidget
{
	Q_OBJECT

signals:
	//! Emitted on changes.
	void changed();
	//! Emitted on wrong condition.
	void wrongCondition();

public:
	explicit ConditionWidget( Como::Source::Type type,
		QWidget * parent = 0, Qt::WindowFlags f = 0 );

	~ConditionWidget();

	//! Set condition.
	void setCondition( const Condition & c );
	//! \return Condition.
	Condition condition() const;

	//! \return Is condition set?
	bool isConditionOk() const;

private:
	//! Init.
	void init();

private slots:
	//! Equaltion changed.
	void expressionChanged( int index );
	//! Value changed.
	void valueChanged( const QString & text );
	//! Level changed.
	void levelChanged( int index );
	//! Message changed.
	void messageChanged( bool on );

private:
	Q_DISABLE_COPY( ConditionWidget )

	QScopedPointer< ConditionWidgetPrivate > d;
}; // class ConditionWidget

} /* namespace Globe */

#endif // GLOBE__CONDITION_WIDGET_HPP__INCLUDED

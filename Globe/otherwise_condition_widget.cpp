
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

// Globe include.
#include <Globe/otherwise_condition_widget.hpp>

#include "ui_otherwise_condition_widget.h"


namespace Globe {

//
// OtherwiseConditionWidgetPrivate
//

class OtherwiseConditionWidgetPrivate {
public:
	OtherwiseConditionWidgetPrivate()
	{
	}

	//! Ui.
	Ui::OtherwiseConditionWidget m_ui;
}; // class OtherwiseConditionWidgetPrivate


//
// OtherwiseConditionWidget
//

OtherwiseConditionWidget::OtherwiseConditionWidget( QWidget * parent,
	Qt::WindowFlags f )
	:	QWidget( parent, f )
	,	d( new OtherwiseConditionWidgetPrivate )
{
	init();
}

OtherwiseConditionWidget::~OtherwiseConditionWidget()
{
}

static inline int levelIndex( Level l )
{
	switch( l )
	{
		case None : return 0;
		case Critical : return 1;
		case Error : return 2;
		case Warning : return 3;
		case Debug : return 4;
		case Info : return 5;
		default : return -1;
	}
}

void
OtherwiseConditionWidget::setCondition( const Condition & c )
{
	d->m_ui.m_level->setCurrentIndex( levelIndex( c.level() ) );
	d->m_ui.m_message->setPlainText( c.message() );
}

static inline Level levelFromIndex( int index )
{
	switch( index )
	{
		case 0 : return None;
		case 1 : return Critical;
		case 2 : return Error;
		case 3 : return Warning;
		case 4 : return Debug;
		case 5 : return Info;
		default : return None;
	}
}

Condition
OtherwiseConditionWidget::condition() const
{
	Condition c;

	c.setLevel( levelFromIndex( d->m_ui.m_level->currentIndex() ) );

	c.setMessage( d->m_ui.m_message->toPlainText() );

	return c;
}

void
OtherwiseConditionWidget::init()
{
	d->m_ui.setupUi( this );

	connect( d->m_ui.m_level, SIGNAL( currentIndexChanged( int ) ),
		this, SLOT( levelChanged( int ) ) );
	connect(d->m_ui.m_message, SIGNAL( modificationChanged( bool ) ),
		this, SLOT( messageChanged( bool ) ) );
}

void
OtherwiseConditionWidget::levelChanged( int index )
{
	if( index != -1 )
		emit changed();
}

void
OtherwiseConditionWidget::messageChanged( bool on )
{
	if( on )
		emit changed();
}

} /* namespace Globe */


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

// Globe include.
#include <Globe/condition_widget.hpp>

#include "ui_condition_widget.h"

// Qt include.
#include <QtGui/QColor>


namespace Globe {

//
// ConditionWidgetPrivate
//

class ConditionWidgetPrivate {
public:
	ConditionWidgetPrivate( Como::Source::Type type )
		:	m_type( type )
	{
	}

	//! Set foreground color to red for the given widget.
	void highlightError( QWidget * widget )
	{
		QPalette palette = widget->palette();
		palette.setColor( QPalette::Text, Qt::red );
		widget->setPalette( palette );
	}

	//! Set foreground color to default value.
	void highlightNormal( QWidget * widget )
	{
		QPalette palette = widget->palette();
		palette.setColor( QPalette::Text, m_textColor );
		widget->setPalette( palette );
	}

	//! Type of the value.
	Como::Source::Type m_type;
	//! Ui.
	Ui::ConditionWidget m_ui;
	//! Default text color.
	QColor m_textColor;
}; // class ConditionWidgetPrivate


//
// ConditionWidget
//

ConditionWidget::ConditionWidget( Como::Source::Type type,
	QWidget * parent, Qt::WindowFlags f )
	:	QWidget( parent, f )
	,	d( new ConditionWidgetPrivate( type ) )
{
	init();
}

ConditionWidget::~ConditionWidget()
{
}

static inline int expressionIndex( Expression expr )
{
	switch( expr )
	{
		case IfLess : return 0;
		case IfLessOrEqual : return 1;
		case IfEqual : return 2;
		case IfGreaterOrEqual : return 3;
		case IfGreater : return 4;
		default : return -1;
	}
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
ConditionWidget::setCondition( const Condition & c )
{
	d->m_ui.m_expression->setCurrentIndex( expressionIndex( c.type() ) );
	d->m_ui.m_value->setText( c.value().toString() );
	d->m_ui.m_level->setCurrentIndex( levelIndex( c.level() ) );
	d->m_ui.m_message->setPlainText( c.message() );
}

static inline Expression expressionFromIndex( int index )
{
	switch( index )
	{
		case 0 : return IfLess;
		case 1 : return IfLessOrEqual;
		case 2 : return IfEqual;
		case 3 : return IfGreaterOrEqual;
		case 4 : return IfGreater;
		default : return IfEqual;
	}
}

static inline QVariant intValueFromString( const QString & text )
{
	return QVariant( text.toInt() );
}

static inline QVariant doubleValueFromString( const QString & text )
{
	return QVariant( text.toDouble() );
}

static inline QVariant stringValueFromString( const QString & text )
{
	return QVariant( text );
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
ConditionWidget::condition() const
{
	Condition c;

	c.setType( expressionFromIndex( d->m_ui.m_expression->currentIndex() ) );

	if( d->m_type == Como::Source::Int )
		c.setValue( intValueFromString( d->m_ui.m_value->text() ) );
	else if( d->m_type == Como::Source::Double )
		c.setValue( doubleValueFromString( d->m_ui.m_value->text() ) );
	else
		c.setValue( stringValueFromString( d->m_ui.m_value->text() ) );

	c.setLevel( levelFromIndex( d->m_ui.m_level->currentIndex() ) );

	c.setMessage( d->m_ui.m_message->toPlainText() );

	return c;
}

void
ConditionWidget::init()
{
	d->m_ui.setupUi( this );

	d->m_textColor = d->m_ui.m_value->palette().color( QPalette::Text );

	connect( d->m_ui.m_expression, SIGNAL( currentIndexChanged( int ) ),
		this, SLOT( expressionChanged( int ) ) );
	connect( d->m_ui.m_value, SIGNAL( textChanged( const QString & ) ),
		this, SLOT( valueChanged( const QString & ) ) );
	connect( d->m_ui.m_level, SIGNAL( currentIndexChanged( int ) ),
		this, SLOT( levelChanged( int ) ) );
	connect(d->m_ui.m_message, SIGNAL( modificationChanged( bool ) ),
		this, SLOT( messageChanged( bool ) ) );
}

void
ConditionWidget::expressionChanged( int index )
{
	if( index != -1 )
		emit changed();
	else
		emit wrongCondition();
}

static inline bool checkIntValue( const QString & text )
{
	bool ok = false;

	text.toInt( &ok );

	return ok;
}

static inline bool checkDoubleValue( const QString & text )
{
	bool ok = false;

	text.toDouble( &ok );

	return ok;
}

static inline bool checkStringValue( const QString & text )
{
	Q_UNUSED( text )

	return true;
}

void
ConditionWidget::valueChanged( const QString & text )
{
	if( d->m_type == Como::Source::Int )
	{
		if( !checkIntValue( text ) )
		{
			d->highlightError( d->m_ui.m_value );
			emit wrongCondition();
		}
		else
		{
			d->highlightNormal( d->m_ui.m_value );
			emit changed();
		}
	}
	else if( d->m_type == Como::Source::Double )
	{
		if( !checkDoubleValue( text ) )
		{
			d->highlightError( d->m_ui.m_value );
			emit wrongCondition();
		}
		else
		{
			d->highlightNormal( d->m_ui.m_value );
			emit changed();
		}
	}
	else
	{
		if( !checkStringValue( text ) )
		{
			d->highlightError( d->m_ui.m_value );
			emit wrongCondition();
		}
		else
		{
			d->highlightNormal( d->m_ui.m_value );
			emit changed();
		}
	}
}

void
ConditionWidget::levelChanged( int index )
{
	if( index != -1 )
		emit changed();
	else
		emit wrongCondition();
}

void
ConditionWidget::messageChanged( bool on )
{
	if( on )
		emit changed();
}

} /* namespace Globe */

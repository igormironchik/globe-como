
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
#include <Globe/Core/color_picker.hpp>

// Qt include.
#include <QPalette>
#include <QPainter>
#include <QColorDialog>


namespace Globe {

//
// ColorPickerPrivate
//

class ColorPickerPrivate {
public:
	explicit ColorPickerPrivate( QWidget * w )
		:	m_color( w->palette().color( QPalette::Window ) )
	{
	}

	//! Color.
	QColor m_color;
}; // class ColorPickerPrivate


//
// ColorPicker
//

ColorPicker::ColorPicker( QWidget * parent, Qt::WindowFlags f )
	:	QFrame( parent, f )
	,	d( new ColorPickerPrivate( this ) )
{
	init();
}

ColorPicker::~ColorPicker()
{
}

const QColor &
ColorPicker::color() const
{
	return d->m_color;
}

void
ColorPicker::setColor( const QColor & c )
{
	d->m_color = c;

	update();
}

void
ColorPicker::paintEvent( QPaintEvent * event )
{
	QFrame::paintEvent( event );

	QPainter painter( this );

	painter.setPen( Qt::NoPen );
	painter.setBrush( d->m_color );

	painter.drawRect( frameRect().marginsRemoved( QMargins( 1, 1, 1, 1 ) ) );
}

void
ColorPicker::mouseReleaseEvent( QMouseEvent * event )
{
	Q_UNUSED( event );

	QColorDialog dlg( d->m_color, this );

	if( dlg.exec() == QDialog::Accepted )
		setColor( dlg.selectedColor() );
}

void
ColorPicker::init()
{
	setFrameShape( QFrame::StyledPanel );
	setFrameShadow( QFrame::Sunken );
}

} /* namespace Globe */

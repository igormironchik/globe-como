
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/color_picker.hpp>

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

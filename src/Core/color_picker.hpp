
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__COLOR_PICKER_HPP__INCLUDED
#define GLOBE__COLOR_PICKER_HPP__INCLUDED

// Qt include.
#include <QFrame>
#include <QScopedPointer>
#include <QColor>


namespace Globe {

//
// ColorPicker
//

class ColorPickerPrivate;

//! Color picker.
class ColorPicker
	:	public QFrame
{
	Q_OBJECT

public:
	ColorPicker( QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );
	~ColorPicker();

	//! \return Color.
	const QColor & color() const;
	//! Set color.
	void setColor( const QColor & c );

protected:
	void paintEvent( QPaintEvent * event );

	void mouseReleaseEvent( QMouseEvent * event );

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( ColorPicker )

	QScopedPointer< ColorPickerPrivate > d;
}; // class ColorPicker

} /* namespace Globe */

#endif // GLOBE__COLOR_PICKER_HPP__INCLUDED

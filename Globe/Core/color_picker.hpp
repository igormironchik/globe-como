
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

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
	ColorPicker( QWidget * parent = 0, Qt::WindowFlags f = 0 );
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

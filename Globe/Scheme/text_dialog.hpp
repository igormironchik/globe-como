
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

#ifndef GLOBE__SCHEME__TEXT_DIALOG_HPP__INCLUDED
#define GLOBE__SCHEME__TEXT_DIALOG_HPP__INCLUDED

// Qt include.
#include <QDialog>
#include <QScopedPointer>


namespace Globe {

namespace Scheme {

//
// TextDialog
//

class TextDialogPrivate;

//! Dialog with text.
class TextDialog
	:	public QDialog
{
	Q_OBJECT

public:
	explicit TextDialog( QString & text, QWidget * parent = 0,
		Qt::WindowFlags f = 0 );

	~TextDialog();

private slots:
	//! Text changed.
	void textChanged();

private:
	Q_DISABLE_COPY( TextDialog )

	QScopedPointer< TextDialogPrivate > d;
}; // class TextDialog

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__TEXT_DIALOG_HPP__INCLUDED

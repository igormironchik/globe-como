
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2020 Igor Mironchik

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

#ifndef GLOBE__PROPERTIES_KEY_TYPE_DIALOG_HPP__INCLUDED
#define GLOBE__PROPERTIES_KEY_TYPE_DIALOG_HPP__INCLUDED

// Globe include.
#include <Core/properties_map.hpp>

// Qt include.
#include <QDialog>
#include <QScopedPointer>


namespace Globe {

//
// PropertiesKeyTypeDialog
//

class PropertiesKeyTypeDialogPrivate;

//! Dialog for setting properties key type.
class PropertiesKeyTypeDialog
	:	public QDialog
{
	Q_OBJECT

public:
	explicit PropertiesKeyTypeDialog( PropertiesKeyType & type,
		QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );

	~PropertiesKeyTypeDialog();

private:
	//! Init.
	void init();

private slots:
	//! Accepted.
	void ok();

private:
	Q_DISABLE_COPY( PropertiesKeyTypeDialog )

	QScopedPointer< PropertiesKeyTypeDialogPrivate > d;
}; // class PropertiesKeyTypeDialog

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_KEY_TYPE_DIALOG_HPP__INCLUDED

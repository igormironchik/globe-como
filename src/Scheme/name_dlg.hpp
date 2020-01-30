
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

#ifndef GLOBE__SCHEME__NAME_DLG_HPP__INCLUDED
#define GLOBE__SCHEME__NAME_DLG_HPP__INCLUDED

// Qt include.
#include <QDialog>

// Globe include.
#include "ui_name_dlg.h"


namespace Globe {

namespace Scheme {

//
// NameDlg
//

//! Name dialog.
class NameDlg Q_DECL_FINAL
	:	public QDialog
{
	Q_OBJECT

public:
	NameDlg( QWidget * parent = Q_NULLPTR );
	~NameDlg();

	//! \return Name.
	QString name() const;

private slots:
	//! Name changed.
	void nameChanged( const QString & name );

private:
	Q_DISABLE_COPY( NameDlg )

	//! Ui.
	Ui::NameDlg m_ui;
}; // class NameDlg

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__NAME_DLG_HPP__INCLUDED

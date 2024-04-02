
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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

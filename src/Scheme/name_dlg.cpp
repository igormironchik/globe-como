
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Scheme/name_dlg.hpp>

// Qt include.
#include <QLineEdit>
#include <QPushButton>
#include <QDialogButtonBox>


namespace Globe {

namespace Scheme {

//
// NameDlg
//

NameDlg::NameDlg( QWidget * parent )
	:	QDialog( parent )
{
	m_ui.setupUi( this );

	m_ui.m_btns->button( QDialogButtonBox::Ok )->setEnabled( false );

	connect( m_ui.m_name, &QLineEdit::textChanged,
		this, &NameDlg::nameChanged );
}

NameDlg::~NameDlg()
{
}

QString
NameDlg::name() const
{
	return m_ui.m_name->text();
}

void
NameDlg::nameChanged( const QString & name )
{
	if( name.isEmpty() )
		m_ui.m_btns->button( QDialogButtonBox::Ok )->setEnabled( false );
	else
		m_ui.m_btns->button( QDialogButtonBox::Ok )->setEnabled( true );
}

} /* namespace Scheme */

} /* namespace Globe */

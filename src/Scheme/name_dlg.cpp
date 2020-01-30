
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

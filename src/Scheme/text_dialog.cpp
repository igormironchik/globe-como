
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
#include <Scheme/text_dialog.hpp>

#include "ui_text_dialog.h"

// Qt include.
#include <QPlainTextEdit>


namespace Globe {

namespace Scheme {

//
// TextDialogPrivate
//

class TextDialogPrivate {
public:
	explicit TextDialogPrivate( QString & text )
		:	m_text( text )
	{
	}

	//! Text.
	QString & m_text;
	//! Ui.
	Ui::TextDialog m_ui;
}; // class TextDialogPrivate


//
// TextDialog
//

TextDialog::TextDialog( QString & text, QWidget * parent,
	Qt::WindowFlags f )
	:	QDialog( parent, f )
	,	d( new TextDialogPrivate( text ) )
{
	d->m_ui.setupUi( this );
	d->m_ui.m_edit->setPlainText( text );

	connect( d->m_ui.m_edit, &QPlainTextEdit::textChanged,
		this, &TextDialog::textChanged );
}

TextDialog::~TextDialog()
{
}

void
TextDialog::textChanged()
{
	d->m_text = d->m_ui.m_edit->toPlainText();
}

} /* namespace Scheme */

} /* namespace Globe */

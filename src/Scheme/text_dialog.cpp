
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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

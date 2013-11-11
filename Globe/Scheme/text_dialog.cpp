
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2013 Igor Mironchik

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

// Globe include.
#include <Globe/Scheme/text_dialog.hpp>

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

	connect( d->m_ui.m_edit, SIGNAL( textChanged() ),
		this, SLOT( textChanged() ) );
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


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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
		Qt::WindowFlags f = Qt::WindowFlags() );

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

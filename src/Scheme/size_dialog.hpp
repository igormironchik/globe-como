
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SCHEME__SIZE_DIALOG_HPP__INCLUDED
#define GLOBE__SCHEME__SIZE_DIALOG_HPP__INCLUDED

// Qt include.
#include <QDialog>
#include <QScopedPointer>


namespace Globe {

namespace Scheme {

//
// SizeDialog
//

class SizeDialogPrivate;

//! Dialog for changing size.
class SizeDialog
	:	public QDialog
{
	Q_OBJECT

public:
	SizeDialog( int & width, int & height,
		QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );

	~SizeDialog();

private slots:
	//! Width changed.
	void widthChanged( int width );
	//! Height changed.
	void heightChanged( int height );

private:
	Q_DISABLE_COPY( SizeDialog )

	QScopedPointer< SizeDialogPrivate > d;
}; // class SizeDialog

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__SIZE_DIALOG_HPP__INCLUDED

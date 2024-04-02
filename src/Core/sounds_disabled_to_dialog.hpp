
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SOUNDS_DISABLE_TO_DIALOG_HPP__INCLUDED
#define GLOBE__SOUNDS_DISABLE_TO_DIALOG_HPP__INCLUDED

// Qt include.
#include <QDialog>
#include <QScopedPointer>


namespace Globe {

//
// DisableSoundToDialog
//

class DisableSoundToDialogPrivate;

//! Dialog with time offset for disabling sound.
class DisableSoundToDialog
	:	public QDialog
{
	Q_OBJECT

public:
	explicit DisableSoundToDialog( QDateTime & to,
		QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );

	~DisableSoundToDialog();

private slots:
	//! Set date and time to current.
	void setDateTimeToCurrent();
	//! Accept button clicked.
	void acceptButtonClicked();
	//! Actual date and time changed.
	void actualDateTimeChanged( const QDateTime & dt );
	//! Relative date and time changed.
	void relativeDateTimeChanged( const QString & dt );

private:
	//! Init.
	void init();
	//! Check correctness of date and time format.
	bool checkCorrectnessOfFormat( const QString & dt );
	//! Highlight error in format of date and time.
	void highlightError();
	//! Highlight ok in format of date and time.
	void highlightOk();

private:
	Q_DISABLE_COPY( DisableSoundToDialog )

	QScopedPointer< DisableSoundToDialogPrivate > d;
}; // class DisableSoundToDialog

} /* namespace Globe */

#endif // GLOBE__SOUNDS_DISABLE_TO_DIALOG_HPP__INCLUDED

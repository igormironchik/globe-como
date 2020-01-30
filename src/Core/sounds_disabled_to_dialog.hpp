
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
		QWidget * parent = 0, Qt::WindowFlags f = 0 );

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

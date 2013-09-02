
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

#ifndef GLOBE__CONFIGURATION_DIALOG_HPP__INCLUDED
#define GLOBE__CONFIGURATION_DIALOG_HPP__INCLUDED

// Qt include.
#include <QDialog>
#include <QScopedPointer>

QT_BEGIN_NAMESPACE
class QListWidgetItem;
class QLineEdit;
class QToolButton;
QT_END_NAMESPACE


namespace Globe {

class ColorForLevel;

//
// ConfigurationDialog
//

class ConfigurationDialogPrivate;

//! Configuration dialog.
class ConfigurationDialog
	:	public QDialog
{
	Q_OBJECT

public:
	explicit ConfigurationDialog( ColorForLevel * cfl,
		QWidget * parent = 0, Qt::WindowFlags f = 0 );

	~ConfigurationDialog();

private slots:
	//! Change settings page.
	void changePage( QListWidgetItem * current, QListWidgetItem * previous );
	//! New settings accepted.
	void newSettingsAccepted();
	//! Reset colors to default values.
	void resetColorsToDefaultValues();
	//! Enable/disable sources log.
	void sourcesLogStateChanged( int state );

	//! Enable/disable critical sound.
	void criticalSoundStateChanged( int state );
	//! Enable/disable error sound.
	void errorSoundStateChanged( int state );
	//! Enable/disable warning sound.
	void warningSoundStateChanged( int state );
	//! Enable/disable debug sound.
	void debugSoundStateChanged( int state );
	//! Enable/disable info sound.
	void infoSoundStateChanged( int state );

	//! Critical sound button clicked.
	void criticalSoundButtonClicked();
	//! Error sound button clicked.
	void errorSoundButtonClicked();
	//! Warning sound button clicked.
	void warningSoundButtonClicked();
	//! Debug sound button clicked.
	void debugSoundButtonClicked();
	//! Info sound button clicked.
	void infoSoundButtonClicked();

protected:
	friend class MainWindow;

	//! Init UI with settings.
	void initUiWithSettings();

private:
	//! Init.
	void init();
	//! Sound checkbox's state changed.
	void soundCheckBoxStateChanged( int state,
		QLineEdit * line, QToolButton * button );
	//! Sound select button clicked.
	void soundSelectButtonClicked( QLineEdit * line );

private:
	Q_DISABLE_COPY( ConfigurationDialog )

	QScopedPointer< ConfigurationDialogPrivate > d;
}; // class ConfigurationDialog

} /* namespace Globe */

#endif // GLOBE__CONFIGURATION_DIALOG_HPP__INCLUDED

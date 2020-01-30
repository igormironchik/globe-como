
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
	ConfigurationDialog( QWidget * parent = 0, Qt::WindowFlags f = 0 );

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

	//! Clear event's log.
	void clearEventLog();
	//! Clear sources log.
	void clearSourcesLog();

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

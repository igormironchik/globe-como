
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__PROPERTIES_CFG_FILENAME_DIALOG_HPP__INCLUDED
#define GLOBE__PROPERTIES_CFG_FILENAME_DIALOG_HPP__INCLUDED

// Qt include.
#include <QDialog>
#include <QScopedPointer>


namespace Globe {

//
// PropertiesCfgFileNameDialog
//

class PropertiesCfgFileNameDialogPrivate;

//! Dialog for properties configuration file name.
class PropertiesCfgFileNameDialog
	:	public QDialog
{
	Q_OBJECT

public:
	PropertiesCfgFileNameDialog( QString & fileName,
		const QString & path,
		QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );

	~PropertiesCfgFileNameDialog();

private:
	//! Init.
	void init();

private slots:
	//! Select file.
	void selectFile();
	//! Accepted.
	void ok();
	//! File name changed.
	void fileNameChanged( const QString & text );

private:
	Q_DISABLE_COPY( PropertiesCfgFileNameDialog )

	QScopedPointer< PropertiesCfgFileNameDialogPrivate > d;
}; // class PropertiesCfgFileNameDialog

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_CFG_FILENAME_DIALOG_HPP__INCLUDED

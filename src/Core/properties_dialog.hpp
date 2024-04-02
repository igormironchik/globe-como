
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__PROPERTIES_DIALOG_HPP__INCLUDED
#define GLOBE__PROPERTIES_DIALOG_HPP__INCLUDED

// Qt include.
#include <QDialog>
#include <QScopedPointer>

// Como include.
#include <Como/Source>


namespace Globe {

class PropertiesWidget;

//
// PropertiesDialog
//

class PropertiesDialogPrivate;

//! Dialog with properties.
class PropertiesDialog
	:	public QDialog
{
	Q_OBJECT

public:
	PropertiesDialog( const QString & cfgDirName, Como::Source::Type valueType,
		QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );
	~PropertiesDialog();

	//! \return Properties widget.
	PropertiesWidget * propertiesWidget();

private:
	//! Init.
	void init();

private slots:
	//! Wrong properties.
	void wrongProperties();
	//! Properties has been changed.
	void propertiesChanged();
	//! Open properties from file.
	void openProperties();

private:
	Q_DISABLE_COPY( PropertiesDialog )

	QScopedPointer< PropertiesDialogPrivate > d;
}; // class PropertiesDialog

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_DIALOG_HPP__INCLUDED

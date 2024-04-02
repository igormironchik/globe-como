
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__PROPERTIES_KEY_TYPE_DIALOG_HPP__INCLUDED
#define GLOBE__PROPERTIES_KEY_TYPE_DIALOG_HPP__INCLUDED

// Globe include.
#include <Core/properties_map.hpp>

// Qt include.
#include <QDialog>
#include <QScopedPointer>


namespace Globe {

//
// PropertiesKeyTypeDialog
//

class PropertiesKeyTypeDialogPrivate;

//! Dialog for setting properties key type.
class PropertiesKeyTypeDialog
	:	public QDialog
{
	Q_OBJECT

public:
	explicit PropertiesKeyTypeDialog( PropertiesKeyType & type,
		QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );

	~PropertiesKeyTypeDialog();

private:
	//! Init.
	void init();

private slots:
	//! Accepted.
	void ok();

private:
	Q_DISABLE_COPY( PropertiesKeyTypeDialog )

	QScopedPointer< PropertiesKeyTypeDialogPrivate > d;
}; // class PropertiesKeyTypeDialog

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_KEY_TYPE_DIALOG_HPP__INCLUDED


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/properties_key_type_dialog.hpp>

#include "ui_properties_key_type_dialog.h"

// Qt include.
#include <QRadioButton>


namespace Globe {

//
// PropertiesKeyTypeDialogPrivate;
//

class PropertiesKeyTypeDialogPrivate {
public:
	explicit PropertiesKeyTypeDialogPrivate( PropertiesKeyType & type )
		:	m_type( type )
	{
	}

	//! Type of the key.
	PropertiesKeyType & m_type;
	//! Ui.
	Ui::PropertiesKeyTypeDialog m_ui;
}; // class PropertiesKeyTypeDialogPrivate


//
// PropertiesKeyTypeDialog
//

PropertiesKeyTypeDialog::PropertiesKeyTypeDialog( PropertiesKeyType & type,
	QWidget * parent, Qt::WindowFlags f )
	:	QDialog( parent, f )
	,	d( new PropertiesKeyTypeDialogPrivate( type ) )
{
	init();
}

PropertiesKeyTypeDialog::~PropertiesKeyTypeDialog()
{
}

void
PropertiesKeyTypeDialog::init()
{
	d->m_ui.setupUi( this );

	setWindowTitle( tr( "Select propertie's type..." ) );

	connect( d->m_ui.m_buttons, &QDialogButtonBox::accepted,
		this, &PropertiesKeyTypeDialog::ok );
}

void
PropertiesKeyTypeDialog::ok()
{
	if( d->m_ui.m_exactly->isChecked() )
		d->m_type =	ExactlyThisSource;
	else if( d->m_ui.m_exactlyButAnyChannel->isChecked() )
		d->m_type = ExactlyThisSourceInAnyChannel;
	else if( d->m_ui.m_typeAndChannelOnly->isChecked() )
		d->m_type = ExactlyThisTypeOfSource;
	else if( d->m_ui.m_typeInAnyChannel->isChecked() )
		d->m_type = ExactlyThisTypeOfSourceInAnyChannel;
	else
		d->m_type = NotDefinedKeyType;

	accept();
}

} /* namespace Globe */

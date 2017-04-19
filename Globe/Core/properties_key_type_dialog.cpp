
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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

// Globe include.
#include <Globe/Core/properties_key_type_dialog.hpp>

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
		this, &PropertiesKeyTypeDialog::accepted );
}

void
PropertiesKeyTypeDialog::accepted()
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

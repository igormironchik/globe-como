
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

// Globe include.
#include <Globe/properties_key_type_dialog.hpp>

#include "ui_properties_key_type_dialog.h"

// Qt include.
#include <QtGui/QRadioButton>


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

	connect( d->m_ui.m_buttons, SIGNAL( accepted() ),
		this, SLOT( accepted() ) );
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


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Scheme/size_dialog.hpp>

#include "ui_size_dialog.h"

// Qt include.
#include <QSpinBox>


namespace Globe {

namespace Scheme {

//
// SizeDialogPrivate
//

class SizeDialogPrivate {
public:
	SizeDialogPrivate( int & width, int & height )
		:	m_width( width )
		,	m_height( height )
	{
	}

	//! Width.
	int & m_width;
	//! Height.
	int & m_height;
	//! Ui.
	Ui::SizeDialog m_ui;
}; // class SizeDialogPrivate


//
// SizeDialog
//

SizeDialog::SizeDialog( int & width, int & height,
	QWidget * parent, Qt::WindowFlags f )
	:	QDialog( parent, f )
	,	d( new SizeDialogPrivate( width, height ) )
{
	d->m_ui.setupUi( this );

	d->m_ui.m_width->setValue( width );
	d->m_ui.m_height->setValue( height );

	void ( QSpinBox::*signal ) ( int ) = &QSpinBox::valueChanged;

	connect( d->m_ui.m_width, signal,
		this, &SizeDialog::widthChanged );

	connect( d->m_ui.m_height, signal,
		this, &SizeDialog::heightChanged );
}

SizeDialog::~SizeDialog()
{
}

void
SizeDialog::widthChanged( int width )
{
	d->m_width = width;
}

void
SizeDialog::heightChanged( int height )
{
	d->m_height = height;
}

} /* namespace Scheme */

} /* namespace Globe */

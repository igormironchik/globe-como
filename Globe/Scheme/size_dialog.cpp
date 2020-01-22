
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

// Globe include.
#include <Globe/Scheme/size_dialog.hpp>

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

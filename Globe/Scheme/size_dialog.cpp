
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

	connect( d->m_ui.m_width, SIGNAL( valueChanged( int ) ),
		this, SLOT( widthChanged( int ) ) );
	connect( d->m_ui.m_height, SIGNAL( valueChanged( int ) ),
		this, SLOT( heightChanged( int ) ) );
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


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
#include <Globe/Core/channel_name_dialog.hpp>

#include "ui_channel_name_dialog.h"

// Qt include.
#include <QComboBox>
#include <QDialogButtonBox>
#include <QPushButton>



namespace Globe {

//
// ChannelNameDialogPrivate
//

class ChannelNameDialogPrivate {
public:
	explicit ChannelNameDialogPrivate( QString & result )
		:	m_result( result )
	{
	}

	//! Result of the dialog.
	QString & m_result;
	//! Ui.
	Ui::ChannelNameDialog m_ui;
}; // class ChannelNameDialogPrivate


//
// ChannelNameDialog
//

ChannelNameDialog::ChannelNameDialog( QString & result,
	const QStringList & names,
	QWidget * parent, Qt::WindowFlags f )
	:	QDialog( parent, f )
	,	d( new ChannelNameDialogPrivate( result ) )
{
	init( names );
}

ChannelNameDialog::~ChannelNameDialog()
{
}

void
ChannelNameDialog::accepted()
{
	d->m_result = d->m_ui.m_channel->currentText();

	accept();
}

void
ChannelNameDialog::currentIndexChanged( int index )
{
	if( index != -1 )
		d->m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( true );
}

void
ChannelNameDialog::init( const QStringList & names )
{
	d->m_ui.setupUi( this );

	connect( d->m_ui.m_channel, SIGNAL( currentIndexChanged( int ) ),
		this, SLOT( currentIndexChanged( int ) ) );

	connect( d->m_ui.m_buttons, SIGNAL( accepted() ),
		this, SLOT( accepted() ) );

	d->m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );

	d->m_ui.m_channel->addItems( names );
}

} /* namespace Globe */

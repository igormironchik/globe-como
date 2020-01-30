
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
#include <Core/channel_name_dialog.hpp>

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

	void ( QComboBox::*signal )( int ) = &QComboBox::currentIndexChanged;

	connect( d->m_ui.m_channel, signal,
		this, &ChannelNameDialog::currentIndexChanged );

	connect( d->m_ui.m_buttons, &QDialogButtonBox::accepted,
		this, &ChannelNameDialog::accepted );

	d->m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );

	d->m_ui.m_channel->addItems( names );
}

} /* namespace Globe */

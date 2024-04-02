
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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
ChannelNameDialog::ok()
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
		this, &ChannelNameDialog::ok );

	d->m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );

	d->m_ui.m_channel->addItems( names );
}

} /* namespace Globe */


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
#include <Globe/Core/source_manual_dialog.hpp>
#include <Globe/Core/sources.hpp>

#include "ui_source_manual_dialog.h"

// Qt include.
#include <QPushButton>


namespace Globe {

//
// SourcemanualDialogPrivate
//

class SourceManualDialogPrivate {
public:
	SourceManualDialogPrivate( Como::Source & source,
		QString & channelName )
		:	m_source( source )
		,	m_channelName( channelName )
		,	m_wasChannelSet( false )
		,	m_wasNameSet( false )
		,	m_wasTypeSet( false )
	{
	}

	//! Enable "OK" button if all is done.
	void enableAcceptIfAllIsOk()
	{
		if( m_wasChannelSet && m_wasNameSet && m_wasTypeSet )
			m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( true );
		else
			m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );
	}

	//! Source.
	Como::Source & m_source;
	//! Channel name.
	QString & m_channelName;
	//! Ui.
	Ui::SourceManualDialog m_ui;
	//! Was channel set?
	bool m_wasChannelSet;
	//! Was name set?
	bool m_wasNameSet;
	//! Was type set?
	bool m_wasTypeSet;
}; // class SourceManualDialogPrivate


//
// SourceManualDialog
//

SourceManualDialog::SourceManualDialog( Como::Source & source,
	QString & channelName, QWidget * parent, Qt::WindowFlags f )
	:	QDialog( parent, f )
	,	d( new SourceManualDialogPrivate( source, channelName ) )
{
	init();
}

SourceManualDialog::~SourceManualDialog()
{
}

void
SourceManualDialog::init()
{
	d->m_ui.setupUi( this );

	d->m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );

	connect( d->m_ui.m_buttons, &QDialogButtonBox::accepted,
		this, &SourceManualDialog::accepted );

	connect( d->m_ui.m_buttons, &QDialogButtonBox::rejected,
		this, &SourceManualDialog::reject );

	void ( QComboBox::*signal ) ( int ) = &QComboBox::currentIndexChanged;

	connect( d->m_ui.m_channel, signal,
		this, &SourceManualDialog::channelWasSet );

	connect( d->m_ui.m_name, &QLineEdit::textChanged,
		this, &SourceManualDialog::nameWasSet );

	connect( d->m_ui.m_typeName, &QLineEdit::textChanged,
		this, &SourceManualDialog::typeWasSet );

	foreach( const QString & channelName, SourcesManager::instance().channelsNames() )
		d->m_ui.m_channel->addItem( channelName );
}

static inline Como::Source::Type typeFromComboBox( int index )
{
	if( index == 0 )
		return Como::Source::Int;
	else if( index == 1 )
		return Como::Source::Double;
	else
		return Como::Source::String;
}

void
SourceManualDialog::accepted()
{
	Como::Source source( typeFromComboBox( d->m_ui.m_valueType->currentIndex() ),
		d->m_ui.m_name->text(), d->m_ui.m_typeName->text(), QVariant(),
		QLatin1String( "" ) );

	d->m_source = source;
	d->m_channelName = d->m_ui.m_channel->currentText();

	accept();
}

void
SourceManualDialog::channelWasSet( int index )
{
	if( index != -1 )
		d->m_wasChannelSet = true;
	else
		d->m_wasChannelSet = false;

	d->enableAcceptIfAllIsOk();
}

void
SourceManualDialog::nameWasSet( const QString & text )
{
	if( !text.isEmpty() )
		d->m_wasNameSet = true;
	else
		d->m_wasNameSet = false;

	d->enableAcceptIfAllIsOk();
}

void
SourceManualDialog::typeWasSet( const QString & text )
{
	if( !text.isEmpty() )
		d->m_wasTypeSet = true;
	else
		d->m_wasTypeSet = false;

	d->enableAcceptIfAllIsOk();
}

} /* namespace Globe */

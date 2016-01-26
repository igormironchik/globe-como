
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

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
#include <Globe/Core/channel_attributes.hpp>
#include <Globe/Core/channels.hpp>

#include "ui_channel_attributes.h"

// Qt include.
#include <QHostAddress>
#include <QPushButton>
#include <QColor>
#include <QPushButton>
#include <QToolTip>
#include <QRegExp>


namespace Globe {

//
// ChannelAttributesPrivate
//

class ChannelAttributesPrivate {
public:
	ChannelAttributesPrivate()
	{
	}

	//! Name of the channel.
	QString m_name;
	//! Address of the channel.
	QHostAddress m_address;
	//! Port of the channel.
	quint16 m_port;
}; // class ChannelAttributesPrivate


//
// ChannelAttributes
//


ChannelAttributes::ChannelAttributes()
	:	d( new ChannelAttributesPrivate )
{
}

ChannelAttributes::~ChannelAttributes()
{
}


const QString &
ChannelAttributes::name() const
{
	return d->m_name;
}

void
ChannelAttributes::setName( const QString & name )
{
	d->m_name = name;
}

const QHostAddress &
ChannelAttributes::address() const
{
	return d->m_address;
}

void
ChannelAttributes::setAddress( const QHostAddress & addr )
{
	d->m_address = addr;
}

quint16
ChannelAttributes::port() const
{
	return d->m_port;
}

void
ChannelAttributes::setPort( quint16 p )
{
	d->m_port = p;
}


//
// ChannelAttributesDialogPrivate
//

class ChannelAttributesDialogPrivate {
public:
	ChannelAttributesDialogPrivate( ChannelAttributes & attributes,
		QDialog * parent )
		:	m_attributes( attributes )
		,	m_isNameSet( false )
		,	m_isNameUnique( false )
		,	m_isIPSet( false )
		,	m_isPortSet( true )
		,	m_parent( parent )
		,	m_checkButton( 0 )
	{
	}

	//! \return State of the validation of IP address and port.
	bool checkIPAndPort()
	{
		return ( ChannelsManager::instance().isAddressAndPortUnique(
			QHostAddress( m_ui.m_ip->text() ), m_ui.m_port->value() ) );
	}

	//! Print message about current state.
	void printMessageAndHighlight()
	{
		m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );

		if( m_isNameSet && !m_isNameUnique )
		{
			m_message = ChannelAttributesDialog::tr( "Channel with the given name already exists." );
			return;
		}
		else if( !m_isNameSet )
		{
			m_message = ChannelAttributesDialog::tr( "Enter name of the channel." );
			return;
		}
		else if( !m_isIPSet )
		{
			m_message = ChannelAttributesDialog::tr( "Enter IP address of the channel." );
			return;
		}
		else if( !m_isPortSet )
		{
			m_message = ChannelAttributesDialog::tr( "Enter port number." );
			return;
		}

		if( m_isIPSet && m_isPortSet )
		{
			if( !checkIPAndPort() )
			{
				highlightError( m_ui.m_ip );
				highlightError( m_ui.m_port );

				m_message = ChannelAttributesDialog::tr(
					"Channel with the given IP and port already exists." );

				return;
			}
			else
			{
				highlightNormal( m_ui.m_ip );
				highlightNormal( m_ui.m_port );

				m_message = ChannelAttributesDialog::tr( "All is OK." );
			}
		}

		if( m_isNameSet && m_isIPSet && m_isPortSet )
			m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( true );
	}

	/*!
		State of the dialog changed. Probably we have to enable
		or disable "OK" button.
	*/
	void stateChanged()
	{
		printMessageAndHighlight();
	}

	//! Set foreground color to red for the given widget.
	void highlightError( QWidget * widget )
	{
		QPalette palette = widget->palette();
		palette.setColor( QPalette::Text, Qt::red );
		widget->setPalette( palette );
	}

	//! Set foreground color to default value.
	void highlightNormal( QWidget * widget )
	{
		QPalette palette = widget->palette();
		palette.setColor( QPalette::Text, m_textColor );
		widget->setPalette( palette );
	}

	//! Attributes of the channel.
	ChannelAttributes & m_attributes;
	//! UI.
	Ui::ChannelAttributesDialog m_ui;
	//! Default text color.
	QColor m_textColor;
	//! Is name was set.
	bool m_isNameSet;
	//! Is name unique.
	bool m_isNameUnique;
	//! Is IP was set.
	bool m_isIPSet;
	//! Is port was set.
	bool m_isPortSet;
	//! Parent.
	QDialog * m_parent;
	//! Message.
	QString m_message;
	//! Check button.
	QPushButton * m_checkButton;
}; // class ChannelAttributesDialogPrivate


//
// ChannelAttributesDialog
//

ChannelAttributesDialog::ChannelAttributesDialog( ChannelAttributes & attributes,
	QWidget * parent, Qt::WindowFlags f )
	:	QDialog( parent, f )
	,	d( new ChannelAttributesDialogPrivate( attributes, this ) )
{
	init();
}

ChannelAttributesDialog::~ChannelAttributesDialog()
{
}

void
ChannelAttributesDialog::init()
{
	d->m_ui.setupUi( this );

	d->m_checkButton = new QPushButton( tr( "Check" ), this );
	d->m_ui.m_buttons->addButton( d->m_checkButton,
		QDialogButtonBox::HelpRole );

	d->m_textColor = d->m_ui.m_name->palette().color( QPalette::Text );

	d->stateChanged();

	connect( d->m_ui.m_name, &QLineEdit::textEdited,
		this, &ChannelAttributesDialog::nameEdited );
	connect( d->m_ui.m_ip, &QLineEdit::textEdited,
		this, &ChannelAttributesDialog::ipEdited );

	void ( QSpinBox::*signal )( int ) = &QSpinBox::valueChanged;

	connect( d->m_ui.m_port, signal,
		this, &ChannelAttributesDialog::portEdited );
	connect( d->m_ui.m_buttons, &QDialogButtonBox::accepted,
		this, &ChannelAttributesDialog::accepted );
	connect( d->m_checkButton, &QPushButton::clicked,
		this, &ChannelAttributesDialog::checkFields );
}

void
ChannelAttributesDialog::nameEdited( const QString & text )
{
	if( text.length() )
	{
		if( !ChannelsManager::instance().isNameUnique( text ) )
		{
			d->highlightError( d->m_ui.m_name );
			d->m_isNameSet = true;
			d->m_isNameUnique = false;
			d->stateChanged();
		}
		else
		{
			d->highlightNormal( d->m_ui.m_name );
			d->m_isNameSet = true;
			d->m_isNameUnique = true;
			d->stateChanged();
		}
	}
	else
	{
		d->highlightError( d->m_ui.m_name );
		d->m_isNameSet = false;
		d->m_isNameUnique = false;
		d->stateChanged();
	}
}

void
ChannelAttributesDialog::ipEdited( const QString & text )
{
	static const QRegExp ipValidationRegExp(
		"^([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\."
		"([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\."
		"([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\."
		"([01]?\\d\\d?|2[0-4]\\d|25[0-5])$" );

	if( text.length() )
	{
		if( !ipValidationRegExp.exactMatch( text ) )
		{
			d->highlightError( d->m_ui.m_ip );
			d->m_isIPSet = false;
			d->stateChanged();
		}
		else
		{
			d->highlightNormal( d->m_ui.m_ip );
			d->m_isIPSet = true;
			d->stateChanged();
		}
	}
	else
	{
		d->highlightError( d->m_ui.m_ip );
		d->m_isIPSet = false;
		d->stateChanged();
	}
}

void
ChannelAttributesDialog::portEdited( int val )
{
	if( val <= 0 )
	{
		d->highlightError( d->m_ui.m_port );
		d->m_isPortSet = false;
		d->stateChanged();
	}
	else
	{
		d->highlightNormal( d->m_ui.m_port );
		d->m_isPortSet = true;
		d->stateChanged();
	}
}

void
ChannelAttributesDialog::accepted()
{
	d->m_attributes.setName( d->m_ui.m_name->text() );
	d->m_attributes.setAddress( QHostAddress( d->m_ui.m_ip->text() ) );
	d->m_attributes.setPort( d->m_ui.m_port->value() );

	accept();
}

void
ChannelAttributesDialog::checkFields()
{
	QToolTip::showText( mapToGlobal( d->m_checkButton->pos() ),
		d->m_message, this );
}

} /* namespace Globe */


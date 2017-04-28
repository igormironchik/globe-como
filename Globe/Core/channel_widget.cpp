
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
#include <Globe/Core/channel_widget.hpp>
#include <Globe/Core/channels.hpp>
#include <Globe/Core/channel_timeout_widget.hpp>

// Qt include.
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QPixmap>


namespace Globe {

//
// ChannelWidgetPrivate
//

class ChannelWidgetPrivate {
public:
	explicit ChannelWidgetPrivate( Channel * channel )
		:	m_channel( channel )
		,	m_stateLabel( 0 )
		,	m_nameLabel( 0 )
		,	m_ipLabel( 0 )
		,	m_timeoutWidget( 0 )
		,	m_rateLabel( 0 )
		,	m_connectButton( 0 )
		,	m_disconnectButton( 0 )
		,	m_reconnectButton( 0 )
	{
		m_connectedPixmap.load( QString::fromUtf8(
			":/img/connect_established_22x22.png" ), "PNG" );
		m_disconnectedPixmap.load( QString::fromUtf8(
			":/img/connect_no_22x22.png" ), "PNG" );
	}

	//! Channel.
	Channel * m_channel;
	//! Channel's state label.
	QLabel * m_stateLabel;
	//! Connected pixmap.
	QPixmap m_connectedPixmap;
	//! Disconnected pixmap.
	QPixmap m_disconnectedPixmap;
	//! Channel's name label.
	QLabel * m_nameLabel;
	//! Channel's IP and port label;
	QLabel * m_ipLabel;
	//! Channel's timeout widget.
	ChannelTimeoutWidget * m_timeoutWidget;
	//! Channel's messages rate label.
	QLabel * m_rateLabel;
	//! Rate units label.
	QLabel * m_rateUnits;
	//! Connect button.
	QToolButton * m_connectButton;
	//! Disconnect button.
	QToolButton * m_disconnectButton;
	//! Reconnect button.
	QToolButton * m_reconnectButton;
}; // class ChannelWidgetPrivate


//
// ChannelWidget
//

ChannelWidget::ChannelWidget( Channel * channel,
	QWidget * parent, Qt::WindowFlags f )
	:	QWidget( parent, f )
	,	d( new ChannelWidgetPrivate( channel ) )
{
	init();
}

ChannelWidget::~ChannelWidget()
{
}

const int labelsLayoutSpacing = 4;
const int rateAndTimeoutLayoutSpacing = 6;
const int spacerSize = 10;

void
ChannelWidget::init()
{
	QHBoxLayout * mainLayout = new QHBoxLayout( this );
	mainLayout->setSpacing( 0 );
	mainLayout->setContentsMargins( 0, 0, 0, 0 );

	QVBoxLayout * labelsLayout = new QVBoxLayout();
	labelsLayout->setSpacing( labelsLayoutSpacing );
	labelsLayout->setContentsMargins( 0, 0, 0, 0 );

	QHBoxLayout * stateAndNameLayout = new QHBoxLayout();
	stateAndNameLayout->setSpacing( 0 );
	stateAndNameLayout->setContentsMargins( 0, 0, 0, 0 );

	d->m_stateLabel = new QLabel( this );
	d->m_stateLabel->setPixmap( d->m_disconnectedPixmap );
	d->m_stateLabel->setToolTip( tr( "State of the channel." ) );
	stateAndNameLayout->addWidget( d->m_stateLabel );

	d->m_nameLabel = new QLabel( this );
	d->m_nameLabel->setText( d->m_channel->name() );
	QFont nameFont = d->m_nameLabel->font();
	nameFont.setBold( true );
	nameFont.setPointSize( nameFont.pointSize() + 2 );
	d->m_nameLabel->setFont( nameFont );
	d->m_nameLabel->setToolTip(tr( "Name of the channel." ) );
	stateAndNameLayout->addWidget( d->m_nameLabel );

	QSpacerItem * stateAndNameSpacer =
		new QSpacerItem( spacerSize, spacerSize,
			QSizePolicy::Expanding, QSizePolicy::Minimum );
	stateAndNameLayout->addSpacerItem( stateAndNameSpacer );

	labelsLayout->addLayout( stateAndNameLayout );

	QHBoxLayout * ipLayout = new QHBoxLayout();
	ipLayout->setSpacing( 0 );
	ipLayout->setContentsMargins( 0, 0, 0, 0 );

	d->m_ipLabel = new QLabel( this );
	d->m_ipLabel->setText( d->m_channel->hostAddress() +
		":" + QString::number( d->m_channel->portNumber() ) );
	d->m_ipLabel->setToolTip( tr( "IP address and port." ) );
	ipLayout->addWidget( d->m_ipLabel );

	labelsLayout->addLayout( ipLayout );

	QHBoxLayout * rateAndTimeoutLayout = new QHBoxLayout();
	rateAndTimeoutLayout->setSpacing( rateAndTimeoutLayoutSpacing );
	rateAndTimeoutLayout->setContentsMargins( 0, 0, 0, 0 );

	d->m_timeoutWidget = new ChannelTimeoutWidget( d->m_channel->timeout(),
		this );
	rateAndTimeoutLayout->addWidget( d->m_timeoutWidget );

	d->m_rateLabel = new QLabel( this );
	d->m_rateLabel->setText( QString::number( 0 ) );
	d->m_rateLabel->setToolTip( tr( "Count of messages per second." ) );
	rateAndTimeoutLayout->addWidget( d->m_rateLabel );

	d->m_rateUnits = new QLabel( this );
	d->m_rateUnits->setText( tr( "msg/s" ) );
	rateAndTimeoutLayout->addWidget( d->m_rateUnits );

	QSpacerItem * spacerBetweenTimeoutAndRate =
		new QSpacerItem( spacerSize, spacerSize,
			QSizePolicy::Expanding, QSizePolicy::Minimum );
	rateAndTimeoutLayout->addSpacerItem( spacerBetweenTimeoutAndRate );

	labelsLayout->addLayout( rateAndTimeoutLayout );

	QSpacerItem * vLabelsSpacer =
		new QSpacerItem( spacerSize, spacerSize,
			QSizePolicy::Minimum, QSizePolicy::Expanding );
	labelsLayout->addSpacerItem( vLabelsSpacer );

	mainLayout->addLayout( labelsLayout );

	QVBoxLayout * controlsLayout = new QVBoxLayout();
	controlsLayout->setSpacing( 0 );
	controlsLayout->setContentsMargins( 0, 0, 0, 0 );

	d->m_connectButton = new QToolButton( this );
	QIcon connectIcon;
	connectIcon.addFile( QString::fromUtf8( ":/img/connect_16x16.png" ),
		QSize(), QIcon::Normal, QIcon::Off );
	d->m_connectButton->setIcon( connectIcon );
	d->m_connectButton->setIconSize( QSize( 16, 16 ) );
	d->m_connectButton->setToolTip( tr( "Connect." ) );
	controlsLayout->addWidget( d->m_connectButton );

	d->m_disconnectButton = new QToolButton( this );
	QIcon disconnectIcon;
	disconnectIcon.addFile( QString::fromUtf8( ":/img/disconnect_16x16.png" ),
		QSize(), QIcon::Normal, QIcon::Off );
	d->m_disconnectButton->setIcon( disconnectIcon );
	d->m_disconnectButton->setIconSize( QSize( 16, 16 ) );
	d->m_disconnectButton->setEnabled( false );
	d->m_disconnectButton->setToolTip( tr( "Disconnect." ) );
	controlsLayout->addWidget( d->m_disconnectButton );

	d->m_reconnectButton = new QToolButton( this );
	QIcon reconnectIcon;
	reconnectIcon.addFile( QString::fromUtf8( ":/img/reconnect_16x16.png" ),
		QSize(), QIcon::Normal, QIcon::Off );
	d->m_reconnectButton->setIcon( reconnectIcon );
	d->m_reconnectButton->setIconSize( QSize( 16, 16 ) );
	d->m_reconnectButton->setEnabled( false );
	d->m_reconnectButton->setToolTip( tr( "Reconnect." ) );
	controlsLayout->addWidget( d->m_reconnectButton );

	QSpacerItem * vSpacer =
		new QSpacerItem( spacerSize, spacerSize, QSizePolicy::Minimum, QSizePolicy::Expanding );
	controlsLayout->addSpacerItem( vSpacer );

	mainLayout->addLayout( controlsLayout );

	connect( d->m_timeoutWidget, &ChannelTimeoutWidget::timeoutChanged,
		this, &ChannelWidget::timeoutChanged );
	connect( d->m_channel, &Channel::messagesRate,
		this, &ChannelWidget::messageRate );
	connect( d->m_channel, &Channel::connected,
		this, &ChannelWidget::connected );
	connect( d->m_channel, &Channel::disconnected,
		this, &ChannelWidget::disconnected );
	connect( d->m_connectButton, &QToolButton::clicked,
		this, &ChannelWidget::connectButtonClicked );
	connect( d->m_disconnectButton, &QToolButton::clicked,
		this, &ChannelWidget::disconnectButtonClicked );
	connect( d->m_reconnectButton, &QToolButton::clicked,
		this, &ChannelWidget::reconnectButtonClicked );
}

QSize
ChannelWidget::minimumSizeHint() const
{
	int height = qMax( d->m_stateLabel->minimumSizeHint().height(),
		d->m_nameLabel->minimumSizeHint().height() );
	int width = d->m_stateLabel->minimumSizeHint().width() +
		d->m_nameLabel->minimumSizeHint().width();

	height += ( labelsLayoutSpacing + d->m_ipLabel->minimumSizeHint().height() );
	width = qMax( width, d->m_ipLabel->minimumSizeHint().width() );

	height += ( labelsLayoutSpacing +
		qMax( d->m_timeoutWidget->minimumSizeHint().height(),
			d->m_rateLabel->minimumSizeHint().height() ) );
	width = qMax( width, ( d->m_timeoutWidget->minimumSizeHint().width() +
		d->m_rateLabel->minimumSizeHint().width() +
		d->m_rateUnits->minimumSizeHint().width() ) );

	width += d->m_connectButton->minimumSizeHint().width();
	height = qMax( height, d->m_connectButton->minimumSizeHint().height() * 3 );

	return QSize( width, height );
}

QSize
ChannelWidget::sizeHint() const
{
	return minimumSizeHint();
}

Channel *
ChannelWidget::channel() const
{
	return d->m_channel;
}

void
ChannelWidget::timeoutChanged( int msecs )
{
	d->m_channel->updateTimeout( msecs );
}

void
ChannelWidget::messageRate( int msgCount )
{
	d->m_rateLabel->setText( QString::number( msgCount ) );
}

void
ChannelWidget::connected()
{
	d->m_stateLabel->setPixmap( d->m_connectedPixmap );
	d->m_connectButton->setEnabled( false );
	d->m_disconnectButton->setEnabled( true );
	d->m_reconnectButton->setEnabled( true );
}

void
ChannelWidget::disconnected()
{
	d->m_stateLabel->setPixmap( d->m_disconnectedPixmap );
	d->m_connectButton->setEnabled( true );
	d->m_disconnectButton->setEnabled( false );
	d->m_reconnectButton->setEnabled( false );
}

void
ChannelWidget::connectButtonClicked()
{
	d->m_channel->connectToHost();
}

void
ChannelWidget::disconnectButtonClicked()
{
	d->m_channel->disconnectFromHost();
}

void
ChannelWidget::reconnectButtonClicked()
{
	d->m_channel->reconnectToHost();
}

} /* namespace Globe */


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/channels_to_show.hpp>

#include "ui_channels_to_show.h"


namespace Globe {

//
// ChannelsToShowPrivate
//

class ChannelsToShowPrivate {
public:
	explicit ChannelsToShowPrivate( ShownChannels shownChannels )
		:	m_shownChannels( shownChannels )
	{
	}

	//! User interface.
	Ui::ChannelsToShow m_ui;
	//! Shown channels mode.
	ShownChannels m_shownChannels;
}; // class ChannelsToShowPrivate


//
// ChannelsToShow
//


ChannelsToShow::ChannelsToShow( ShownChannels shownChannels,
	QWidget * parent, Qt::WindowFlags f )
	:	QWidget( parent, f )
	,	d( new ChannelsToShowPrivate( shownChannels ) )
{
	init();
}

ChannelsToShow::~ChannelsToShow()
{
}

void
ChannelsToShow::init()
{
	d->m_ui.setupUi( this );

	void ( QComboBox::*signal) ( int ) = &QComboBox::currentIndexChanged;

	connect( d->m_ui.m_shownChannels, signal,
		this, &ChannelsToShow::displayModeChanged );

	setShownChannelsMode( d->m_shownChannels );
}

ShownChannels
ChannelsToShow::shownChannelsMode() const
{
	return d->m_shownChannels;
}

void
ChannelsToShow::displayModeChanged( int index )
{
	switch( index )
	{
		case 0 : {
			d->m_shownChannels = ShowAll;
			emit displayAllChannels();
		} break;
		case 1 : {
			d->m_shownChannels = ShowConnectedOnly;
			emit displayConnectedChannels();
		} break;
		case 2 : {
			d->m_shownChannels = ShowDisconnectedOnly;
			emit displayDisconnectedChannels();
		} break;
	}
}

void
ChannelsToShow::setShownChannelsMode( ShownChannels mode )
{
	d->m_shownChannels = mode;

	switch( d->m_shownChannels )
	{
		case ShowAll : d->m_ui.m_shownChannels->setCurrentIndex( 0 );
			break;
		case ShowConnectedOnly : d->m_ui.m_shownChannels->setCurrentIndex( 1 );
			break;
		case ShowDisconnectedOnly : d->m_ui.m_shownChannels->setCurrentIndex( 2 );
			break;
	}
}

} /* namespace Globe */


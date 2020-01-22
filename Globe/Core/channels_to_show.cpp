
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
#include <Globe/Core/channels_to_show.hpp>

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


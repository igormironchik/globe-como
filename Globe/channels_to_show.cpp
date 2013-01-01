
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
#include <Globe/channels_to_show.hpp>
#include "ui_channels_to_show.h"


namespace Globe {

//
// ChannelsToShowPrivate
//

class ChannelsToShowPrivate {
public:
	ChannelsToShowPrivate( ShownChannels shownChannels )
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

	connect( d->m_ui.m_shownChannels, SIGNAL( currentIndexChanged( int ) ),
		this, SLOT( displayModeChanged( int ) ) );

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


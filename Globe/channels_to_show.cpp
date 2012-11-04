
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 Igor Mironchik

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
#include <Globe/ui_channels_to_show.h>


namespace Globe {

//
// ChannelsToShowPrivate
//

class ChannelsToShowPrivate {
public:
	ChannelsToShowPrivate()
	{
	}

	//! User interface.
	Ui::ChannelsToShow m_ui;
}; // class ChannelsToShowPrivate


//
// ChannelsToShow
//


ChannelsToShow::ChannelsToShow( QWidget * parent, Qt::WindowFlags f )
	:	QWidget( parent, f )
	,	d( new ChannelsToShowPrivate )
{
	init();
}

void
ChannelsToShow::init()
{
	d->m_ui.setupUi( this );

	connect( d->m_ui.m_shownChannels, SIGNAL( currentIndexChanged( int ) ),
		this, SLOT( displayModeChanged( int ) ) );
}

void
ChannelsToShow::displayModeChanged( int index )
{
	switch( index )
	{
		case 0 : emit displayAllChannels(); break;
		case 1 : emit displayConnectedChannels(); break;
		case 2 : emit displayDisconnectedChannels(); break;
	}
}

} /* namespace Globe */


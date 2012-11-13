
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
#include <Globe/mainwindow.hpp>
#include <Globe/channels.hpp>
#include <Globe/db.hpp>
#include <Globe/channels_list.hpp>


namespace Globe {

//
// MainWindowPrivate
//

class MainWindowPrivate {
public:
	MainWindowPrivate( ChannelsManager * channelsManager, DB * db )
		:	m_channelsManager( channelsManager )
		,	m_db( db )
	{
	}

	//! Channels manager.
	ChannelsManager * m_channelsManager;
	//! Database.
	DB * m_db;
}; // class MainWindowPrivate


//
// MainWindow
//

MainWindow::MainWindow( ChannelsManager * channelsManager, DB * db,
	QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new MainWindowPrivate( channelsManager, db ) )
{
	init();
}

MainWindow::~MainWindow()
{
}

void
MainWindow::init()
{
	ChannelsList * list = new ChannelsList( d->m_channelsManager,
		ShowAll, Qt::AscendingOrder, this );

	setCentralWidget( list );

	Channel * ch1 = d->m_channelsManager->createChannel( QString( "Test" ),
		QHostAddress( QString( "127.0.0.1" ) ), 4545 );
	list->addChannel( ch1 );

	Channel * ch2 = d->m_channelsManager->createChannel( QString( "Test Always Offline" ),
		QHostAddress( QString( "127.0.0.1" ) ), 2030 );
	list->addChannel( ch2 );

	Channel * ch3 = d->m_channelsManager->createChannel( QString( "Test Always Offline #2" ),
		QHostAddress( QString( "127.0.0.1" ) ), 3031 );
	list->addChannel( ch3 );

	ch1->connectToHost();
	ch2->connectToHost();
	ch3->connectToHost();
}

} /* namespace Globe */

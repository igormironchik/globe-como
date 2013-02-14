
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
#include <Globe/channel_view_window.hpp>
#include <Globe/channel_view.hpp>
#include <Globe/channel_view_window_model.hpp>


namespace Globe {

//
// ChannelViewWindowPrivate
//

class ChannelViewWindowPrivate {
public:
	ChannelViewWindowPrivate( PropertiesManager * propertiesManager,
		SourcesManager * sourcesManager,
		ChannelsManager * channelsManager )
		:	m_view( 0 )
		,	m_propertiesManager( propertiesManager )
		,	m_sourcesManager( sourcesManager )
		,	m_channelsManager( channelsManager )
	{
	}

	//! View.
	ChannelView * m_view;
	//! Channel's name.
	QString m_channelName;
	//! Properties manager.
	PropertiesManager * m_propertiesManager;
	//! Sources manager.
	SourcesManager * m_sourcesManager;
	//! Channels manager.
	ChannelsManager * m_channelsManager;
}; // class ChannelViewWindowPrivate


//
// ChannelViewWindow
//

ChannelViewWindow::ChannelViewWindow( PropertiesManager * propertiesManager,
		SourcesManager * sourcesManager,
		ChannelsManager * channelsManager,
		QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new ChannelViewWindowPrivate( propertiesManager, sourcesManager,
			channelsManager ) )
{
	init();
}

ChannelViewWindow::~ChannelViewWindow()
{
}

const QString &
ChannelViewWindow::channel() const
{
	return d->m_channelName;
}

void
ChannelViewWindow::setChannel( const QString & channelName )
{
	d->m_channelName = channelName;

	d->m_view->model()->initModel( d->m_channelName );
}

ChannelViewWindowCfg
ChannelViewWindow::cfg() const
{
	ChannelViewWindowCfg cfg;

	cfg.setChannelName( d->m_channelName );
	cfg.setWindowStateCfg( windowStateCfg( this ) );

	return cfg;
}

void
ChannelViewWindow::setCfg( const ChannelViewWindowCfg & c )
{
	setChannel( c.channelName() );

	restoreWindowState( c.windowStateCfg(), this );
}

void
ChannelViewWindow::init()
{
	d->m_view = new ChannelView( d->m_propertiesManager,
		d->m_sourcesManager, d->m_channelsManager, this );

	setCentralWidget( d->m_view );
}

} /* namespace Globe */


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

#ifndef GLOBE__CHANNEL_VIEW_WINDOW_HPP__INCLUDED
#define GLOBE__CHANNEL_VIEW_WINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Globe/channel_view_window_cfg.hpp>
#include <Globe/with_menu.hpp>


namespace Globe {

class PropertiesManager;
class SourcesManager;
class ChannelsManager;
class ToolWindowObject;
class MainWindow;
class ColorForLevel;


//
// ChannelViewWindow
//

class ChannelViewWindowPrivate;

//! Window with channel's sources.
class ChannelViewWindow
	:	public QMainWindow
	,	public WithMenu
{
	Q_OBJECT

public:
	ChannelViewWindow( PropertiesManager * propertiesManager,
		SourcesManager * sourcesManager,
		ChannelsManager * channelsManager,
		MainWindow * mainWindow,
		ColorForLevel * colorForLevel,
		QWidget * parent = 0, Qt::WindowFlags flags = 0 );

	~ChannelViewWindow();

	//! \return Name of the current channel.
	const QString & channel() const;
	//! \return Is channel was set successfully. Set channel.
	bool setChannel( const QString & channelName );

	//! \return Configuration.
	ChannelViewWindowCfg cfg() const;
	//! Set window configuration.
	void setWindowCfg( const ChannelViewWindowCfg & c );

	//! Init menu.
	void initMenu( const Menu & menu );

protected:
	void closeEvent( QCloseEvent * event );

private:
	//! Init.
	void init();
	//! \return Configuration of the header.
	ViewHeaderCfg viewHeaderCfg() const;
	//! Restore header from configuration.
	void restoreHeader( const ViewHeaderCfg & cfg );

private:
	Q_DISABLE_COPY( ChannelViewWindow )

	QScopedPointer< ChannelViewWindowPrivate > d;
}; // class ChannelViewWindow

} /* namespace Globe */

#endif // GLOBE__CHANNEL_VIEW_WINDOW_HPP__INCLUDED

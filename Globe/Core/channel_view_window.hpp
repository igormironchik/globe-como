
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

#ifndef GLOBE__CHANNEL_VIEW_WINDOW_HPP__INCLUDED
#define GLOBE__CHANNEL_VIEW_WINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Globe/Core/channel_view_window_cfg.hpp>
#include <Globe/Core/with_menu.hpp>


namespace Globe {

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
	ChannelViewWindow( QWidget * parent = 0, Qt::WindowFlags flags = 0 );

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

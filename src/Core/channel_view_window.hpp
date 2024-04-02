
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__CHANNEL_VIEW_WINDOW_HPP__INCLUDED
#define GLOBE__CHANNEL_VIEW_WINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Core/channel_view_window_cfg.hpp>
#include <Core/with_menu.hpp>


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
	ChannelViewWindow( QWidget * parent = 0, Qt::WindowFlags flags = Qt::WindowFlags() );

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

private slots:
	//! Update windows menu.
	void updateWindowsMenu( QWidget * );

private:
	Q_DISABLE_COPY( ChannelViewWindow )

	QScopedPointer< ChannelViewWindowPrivate > d;
}; // class ChannelViewWindow

} /* namespace Globe */

#endif // GLOBE__CHANNEL_VIEW_WINDOW_HPP__INCLUDED

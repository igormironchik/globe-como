
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__CHANNELS_TO_SHOW_HPP__INCLUDED
#define GLOBE__CHANNELS_TO_SHOW_HPP__INCLUDED

// Qt include.
#include <QWidget>
#include <QScopedPointer>


namespace Globe {

//! Shown channels.
enum ShownChannels {
	//! Show only connected channels.
	ShowConnectedOnly = 0,
	//! Show only disconnected channels.
	ShowDisconnectedOnly = 1,
	//! Show all channels.
	ShowAll = 2
}; // enum ShownChannels


class ChannelsToShowPrivate;

//
// ChannelsToShow
//

//! Widget that allow user to select display mode of the channels.
class ChannelsToShow
	:	public QWidget
{

	Q_OBJECT

signals:
	//! "Display all channels" mode selected.
	void displayAllChannels();
	//! "Display connected channels" mode selected.
	void displayConnectedChannels();
	//! "Display disconnected channels" mode selected.
	void displayDisconnectedChannels();

public:
	ChannelsToShow( ShownChannels shownChannels = ShowAll,
		QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );
	~ChannelsToShow();

	//! \return Shown channels mode.
	ShownChannels shownChannelsMode() const;
	//! Set shown channels mode.
	void setShownChannelsMode( ShownChannels mode );

private slots:
	//! User changed the display mode.
	void displayModeChanged( int index );

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( ChannelsToShow )

	QScopedPointer< ChannelsToShowPrivate > d;
}; // class ChannelsToShow

} /* namespace Globe */

#endif // GLOBE__CHANNELS_TO_SHOW_HPP__INCLUDED

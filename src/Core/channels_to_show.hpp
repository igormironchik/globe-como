
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

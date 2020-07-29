
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

#ifndef GLOBE__CHANNEL_NAME_DIALOG_HPP__INCLUDED
#define GLOBE__CHANNEL_NAME_DIALOG_HPP__INCLUDED

// Qt include.
#include <QDialog>
#include <QScopedPointer>


namespace Globe {

//
// ChannelNameDialog
//

class ChannelNameDialogPrivate;

//! Dialog for selecting channel's name.
class ChannelNameDialog
	:	public QDialog
{
	Q_OBJECT

public:
	ChannelNameDialog( QString & result,
		const QStringList & names,
		QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );

	~ChannelNameDialog();

private slots:
	//! Accepted.
	void accepted();
	//! Current index changed.
	void currentIndexChanged( int index );

private:
	//! Init.
	void init( const QStringList & names );

private:
	Q_DISABLE_COPY( ChannelNameDialog )

	QScopedPointer< ChannelNameDialogPrivate > d;
}; // class ChannelNameDialog

} /* namespace Globe */

#endif // GLOBE__CHANNEL_NAME_DIALOG_HPP__INCLUDED

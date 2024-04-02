
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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
	void ok();
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

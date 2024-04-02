
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SOURCE_MANUAL_DIALOG_HPP__INCLUDED
#define GLOBE__SOURCE_MANUAL_DIALOG_HPP__INCLUDED

// Qt include.
#include <QDialog>
#include <QScopedPointer>

// Como include.
#include <Como/Source>


namespace Globe {

class SourcesManager;


//
// SourceManualDialog
//

class SourceManualDialogPrivate;

//! Dialog for setting source parameters.
class SourceManualDialog
	:	public QDialog
{
	Q_OBJECT

public:
	SourceManualDialog( Como::Source & source, QString & channelName,
		QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );

	~SourceManualDialog();

private:
	//! Init.
	void init();

private slots:
	//! Accepted.
	void ok();
	//! Channel was set.
	void channelWasSet( int index );
	//! Name was set.
	void nameWasSet( const QString & text );
	//! Type was set.
	void typeWasSet( const QString & text );

private:
	Q_DISABLE_COPY( SourceManualDialog )

	QScopedPointer< SourceManualDialogPrivate > d;
}; // class SourceManualDialog

} /* namespace Globe */

#endif // GLOBE__SOURCE_MANUAL_DIALOG_HPP__INCLUDED

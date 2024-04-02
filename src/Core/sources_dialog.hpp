
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SOURCES_DIALOG_HPP__INCLUDED
#define GLOBE__SOURCES_DIALOG_HPP__INCLUDED

// Qt include.
#include <QDialog>
#include <QScopedPointer>

// Como include.
#include <Como/Source>


namespace Globe {

//
// SourcesDialog
//

class SourcesDialogPrivate;

//! Dialog for selecting the source.
class SourcesDialog
	:	public QDialog
{
	Q_OBJECT

public:
	SourcesDialog( Como::Source & source, QString & channelName,
		QWidget * parent = 0, Qt::WindowFlags flags = Qt::WindowFlags() );

	~SourcesDialog();

private:
	//! Init.
	void init();

private slots:
	//! Source selected.
	void sourceSelected( const Como::Source & source );
	//! Channel selected.
	void channelSelected( const QString & channelName );
	//! Set source manually.
	void setSourceManually();

private:
	Q_DISABLE_COPY( SourcesDialog )

	QScopedPointer< SourcesDialogPrivate > d;
}; // class SourcesDialog

} /* namespace Globe */

#endif // GLOBE__SOURCES_DIALOG_HPP__INCLUDED

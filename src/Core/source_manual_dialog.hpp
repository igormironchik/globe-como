
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

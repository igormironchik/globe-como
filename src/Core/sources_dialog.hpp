
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

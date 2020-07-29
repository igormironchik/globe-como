
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

#ifndef GLOBE__PROPERTIES_DIALOG_HPP__INCLUDED
#define GLOBE__PROPERTIES_DIALOG_HPP__INCLUDED

// Qt include.
#include <QDialog>
#include <QScopedPointer>

// Como include.
#include <Como/Source>


namespace Globe {

class PropertiesWidget;

//
// PropertiesDialog
//

class PropertiesDialogPrivate;

//! Dialog with properties.
class PropertiesDialog
	:	public QDialog
{
	Q_OBJECT

public:
	PropertiesDialog( const QString & cfgDirName, Como::Source::Type valueType,
		QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );
	~PropertiesDialog();

	//! \return Properties widget.
	PropertiesWidget * propertiesWidget();

private:
	//! Init.
	void init();

private slots:
	//! Wrong properties.
	void wrongProperties();
	//! Properties has been changed.
	void propertiesChanged();
	//! Open properties from file.
	void openProperties();

private:
	Q_DISABLE_COPY( PropertiesDialog )

	QScopedPointer< PropertiesDialogPrivate > d;
}; // class PropertiesDialog

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_DIALOG_HPP__INCLUDED


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

// Globe include.
#include <Core/properties_cfg_filename_dialog.hpp>
#include <Core/utils.hpp>

#include "ui_properties_cfg_filename_dialog.h"

// Qt include.
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QLineEdit>
#include <QLabel>
#include <QFile>


namespace Globe {

//
// PropertiesCfgFileNameDialogPrivate
//

class PropertiesCfgFileNameDialogPrivate {
public:
	PropertiesCfgFileNameDialogPrivate( QString & fileName,
		const QString & path )
		:	m_fileName( fileName )
		,	m_path( path )
	{
	}

	//! File name.
	QString & m_fileName;
	//! Path.
	QString m_path;
	//! Ui.
	Ui::PropertiesCfgFileNameDialog m_ui;
}; // class PropertiesCfgFileNameDialogPrivate


//
// PropertiesCfgFileNameDialog
//

PropertiesCfgFileNameDialog::PropertiesCfgFileNameDialog( QString & fileName,
	const QString & path,
	QWidget * parent, Qt::WindowFlags f )
	:	QDialog( parent, f )
	,	d( new PropertiesCfgFileNameDialogPrivate( fileName, path ) )
{
	init();
}

PropertiesCfgFileNameDialog::~PropertiesCfgFileNameDialog()
{
}

void
PropertiesCfgFileNameDialog::init()
{
	d->m_ui.setupUi( this );

	d->m_ui.m_directory->setText( d->m_path );

	d->m_ui.m_buttons->button( QDialogButtonBox::Ok )->setDefault( true );
	d->m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );

	connect( d->m_ui.m_buttons, &QDialogButtonBox::accepted,
		this, &PropertiesCfgFileNameDialog::accepted );
	connect( d->m_ui.m_buttons, &QDialogButtonBox::rejected,
		this, &PropertiesCfgFileNameDialog::reject );
	connect( d->m_ui.m_fileName, &QLineEdit::textChanged,
		this, &PropertiesCfgFileNameDialog::fileNameChanged );
	connect( d->m_ui.m_selectButton, &QToolButton::clicked,
		this, &PropertiesCfgFileNameDialog::selectFile );
}

void
PropertiesCfgFileNameDialog::selectFile()
{
	const QString fileName = QFileDialog::getOpenFileName( this,
		tr( "Open Configuration File" ), d->m_path,
		tr( "Configuration Files (*.cfg)" ) );

	if( !fileName.isEmpty() )
		d->m_ui.m_fileName->setText( relativeFilePath( fileName, d->m_path ) );
}

void
PropertiesCfgFileNameDialog::accepted()
{
	static const QString fileNameExtension = QLatin1String( ".cfg" );

	if( !d->m_fileName.endsWith( fileNameExtension ) )
		d->m_fileName.append( fileNameExtension );

	d->m_fileName = relativeFilePath( d->m_fileName, d->m_path );

	const QFile file( d->m_path + d->m_fileName );

	if( file.exists() )
	{
		const QMessageBox::StandardButton button =
			QMessageBox::question( 0, tr( "File already exists..." ),
			tr( "File already exists. Do you want to overwrite it?" ),
			QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel );

		if( button == QMessageBox::Cancel )
			return;
	}

	accept();
}

void
PropertiesCfgFileNameDialog::fileNameChanged( const QString & text )
{
	d->m_fileName = text;

	if( !text.isEmpty() )
		d->m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( true );
	else
		d->m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );
}

} /* namespace Globe */

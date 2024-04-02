
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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
		this, &PropertiesCfgFileNameDialog::ok );
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
PropertiesCfgFileNameDialog::ok()
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

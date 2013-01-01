
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2013 Igor Mironchik

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

// Globe include.
#include <Globe/properties_cfg_filename_dialog.hpp>
#include <Globe/utils.hpp>

#include "ui_properties_cfg_filename_dialog.h"

// Qt include.
#include <QtGui/QDialogButtonBox>
#include <QtGui/QPushButton>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QtCore/QFile>


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

	connect( d->m_ui.m_buttons, SIGNAL( accepted() ),
		this, SLOT( accepted() ) );
	connect( d->m_ui.m_buttons, SIGNAL( rejected() ),
		this, SLOT( reject() ) );
	connect( d->m_ui.m_fileName, SIGNAL( textChanged( const QString & ) ),
		this, SLOT( fileNameChanged( const QString & ) ) );
	connect( d->m_ui.m_selectButton, SIGNAL( clicked() ),
		this, SLOT( selectFile() ) );
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
			QMessageBox::question( this, tr( "File already exists..." ),
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


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
#include <Globe/Core/properties_dialog.hpp>
#include <Globe/Core/properties_widget.hpp>
#include <Globe/Core/properties.hpp>

// Qt include.
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

// QtConfFile include.
#include <QtConfFile/Exceptions>


namespace Globe {

//
// PropertiesDialogPrivate
//

class PropertiesDialogPrivate {
public:
	PropertiesDialogPrivate( const QString & cfgDirName,
		Como::Source::Type valueType )
		:	m_cfgDirName( cfgDirName )
		,	m_valueType( valueType )
		,	m_properties( 0 )
		,	m_buttons( 0 )
	{
	}

	//! Configuration directory.
	QString m_cfgDirName;
	//! Type of the value.
	Como::Source::Type m_valueType;
	//! Properties widget.
	PropertiesWidget * m_properties;
	//! Buttons.
	QDialogButtonBox * m_buttons;
}; // class PropertiesDialogPrivate


//
// PropertiesDialog
//

PropertiesDialog::PropertiesDialog( const QString & cfgDirName,
	Como::Source::Type valueType,
	QWidget * parent, Qt::WindowFlags f )
	:	QDialog( parent, f )
	,	d( new PropertiesDialogPrivate( cfgDirName, valueType ) )
{
	init();
}

PropertiesDialog::~PropertiesDialog()
{
}

PropertiesWidget *
PropertiesDialog::propertiesWidget()
{
	return d->m_properties;
}

void
PropertiesDialog::init()
{
	resize( 450, 250 );
	setWindowTitle( tr( "Properties Dialog" ) );

	QVBoxLayout * layout = new QVBoxLayout( this );

	d->m_properties = new PropertiesWidget( d->m_valueType, this );

	layout->addWidget( d->m_properties );

	QFrame * line = new QFrame( this );
	line->setFrameShape( QFrame::HLine );
	line->setFrameShadow( QFrame::Sunken );

	layout->addWidget( line );

	d->m_buttons = new QDialogButtonBox( this );
	d->m_buttons->setOrientation( Qt::Horizontal );
	d->m_buttons->setStandardButtons( QDialogButtonBox::Ok |
		QDialogButtonBox::Cancel );

	layout->addWidget( d->m_buttons );

	d->m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );

	QPushButton * openButton = new QPushButton( tr( "Open" ), this );

	d->m_buttons->addButton( openButton, QDialogButtonBox::ActionRole );

	connect( d->m_buttons, SIGNAL( accepted() ),
		this, SLOT( accept() ) );
	connect( d->m_buttons, SIGNAL( rejected() ),
		this, SLOT( reject() ) );
	connect( d->m_properties, SIGNAL( wrongProperties() ),
		this, SLOT( wrongProperties() ) );
	connect( d->m_properties, SIGNAL( changed() ),
		this, SLOT( propertiesChanged() ) );
	connect( openButton, SIGNAL( clicked() ),
		this, SLOT( openProperties() ) );
}

void
PropertiesDialog::wrongProperties()
{
	d->m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );
}

void
PropertiesDialog::propertiesChanged()
{
	d->m_buttons->button( QDialogButtonBox::Ok )->setEnabled( true );
}

void
PropertiesDialog::openProperties()
{
	const QString fileName = QFileDialog::getOpenFileName( this,
		tr( "Select properties configuration file..." ),
		d->m_cfgDirName,
		tr( "Configuration Files (*.cfg)" )  );

	if( !fileName.isEmpty() )
	{
		try {
			Properties p;

			readPropertiesConfiguration( fileName, p, d->m_valueType );

			d->m_properties->setProperties( p );
		}
		catch( const QtConfFile::Exception & x )
		{
			QMessageBox::critical( 0,
				tr( "Unable to load properties configuration..." ),
				tr( "Unable to load properties configuration...\n\n%1" )
					.arg( x.whatAsQString() ) );
		}
	}
}

} /* namespace Globe */

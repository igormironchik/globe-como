
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/properties_dialog.hpp>
#include <Core/properties_widget.hpp>
#include <Core/properties.hpp>

// Qt include.
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

// cfgfile include.
#include <cfgfile/all.hpp>


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

	connect( d->m_buttons, &QDialogButtonBox::accepted,
		this, &PropertiesDialog::accept );
	connect( d->m_buttons, &QDialogButtonBox::rejected,
		this, &PropertiesDialog::reject );
	connect( d->m_properties, &PropertiesWidget::wrongProperties,
		this, &PropertiesDialog::wrongProperties );
	connect( d->m_properties, &PropertiesWidget::changed,
		this, &PropertiesDialog::propertiesChanged );
	connect( openButton, &QPushButton::clicked,
		this, &PropertiesDialog::openProperties );
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
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			QMessageBox::critical( 0,
				tr( "Unable to load properties configuration..." ),
				tr( "Unable to load properties configuration...\n\n%1" )
					.arg( x.desc() ) );
		}
	}
}

} /* namespace Globe */

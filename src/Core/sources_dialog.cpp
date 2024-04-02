
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/sources_dialog.hpp>
#include <Core/sources_widget.hpp>
#include <Core/source_manual_dialog.hpp>

// Qt include.
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QSpacerItem>
#include <QPushButton>


namespace Globe {

//
// SourcesDialogPrivate
//

class SourcesDialogPrivate {
public:
	SourcesDialogPrivate( Como::Source & source, QString & channelName )
		:	m_source( source )
		,	m_channelName( channelName )
		,	m_widget( 0 )
		,	m_buttons( 0 )
		,	m_setManuallyButton( 0 )
	{
	}

	//! Source.
	Como::Source & m_source;
	//! Channel's name.
	QString & m_channelName;
	//! Widget.
	SourcesWidget * m_widget;
	//! Buttons.
	QDialogButtonBox * m_buttons;
	//! Set source manually button.
	QPushButton * m_setManuallyButton;
}; // class SourcesDialogPrivate


//
// SourcesDialog
//

SourcesDialog::SourcesDialog( Como::Source & source, QString & channelName,
	QWidget * parent, Qt::WindowFlags flags )
	:	QDialog( parent, flags )
	,	d( new SourcesDialogPrivate( source, channelName ) )
{
	init();
}

SourcesDialog::~SourcesDialog()
{
}


void
SourcesDialog::init()
{
	setWindowTitle( tr( "Select source..." ) );

	QVBoxLayout * layout = new QVBoxLayout( this );

	d->m_widget = new SourcesWidget( this );

	QSpacerItem * spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
		QSizePolicy::Expanding );

	QFrame * line = new QFrame( this );
	line->setFrameStyle( QFrame::HLine | QFrame::Sunken );

	d->m_buttons = new QDialogButtonBox(
		QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
		Qt::Horizontal, this );

	d->m_buttons->button( QDialogButtonBox::Ok )->setDefault( true );
	d->m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );

	d->m_setManuallyButton = new QPushButton( tr( "Set Manually" ), this );
	d->m_buttons->addButton( d->m_setManuallyButton,
		QDialogButtonBox::ActionRole );

	layout->addWidget( d->m_widget );
	layout->addSpacerItem( spacer );
	layout->addWidget( line );
	layout->addWidget( d->m_buttons );

	connect( d->m_widget, &SourcesWidget::sourceSelected,
		this, &SourcesDialog::sourceSelected );

	connect( d->m_widget, &SourcesWidget::channelSelected,
		this, &SourcesDialog::channelSelected );

	connect( d->m_buttons, &QDialogButtonBox::accepted,
		this, &SourcesDialog::accept );

	connect( d->m_buttons, &QDialogButtonBox::rejected,
		this, &SourcesDialog::reject );

	connect( d->m_setManuallyButton, &QPushButton::clicked,
		this, &SourcesDialog::setSourceManually );
}

void
SourcesDialog::sourceSelected( const Como::Source & source )
{
	d->m_source = source;
	d->m_channelName = d->m_widget->channelName();

	d->m_buttons->button( QDialogButtonBox::Ok )->setEnabled( true );
}

void
SourcesDialog::channelSelected( const QString & channelName )
{
	Q_UNUSED( channelName )

	d->m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );
}

void
SourcesDialog::setSourceManually()
{
	SourceManualDialog dialog( d->m_source, d->m_channelName, this );

	if( dialog.exec() == QDialog::Accepted )
		accept();
}

} /* namespace Globe */

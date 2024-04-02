
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/sounds_disabled_to_dialog.hpp>

#include "ui_sounds_disabled_to_dialog.h"

// Qt include.
#include <QDialogButtonBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QRegularExpression>


namespace Globe {

//
// DisableSoundToDialogPrivate
//

class DisableSoundToDialogPrivate {
public:
	explicit DisableSoundToDialogPrivate( QDateTime & to )
		:	m_to( to )
		,	m_group( 0 )
		,	m_formatRegExp(
				QLatin1String( "^((\\d+)[dD])?((\\d+)[hH])?((\\d+)[mM])?$" ) )
	{
	}

	//! Ui.
	Ui::DisabledToDialog m_ui;
	//! Date and time.
	QDateTime & m_to;
	//! Button group.
	QButtonGroup * m_group;
	//! Color of normal text.
	QColor m_textColor;
	//! Regular expression for checking the format of date and time.
	QRegularExpression m_formatRegExp;
}; // class DisableSoundToDialogPrivate


//
// DisableSoundToDialog
//

DisableSoundToDialog::DisableSoundToDialog( QDateTime & to, QWidget * parent,
	Qt::WindowFlags f )
	:	QDialog( parent, f )
	,	d( new DisableSoundToDialogPrivate( to ) )
{
	init();
}

DisableSoundToDialog::~DisableSoundToDialog()
{
}

void
DisableSoundToDialog::setDateTimeToCurrent()
{
	d->m_ui.m_actualDateTimeEdit->setDateTime(
		QDateTime::currentDateTime() );
}

void
DisableSoundToDialog::acceptButtonClicked()
{
	if( d->m_ui.m_toActualTimeRadioButton->isChecked() )
		d->m_to = d->m_ui.m_actualDateTimeEdit->dateTime();
	else
	{
		const auto match = d->m_formatRegExp.match(
			d->m_ui.m_relativeDateTimeEdit->text(), 0,
			QRegularExpression::PartialPreferCompleteMatch );

		if( match.hasMatch() )
		{
			int days = 0;
			int hours = 0;
			int minutes = 0;

			const QString daysString = match.captured( 2 );
			const QString hoursString = match.captured( 4 );
			const QString minutesString = match.captured( 6 );

			if( !daysString.isEmpty() )
				days = daysString.toInt();

			if( !hoursString.isEmpty() )
				hours = hoursString.toInt();

			if( !minutesString.isEmpty() )
				minutes = minutesString.toInt();

			d->m_to = QDateTime::currentDateTime();

			d->m_to = d->m_to.addDays( days );
			d->m_to = d->m_to.addSecs( hours * 60 * 60 + minutes * 60 );
		}
		else
			reject();
	}

	accept();
}

void
DisableSoundToDialog::actualDateTimeChanged( const QDateTime & dt )
{
	Q_UNUSED( dt )

	d->m_ui.m_toActualTimeRadioButton->setChecked( true );

	d->m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( true );
}

void
DisableSoundToDialog::relativeDateTimeChanged( const QString & dt )
{
	d->m_ui.m_toRelativeTimeRadioButton->setChecked( true );

	if( !checkCorrectnessOfFormat( dt ) )
	{
		highlightError();
		d->m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );
	}
	else
	{
		highlightOk();
		d->m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( true );
	}
}

void
DisableSoundToDialog::init()
{
	d->m_ui.setupUi( this );

	d->m_ui.m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );

	setDateTimeToCurrent();

	d->m_group = new QButtonGroup( this );
	d->m_group->addButton( d->m_ui.m_toActualTimeRadioButton );
	d->m_group->addButton( d->m_ui.m_toRelativeTimeRadioButton );

	d->m_textColor = d->m_ui.m_relativeDateTimeEdit->palette()
		.color( QPalette::Text );

	connect( d->m_ui.m_currentDateTimeButton, &QToolButton::clicked,
		this, &DisableSoundToDialog::setDateTimeToCurrent );

	connect( d->m_ui.m_buttons->button( QDialogButtonBox::Ok ),
		&QPushButton::clicked,
		this, &DisableSoundToDialog::acceptButtonClicked );

	connect( d->m_ui.m_actualDateTimeEdit, &QDateTimeEdit::dateTimeChanged,
		this, &DisableSoundToDialog::actualDateTimeChanged );

	connect( d->m_ui.m_relativeDateTimeEdit, &QLineEdit::textChanged,
		this, &DisableSoundToDialog::relativeDateTimeChanged );
}

bool
DisableSoundToDialog::checkCorrectnessOfFormat( const QString & dt )
{
	const auto match = d->m_formatRegExp.match( dt, 0,
		QRegularExpression::PartialPreferCompleteMatch );

	return ( match.hasMatch() && !match.hasPartialMatch() );
}

void
DisableSoundToDialog::highlightError()
{
	QPalette palette = d->m_ui.m_relativeDateTimeEdit->palette();
	palette.setColor( QPalette::Text, Qt::red );
	d->m_ui.m_relativeDateTimeEdit->setPalette( palette );
}

void
DisableSoundToDialog::highlightOk()
{
	QPalette palette = d->m_ui.m_relativeDateTimeEdit->palette();
	palette.setColor( QPalette::Text, d->m_textColor );
	d->m_ui.m_relativeDateTimeEdit->setPalette( palette );
}

} /* namespace Globe */

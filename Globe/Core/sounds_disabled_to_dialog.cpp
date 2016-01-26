
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

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
#include <Globe/Core/sounds_disabled_to_dialog.hpp>

#include "ui_sounds_disabled_to_dialog.h"

// Qt include.
#include <QDialogButtonBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QRegExp>


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
	QRegExp m_formatRegExp;
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
		const int pos = d->m_formatRegExp.indexIn(
			d->m_ui.m_relativeDateTimeEdit->text() );

		if( pos > -1 )
		{
			int days = 0;
			int hours = 0;
			int minutes = 0;

			const QString daysString = d->m_formatRegExp.cap( 2 );
			const QString hoursString = d->m_formatRegExp.cap( 4 );
			const QString minutesString = d->m_formatRegExp.cap( 6 );

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
	return d->m_formatRegExp.exactMatch( dt );
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

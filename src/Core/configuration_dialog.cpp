
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/configuration_dialog.hpp>
#include <Core/color_for_level.hpp>
#include <Core/log.hpp>
#include <Core/log_cfg.hpp>
#include <Core/utils.hpp>
#include <Core/sounds_cfg.hpp>
#include <Core/sounds.hpp>
#include <Core/configuration.hpp>

#include "ui_configuration_dialog.h"

// Qt include.
#include <QStackedWidget>
#include <QListWidget>
#include <QDialogButtonBox>
#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QToolButton>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>


namespace Globe {

//
// ConfigurationDialogPrivate
//

class ConfigurationDialogPrivate {
public:
	ConfigurationDialogPrivate( )
	{
	}

	//! Ui.
	Ui::ConfigurationDialog m_ui;
}; // class ConfigurationDialogPrivate


//
// ConfigurationDialog
//

ConfigurationDialog::ConfigurationDialog( QWidget * parent, Qt::WindowFlags f )
	:	QDialog( parent, f )
	,	d( new ConfigurationDialogPrivate )
{
	init();
}

ConfigurationDialog::~ConfigurationDialog()
{
}

void
ConfigurationDialog::init()
{
	d->m_ui.setupUi( this );

	connect( d->m_ui.m_buttons, &QDialogButtonBox::accepted,
		this, &ConfigurationDialog::newSettingsAccepted );

	connect( d->m_ui.m_menu, &QListWidget::currentItemChanged,
		this, &ConfigurationDialog::changePage );

	connect( d->m_ui.m_resetColorsToDefaultSettings, &QPushButton::clicked,
		this, &ConfigurationDialog::resetColorsToDefaultValues );

	connect( d->m_ui.m_enableSourcesLog, &QCheckBox::stateChanged,
		this, &ConfigurationDialog::sourcesLogStateChanged );

	connect( d->m_ui.m_enableCriticalSound, &QCheckBox::stateChanged,
		this, &ConfigurationDialog::criticalSoundStateChanged );

	connect( d->m_ui.m_enableErrorSound, &QCheckBox::stateChanged,
		this, &ConfigurationDialog::errorSoundStateChanged );

	connect( d->m_ui.m_enableWarningSound, &QCheckBox::stateChanged,
		this, &ConfigurationDialog::warningSoundStateChanged );

	connect( d->m_ui.m_enableDebugSound, &QCheckBox::stateChanged,
		this, &ConfigurationDialog::debugSoundStateChanged );

	connect( d->m_ui.m_enableInfoSound, &QCheckBox::stateChanged,
		this, &ConfigurationDialog::infoSoundStateChanged );

	connect( d->m_ui.m_criticalSoundButton, &QToolButton::clicked,
		this, &ConfigurationDialog::criticalSoundButtonClicked );

	connect( d->m_ui.m_errorSoundButton, &QToolButton::clicked,
		this, &ConfigurationDialog::errorSoundButtonClicked );

	connect( d->m_ui.m_warningSoundButton, &QToolButton::clicked,
		this, &ConfigurationDialog::warningSoundButtonClicked );

	connect( d->m_ui.m_debugSoundButton, &QToolButton::clicked,
		this, &ConfigurationDialog::debugSoundButtonClicked );

	connect( d->m_ui.m_infoSoundButton, &QToolButton::clicked,
		this, &ConfigurationDialog::infoSoundButtonClicked );

	connect( d->m_ui.m_clearEventLogButton, &QToolButton::clicked,
		this, &ConfigurationDialog::clearEventLog );

	connect( d->m_ui.m_clearSourcesLogButton, &QToolButton::clicked,
		this, &ConfigurationDialog::clearSourcesLog );

	checkDirAndCreateIfNotExists( Configuration::instance().path(),
		QLatin1String( "sounds" ) );
}

void
ConfigurationDialog::initUiWithSettings()
{
	d->m_ui.m_noneColorPicker->setColor( ColorForLevel::instance().color( None ) );
	d->m_ui.m_criticalColorPicker->setColor( ColorForLevel::instance().color( Critical ) );
	d->m_ui.m_errorColorPicker->setColor( ColorForLevel::instance().color( Error ) );
	d->m_ui.m_warningColorPicker->setColor( ColorForLevel::instance().color( Warning ) );
	d->m_ui.m_debugColorPicker->setColor( ColorForLevel::instance().color( Debug ) );
	d->m_ui.m_infoColorPicker->setColor( ColorForLevel::instance().color( Info ) );
	d->m_ui.m_deregisteredColorPicker->setColor(
		ColorForLevel::instance().deregisteredColor() );
	d->m_ui.m_disconnectedColorPicker->setColor(
		ColorForLevel::instance().disconnectedColor() );

	if( Log::instance().cfg().isEventLogEnabled() )
		d->m_ui.m_enableEventsLog->setChecked( true );

	if( Log::instance().cfg().isSourcesLogEnabled() )
		d->m_ui.m_enableSourcesLog->setChecked( true );

	d->m_ui.m_sourcesLogDays->setValue(
		Log::instance().cfg().sourcesLogDays() );

	SoundsCfg soundsCfg = Sounds::instance().cfg();

	if( soundsCfg.isCriticalSoundEnabled() )
	{
		d->m_ui.m_enableCriticalSound->setChecked( true );
		d->m_ui.m_criticalSoundLine->setText( soundsCfg.criticalSoundFile() );
	}

	if( soundsCfg.isErrorSoundEnabled() )
	{
		d->m_ui.m_enableErrorSound->setChecked( true );
		d->m_ui.m_errorSoundLine->setText( soundsCfg.errorSoundFile() );
	}

	if( soundsCfg.isWarningSoundEnabled() )
	{
		d->m_ui.m_enableWarningSound->setChecked( true );
		d->m_ui.m_warningSoundLine->setText( soundsCfg.warningSoundFile() );
	}

	if( soundsCfg.isDebugSoundEnabled() )
	{
		d->m_ui.m_enableDebugSound->setChecked( true );
		d->m_ui.m_debugSoundLine->setText( soundsCfg.debugSoundFile() );
	}

	if( soundsCfg.isInfoSoundEnabled() )
	{
		d->m_ui.m_enableInfoSound->setChecked( true );
		d->m_ui.m_infoSoundLine->setText( soundsCfg.infoSoundFile() );
	}
}

void
ConfigurationDialog::changePage( QListWidgetItem * current,
	QListWidgetItem * previous )
{
	if ( !current )
		current = previous;

	d->m_ui.m_stack->setCurrentIndex( d->m_ui.m_menu->row( current ) );
}

void
ConfigurationDialog::newSettingsAccepted()
{
	const QColor none = d->m_ui.m_noneColorPicker->color();
	const QColor critical = d->m_ui.m_criticalColorPicker->color();
	const QColor error = d->m_ui.m_errorColorPicker->color();
	const QColor warning = d->m_ui.m_warningColorPicker->color();
	const QColor debug = d->m_ui.m_debugColorPicker->color();
	const QColor info = d->m_ui.m_infoColorPicker->color();
	const QColor deregistered = d->m_ui.m_deregisteredColorPicker->color();
	const QColor disconnected = d->m_ui.m_disconnectedColorPicker->color();

	ColorForLevel::instance().setColors( none, critical, error, warning,
		debug, info, deregistered, disconnected );

	Log::instance().enableEventsLog(
		d->m_ui.m_enableEventsLog->isChecked() );

	Log::instance().enableSourcesLog(
		d->m_ui.m_enableSourcesLog->isChecked() );

	if( d->m_ui.m_enableSourcesLog->isChecked() )
		Log::instance().setSourcesLogDays(
			d->m_ui.m_sourcesLogDays->value() );

	SoundsCfg soundsCfg;

	if( d->m_ui.m_enableCriticalSound->isChecked() &&
		!d->m_ui.m_criticalSoundLine->text().isEmpty() )
			soundsCfg.setCriticalSoundFile( d->m_ui.m_criticalSoundLine->text() );

	if( d->m_ui.m_enableErrorSound->isChecked() &&
		!d->m_ui.m_errorSoundLine->text().isEmpty() )
			soundsCfg.setErrorSoundFile( d->m_ui.m_errorSoundLine->text() );

	if( d->m_ui.m_enableWarningSound->isChecked() &&
		!d->m_ui.m_warningSoundLine->text().isEmpty() )
			soundsCfg.setWarningSoundFile( d->m_ui.m_warningSoundLine->text() );

	if( d->m_ui.m_enableDebugSound->isChecked() &&
		!d->m_ui.m_debugSoundLine->text().isEmpty() )
			soundsCfg.setDebugSoundFile( d->m_ui.m_debugSoundLine->text() );

	if( d->m_ui.m_enableInfoSound->isChecked() &&
		!d->m_ui.m_infoSoundLine->text().isEmpty() )
			soundsCfg.setInfoSoundFile( d->m_ui.m_infoSoundLine->text() );

	Sounds::instance().setCfg( soundsCfg );

	accept();
}

void
ConfigurationDialog::resetColorsToDefaultValues()
{
	d->m_ui.m_noneColorPicker->setColor( defaultNoneColor );
	d->m_ui.m_criticalColorPicker->setColor( defaultCriticalColor );
	d->m_ui.m_errorColorPicker->setColor( defaultErrorColor );
	d->m_ui.m_warningColorPicker->setColor( defaultWarningColor );
	d->m_ui.m_debugColorPicker->setColor( defaultDebugColor );
	d->m_ui.m_infoColorPicker->setColor( defaultInfoColor );
	d->m_ui.m_deregisteredColorPicker->setColor( defaultDeregisteredColor );
	d->m_ui.m_disconnectedColorPicker->setColor( defaultDisconnectedColor );
}

void
ConfigurationDialog::sourcesLogStateChanged( int state )
{
	if( state == Qt::Checked )
	{
		d->m_ui.m_sourcesLogDays->setEnabled( true );
		d->m_ui.m_sourcesLogDaysLabel->setEnabled( true );
	}
	else
	{
		d->m_ui.m_sourcesLogDays->setEnabled( false );
		d->m_ui.m_sourcesLogDaysLabel->setEnabled( false );
	}
}

void
ConfigurationDialog::soundCheckBoxStateChanged( int state,
	QLineEdit * line, QToolButton * button )
{
	if( state == Qt::Checked )
	{
		line->setEnabled( true );
		button->setEnabled( true );
	}
	else
	{
		line->setEnabled( false );
		button->setEnabled( false );
	}
}

void
ConfigurationDialog::criticalSoundStateChanged( int state )
{
	soundCheckBoxStateChanged( state, d->m_ui.m_criticalSoundLine,
		d->m_ui.m_criticalSoundButton );
}

void
ConfigurationDialog::errorSoundStateChanged( int state )
{
	soundCheckBoxStateChanged( state, d->m_ui.m_errorSoundLine,
		d->m_ui.m_errorSoundButton );
}

void
ConfigurationDialog::warningSoundStateChanged( int state )
{
	soundCheckBoxStateChanged( state, d->m_ui.m_warningSoundLine,
		d->m_ui.m_warningSoundButton );
}

void
ConfigurationDialog::debugSoundStateChanged( int state )
{
	soundCheckBoxStateChanged( state, d->m_ui.m_debugSoundLine,
		d->m_ui.m_debugSoundButton );
}

void
ConfigurationDialog::infoSoundStateChanged( int state )
{
	soundCheckBoxStateChanged( state, d->m_ui.m_infoSoundLine,
		d->m_ui.m_infoSoundButton );
}

void
ConfigurationDialog::soundSelectButtonClicked( QLineEdit * line )
{
	QString fileName = QFileDialog::getOpenFileName( this,
		tr( "Open Sound" ),
		Configuration::instance().path() + QStringLiteral( "sounds" ),
		tr( "Sound Files (*.wav *.mp3 *.ogg)" ) );

	if( !fileName.isEmpty() )
		line->setText( relativeFilePath( fileName, Configuration::instance().path() ) );
}

void
ConfigurationDialog::criticalSoundButtonClicked()
{
	soundSelectButtonClicked( d->m_ui.m_criticalSoundLine );
}

void
ConfigurationDialog::errorSoundButtonClicked()
{
	soundSelectButtonClicked( d->m_ui.m_errorSoundLine );
}

void
ConfigurationDialog::warningSoundButtonClicked()
{
	soundSelectButtonClicked( d->m_ui.m_warningSoundLine );
}

void
ConfigurationDialog::debugSoundButtonClicked()
{
	soundSelectButtonClicked( d->m_ui.m_debugSoundLine );
}

void
ConfigurationDialog::infoSoundButtonClicked()
{
	soundSelectButtonClicked( d->m_ui.m_infoSoundLine );
}

void
ConfigurationDialog::clearEventLog()
{
	Log::instance().clearEventsLog();

	QMessageBox::information( this, tr( "Event log was cleared..." ),
		tr( "Event log was cleared." ) );
}

void
ConfigurationDialog::clearSourcesLog()
{
	Log::instance().clearSourcesLog();

	QMessageBox::information( this, tr( "Sources log was cleared..." ),
		tr( "Sources log was cleared." ) );
}

} /* namespace Globe */

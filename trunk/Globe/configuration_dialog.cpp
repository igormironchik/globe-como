
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
#include <Globe/configuration_dialog.hpp>
#include <Globe/color_for_level.hpp>
#include <Globe/log.hpp>
#include <Globe/log_cfg.hpp>
#include <Globe/utils.hpp>
#include <Globe/sounds_cfg.hpp>
#include <Globe/sounds.hpp>

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

	connect( d->m_ui.m_buttons, SIGNAL( accepted() ),
		this, SLOT( newSettingsAccepted() ) );

	connect( d->m_ui.m_menu,
		SIGNAL( currentItemChanged( QListWidgetItem *, QListWidgetItem * ) ),
		this, SLOT( changePage( QListWidgetItem *, QListWidgetItem * ) ) );

	connect( d->m_ui.m_resetColorsToDefaultSettings,
		SIGNAL( clicked() ), this, SLOT( resetColorsToDefaultValues() ) );

	connect( d->m_ui.m_enableSourcesLog, SIGNAL( stateChanged( int ) ),
		this, SLOT( sourcesLogStateChanged( int ) ) );

	connect( d->m_ui.m_enableCriticalSound,
		SIGNAL( stateChanged( int ) ), this,
		SLOT( criticalSoundStateChanged( int ) ) );

	connect( d->m_ui.m_enableErrorSound,
		SIGNAL( stateChanged( int ) ), this,
		SLOT( errorSoundStateChanged( int ) ) );

	connect( d->m_ui.m_enableWarningSound,
		SIGNAL( stateChanged( int ) ), this,
		SLOT( warningSoundStateChanged( int ) ) );

	connect( d->m_ui.m_enableDebugSound,
		SIGNAL( stateChanged( int ) ), this,
		SLOT( debugSoundStateChanged( int ) ) );

	connect( d->m_ui.m_enableInfoSound,
		SIGNAL( stateChanged( int ) ), this,
		SLOT( infoSoundStateChanged( int ) ) );

	connect( d->m_ui.m_criticalSoundButton, SIGNAL( clicked() ),
		this, SLOT( criticalSoundButtonClicked() ) );

	connect( d->m_ui.m_errorSoundButton, SIGNAL( clicked() ),
		this, SLOT( errorSoundButtonClicked() ) );

	connect( d->m_ui.m_warningSoundButton, SIGNAL( clicked() ),
		this, SLOT( warningSoundButtonClicked() ) );

	connect( d->m_ui.m_debugSoundButton, SIGNAL( clicked() ),
		this, SLOT( debugSoundButtonClicked() ) );

	connect( d->m_ui.m_infoSoundButton, SIGNAL( clicked() ),
		this, SLOT( infoSoundButtonClicked() ) );

	connect( d->m_ui.m_clearEventLogButton, SIGNAL( clicked() ),
		this, SLOT( clearEventLog() ) );

	connect( d->m_ui.m_clearSourcesLogButton, SIGNAL( clicked() ),
		this, SLOT( clearSourcesLog() ) );

	checkDirAndCreateIfNotExists( QLatin1String( "./etc" ),
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
		"./etc/sounds",
		tr( "Sound Files (*.wav *.mp3 *.ogg)" ) );

	if( !fileName.isEmpty() )
		line->setText( relativeFilePath( fileName ) );
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
}

void
ConfigurationDialog::clearSourcesLog()
{
	Log::instance().clearSourcesLog();
}

} /* namespace Globe */

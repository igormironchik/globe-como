
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/log_event_selector.hpp>
#include <Core/launch_time.hpp>

#include "ui_log_event_selector.h"

// Qt include.
#include <QDateTimeEdit>


namespace Globe {

//
// LogEventSelectorCfg
//

LogEventSelectorCfg::LogEventSelectorCfg()
{
}

const QDateTime &
LogEventSelectorCfg::startDateTime() const
{
	return m_startDateTime;
}

void
LogEventSelectorCfg::setStartDateTime( const QDateTime & dt )
{
	m_startDateTime = dt;
}

const QDateTime &
LogEventSelectorCfg::endDateTime() const
{
	return m_endDateTime;
}

void
LogEventSelectorCfg::setEndDateTime( const QDateTime & dt )
{
	m_endDateTime = dt;
}


//
// LogEventSelectorPrivate
//

class LogEventSelectorPrivate {
public:
	LogEventSelectorPrivate()
	{
	}

	//! Ui.
	Ui::LogEventSelector m_ui;
	//! Configuration.
	LogEventSelectorCfg m_cfg;
}; // class LogEventSelectorPrivate


//
// LogEventSelector
//

LogEventSelector::LogEventSelector( QWidget * parent, Qt::WindowFlags f )
	:	QWidget( parent, f )
	,	d( new LogEventSelectorPrivate )
{
	init();
}

LogEventSelector::~LogEventSelector()
{
}

void
LogEventSelector::init()
{
	d->m_ui.setupUi( this );

	connect( d->m_ui.m_from, &QDateTimeEdit::dateTimeChanged,
		this, &LogEventSelector::startDateTimeChanged );
	connect( d->m_ui.m_to, &QDateTimeEdit::dateTimeChanged,
		this, &LogEventSelector::endDateTimeChanged );
	connect( d->m_ui.m_fromLaunchButton, &QToolButton::clicked,
		this, &LogEventSelector::setStartTimeToLaunchTime );
	connect( d->m_ui.m_toCurrentTimeButton, &QToolButton::clicked,
		this, &LogEventSelector::setEndTimeToCurrent );
}

const LogEventSelectorCfg &
LogEventSelector::cfg() const
{
	return d->m_cfg;
}

SelectQueryNavigation *
LogEventSelector::navigationWidget()
{
	return d->m_ui.m_navigation;
}

QDateTime
LogEventSelector::startDateTime() const
{
	return d->m_ui.m_from->dateTime();
}

QDateTime
LogEventSelector::endDateTime() const
{
	return d->m_ui.m_to->dateTime();
}

void
LogEventSelector::startDateTimeChanged( const QDateTime & dt )
{
	d->m_cfg.setStartDateTime( dt );
}

void
LogEventSelector::endDateTimeChanged( const QDateTime & dt )
{
	d->m_cfg.setEndDateTime( dt );
}

void
LogEventSelector::setStartTimeToLaunchTime()
{
	d->m_ui.m_from->setDateTime( LaunchTime::instance().launchTime() );
}

void
LogEventSelector::setEndTimeToCurrent()
{
	d->m_ui.m_to->setDateTime( QDateTime::currentDateTime() );
}

} /* namespace Globe */

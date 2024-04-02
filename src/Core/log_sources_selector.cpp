
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/log_sources_selector.hpp>
#include <Core/launch_time.hpp>
#include <Core/channels.hpp>
#include <Core/sources.hpp>

#include "ui_log_sources_selector.h"

// Qt include.
#include <QDateTimeEdit>
#include <QComboBox>
#include <QMap>
#include <QList>


namespace Globe {

//
// LogSourcesSelectorPrivate
//

class LogSourcesSelectorPrivate {
public:
	LogSourcesSelectorPrivate()
	{
	}

	//! Ui.
	Ui::LogSourcesSelector m_ui;
	//! Types and names.
	QMap< QString, QStringList > m_typesNames;
}; // class LogSourcesSelectorPrivate


//
// LogSourcesSelector
//

LogSourcesSelector::LogSourcesSelector( QWidget * parent, Qt::WindowFlags f )
	:	QWidget( parent, f )
	,	d( new LogSourcesSelectorPrivate )
{
	init();
}

LogSourcesSelector::~LogSourcesSelector()
{
}

void
LogSourcesSelector::init()
{
	d->m_ui.setupUi( this );

	d->m_ui.m_channel->addItems( SourcesManager::instance().channelsNames() );

	connect( d->m_ui.m_fromLaunchButton, &QToolButton::clicked,
		this, &LogSourcesSelector::setStartTimeToLaunchTime );
	connect( d->m_ui.m_toCurrentTimeButton, &QToolButton::clicked,
		this, &LogSourcesSelector::setEndTimeToCurrent );
	connect( d->m_ui.m_channel, &QComboBox::currentTextChanged,
		this, &LogSourcesSelector::channelNameChanged );
	connect( &ChannelsManager::instance(), &ChannelsManager::channelCreated,
		this, &LogSourcesSelector::chanelCreated );
	connect( &ChannelsManager::instance(), &ChannelsManager::channelRemoved,
		this, &LogSourcesSelector::channelRemoved );
	connect( &SourcesManager::instance(), &SourcesManager::newSource,
		this, &LogSourcesSelector::newSource );
	connect( d->m_ui.m_type, &QComboBox::currentTextChanged,
		this, &LogSourcesSelector::typeChanged );
}

SelectQueryNavigation *
LogSourcesSelector::navigationWidget()
{
	return d->m_ui.m_navigation;
}

QDateTime
LogSourcesSelector::startDateTime() const
{
	return d->m_ui.m_from->dateTime();
}

QDateTime
LogSourcesSelector::endDateTime() const
{
	return d->m_ui.m_to->dateTime();
}

QString
LogSourcesSelector::channelName() const
{
	return d->m_ui.m_channel->currentText();
}

QString
LogSourcesSelector::typeName() const
{
	return d->m_ui.m_type->currentText();
}

QString
LogSourcesSelector::sourceName() const
{
	return d->m_ui.m_name->currentText();
}

void
LogSourcesSelector::setStartTimeToLaunchTime()
{
	d->m_ui.m_from->setDateTime( LaunchTime::instance().launchTime() );
}

void
LogSourcesSelector::setEndTimeToCurrent()
{
	d->m_ui.m_to->setDateTime( QDateTime::currentDateTime() );
}

void
LogSourcesSelector::channelNameChanged( const QString & text )
{
	d->m_typesNames.clear();

	clearNames();

	clearTypes();

	if( SourcesManager::instance().channelsNames().contains( text ) )
	{
		const QList< Como::Source > sources =
			SourcesManager::instance().sources( text );

		foreach( const Como::Source & s, sources )
		{
			d->m_typesNames[ s.typeName() ].append( s.name() );

			d->m_ui.m_type->addItem( s.typeName() );
		}
	}
}

void
LogSourcesSelector::chanelCreated( Globe::Channel * ch )
{
	d->m_ui.m_channel->addItem( ch->name() );
}

void
LogSourcesSelector::channelRemoved( Globe::Channel * ch )
{
	const int index = d->m_ui.m_channel->findText( ch->name() );

	if( index != -1 )
		d->m_ui.m_channel->removeItem( index );
}

void
LogSourcesSelector::newSource( const Como::Source & source,
	const QString & channelName )
{
	if( d->m_ui.m_channel->currentText() == channelName )
	{
		if( !d->m_typesNames[ source.typeName() ].contains( source.name() ) )
		{
			d->m_typesNames[ source.typeName() ].append( source.name() );
			d->m_ui.m_type->addItem( source.typeName() );

			if( d->m_ui.m_type->currentText() == source.typeName() )
			{
				if( d->m_ui.m_name->findText( source.name() ) == -1 )
					d->m_ui.m_name->addItem( source.name() );
			}
		}
	}
}

void
LogSourcesSelector::typeChanged( const QString & text )
{
	clearNames();

	if( d->m_typesNames.contains( text ) )
		d->m_ui.m_name->addItems( d->m_typesNames[ text ] );
}

void
LogSourcesSelector::clearTypes()
{
	const int typesCount = d->m_ui.m_type->count();

	if( typesCount )
		for( int i = 0; i < typesCount; ++i )
			d->m_ui.m_type->removeItem( 0 );
}

void
LogSourcesSelector::clearNames()
{
	const int namesCount = d->m_ui.m_name->count();

	if( namesCount )
		for( int i = 0; i < namesCount; ++i )
			d->m_ui.m_name->removeItem( 0 );
}

} /* namespace Globe */

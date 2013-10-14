
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
#include <Globe/log_sources_selector.hpp>
#include <Globe/launch_time.hpp>
#include <Globe/channels.hpp>
#include <Globe/sources.hpp>

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

	connect( d->m_ui.m_fromLaunchButton, SIGNAL( clicked() ),
		this, SLOT( setStartTimeToLaunchTime() ) );
	connect( d->m_ui.m_toCurrentTimeButton, SIGNAL( clicked() ),
		this, SLOT( setEndTimeToCurrent() ) );
	connect( d->m_ui.m_channel, SIGNAL( currentTextChanged( const QString & ) ),
		this, SLOT( channelNameChanged( const QString & ) ) );
	connect( &ChannelsManager::instance(), SIGNAL( channelCreated( Channel * ) ),
		this, SLOT( chanelCreated( Channel * ) ) );
	connect( &ChannelsManager::instance(), SIGNAL( channelRemoved( Channel * ) ),
		this, SLOT( channelRemoved( Channel * ) ) );
	connect( &SourcesManager::instance(),
		SIGNAL( newSource( const Como::Source &, const QString & ) ),
		this, SLOT( newSource( const Como::Source &, const QString & ) ) );
	connect( d->m_ui.m_type, SIGNAL( currentTextChanged( const QString & ) ),
		this, SLOT( typeChanged( QString ) ) );
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
LogSourcesSelector::chanelCreated( Channel * ch )
{
	d->m_ui.m_channel->addItem( ch->name() );
}

void
LogSourcesSelector::channelRemoved( Channel * ch )
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

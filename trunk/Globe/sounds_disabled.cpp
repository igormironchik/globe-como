
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
#include <Globe/sounds_disabled.hpp>
#include <Globe/sounds_disabled_data.hpp>

// Qt include.
#include <QTimer>


namespace Globe {

//
// DisabledSoundsPrivate
//

class DisabledSoundsPrivate {
public:
	DisabledSoundsPrivate()
		:	m_timer( 0 )
	{
	}

	//! Timer.
	QTimer * m_timer;
	//! Map of disabled sounds.
	DisabledSoundsMap m_map;
}; // class DisabledSoundsPrivate


//
// DisabledSounds
//

DisabledSounds::DisabledSounds( QObject * parent )
	:	QObject( parent )
	,	d( new DisabledSoundsPrivate )
{
	init();
}

DisabledSounds::~DisabledSounds()
{
}

DisabledSounds &
DisabledSounds::instance()
{
	static DisabledSounds inst;

	return inst;
}

bool
DisabledSounds::isSoundsEnabled( const Como::Source & source,
	const QString & channelName )
{
	const int index = d->m_map[ channelName ].indexOf(
		DisabledSoundsData( source ) );

	if( index == -1 )
		return true;
	else
		return false;
}

void
DisabledSounds::disableSounds( const Como::Source & source,
	const QString & channelName,
	const QDateTime & to )
{
	const int index = d->m_map[ channelName ].indexOf(
		DisabledSoundsData( source ) );

	if( index == -1 )
	{
		d->m_map[ channelName ].append( DisabledSoundsData( source, to ) );

		emit soundsDisabled( source, channelName, to );
	}
	else
		d->m_map[ channelName ][ index ].dateTime() = to;
}

void
DisabledSounds::enableSounds( const Como::Source & source,
	const QString & channelName )
{
	const int index = d->m_map[ channelName ].indexOf(
		DisabledSoundsData( source ) );

	if( index != -1 )
	{
		d->m_map[ channelName ].removeAt( index );

		emit soundsEnabled( source, channelName );
	}
}

void
DisabledSounds::readCfg( const QString & fileName )
{

}

void
DisabledSounds::saveCfg( const QString & fileName )
{

}

void
DisabledSounds::checkAndEnableIf()
{
	const QDateTime now = QDateTime::currentDateTime();

	QMutableMapIterator< QString, QList< DisabledSoundsData > > it( d->m_map );

	while( it.hasNext() )
	{
		it.next();

		QList< DisabledSoundsData > toRemove;

		foreach( const DisabledSoundsData & data, it.value() )
		{
			if( data.dateTime() <= now )
				toRemove.append( data );
		}

		foreach( const DisabledSoundsData & data, toRemove )
		{
			it.value().removeOne( data );

			emit soundsEnabled( data.source(), it.key() );
		}
	}
}

void
DisabledSounds::initTimer()
{
	d->m_timer->start( 60 * 1000 );

	connect( d->m_timer, SIGNAL( timeout() ),
		this, SLOT( checkAndEnableIf() ) );

	checkAndEnableIf();
}

void
DisabledSounds::init()
{
	d->m_timer = new QTimer( this );

	QTimer::singleShot( ( 60 - QTime::currentTime().second() ) * 1000,
		this, SLOT( initTimer() ) );
}

} /* namespace Globe */

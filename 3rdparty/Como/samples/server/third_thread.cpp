
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Server include.
#include "third_thread.hpp"

// Como include.
#include <Como/Source>

// Qt include.
#include <QTimer>
#include <QScopedPointer>


//
// ThirdObject::ThirdObjectPrivate
//

struct ThirdObject::ThirdObjectPrivate {
	explicit ThirdObjectPrivate( Como::ServerSocket * socket )
		:	m_source( new Como::Source( Como::Source::String,
				QString( "ThirdObject" ),
				QString( "DynamicSource" ),
				QVariant( QString( "I'm alive" ) ),
				QString( "This is example of usage\n"
					"Como::Source::String as dynamic source." ),
				socket ) )
		,	m_socket( socket )
	{}

	~ThirdObjectPrivate()
	{
	}

	QScopedPointer< Como::Source > m_source;
	Como::ServerSocket * m_socket;
}; // struct ThirdObject::ThirdObjectPrivate


static const int c_delay = 1500;

//
// ThirdObject
//

ThirdObject::ThirdObject( Como::ServerSocket * socket,
	QObject * parent )
	:	QObject( parent )
	,	d( new ThirdObjectPrivate( socket ) )
{
	QTimer::singleShot( c_delay, this, SLOT( slotSwitchToStateTwo() ) );
}

ThirdObject::~ThirdObject()
{
}

void
ThirdObject::slotSwitchToStateOne()
{
	d->m_source.reset( new Como::Source( Como::Source::String,
		QString( "ThirdObject" ),
		QString( "DynamicSource" ),
		QVariant( QString( "I'm alive" ) ),
		QString( "This is example of usage\n"
			"Como::Source::String as dynamic source." ),
		d->m_socket ) );

	QTimer::singleShot( c_delay, this, SLOT( slotSwitchToStateTwo() ) );
}

void
ThirdObject::slotSwitchToStateTwo()
{
	d->m_source->setValue( QString( "I will die soon" ) );

	QTimer::singleShot( c_delay, this, SLOT( slotSwitchToStateThree() ) );
}

void
ThirdObject::slotSwitchToStateThree()
{
	d->m_source.reset();

	QTimer::singleShot( c_delay, this, SLOT( slotSwitchToStateOne() ) );
}


//
// ThirdThread::ThirdThreadPrivate
//

struct ThirdThread::ThirdThreadPrivate {
	explicit ThirdThreadPrivate( Como::ServerSocket * socket )
		:	m_socket( socket )
	{
	}

	Como::ServerSocket * m_socket;
}; // struct ThirdThread::ThirdThreadPrivate


//
// ThirdThread
//

ThirdThread::ThirdThread( Como::ServerSocket * socket,
	QObject * parent )
	:	QThread( parent )
	,	d( new ThirdThreadPrivate( socket ) )
{
}

ThirdThread::~ThirdThread()
{
}

void
ThirdThread::run()
{
	ThirdObject object( d->m_socket );

	exec();
}

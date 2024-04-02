
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Server include.
#include "first_thread.hpp"

// Como include.
#include <Como/Source>

// Qt include.
#include <QTimer>


//
// FirstObject::FirstObjectPrivate
//

struct FirstObject::FirstObjectPrivate {
	explicit FirstObjectPrivate( Como::ServerSocket * socket )
		:	m_source( Como::Source::String,
				QString( "FirstObject" ),
				QString( "StringSource" ),
				QVariant( QString( "I" ) ),
				QString( "This is example of usage\n"
					"Como::Source::String source." ),
				socket )
	{}

	Como::Source m_source;
}; // struct FirstObject::FirstObjectPrivate


static const int c_delay = 750;

//
// FirstObject
//

FirstObject::FirstObject( Como::ServerSocket * socket,
	QObject * parent )
	:	QObject( parent )
	,	d( new FirstObjectPrivate( socket ) )
{
	QTimer::singleShot( c_delay, this, SLOT( slotSwitchToStateTwo() ) );
}

FirstObject::~FirstObject()
{
}

void
FirstObject::slotSwitchToStateOne()
{
	d->m_source.setValue( QString( "I" ) );

	QTimer::singleShot( c_delay, this, SLOT( slotSwitchToStateTwo() ) );
}

void
FirstObject::slotSwitchToStateTwo()
{
	d->m_source.setValue( QString( "love" ) );

	QTimer::singleShot( c_delay, this, SLOT( slotSwitchToStateThree() ) );
}

void
FirstObject::slotSwitchToStateThree()
{
	d->m_source.setValue( QString( "Como" ) );

	QTimer::singleShot( c_delay, this, SLOT( slotSwitchToStateOne() ) );
}


//
// FirstThread::FirstThreadPrivate
//

struct FirstThread::FirstThreadPrivate {
	explicit FirstThreadPrivate( Como::ServerSocket * socket )
		:	m_socket( socket )
	{
	}

	Como::ServerSocket * m_socket;
}; // struct FirstThread::FirstThreadPrivate


//
// FirstThread
//

FirstThread::FirstThread( Como::ServerSocket * socket,
	QObject * parent )
	:	QThread( parent )
	,	d( new FirstThreadPrivate( socket ) )
{
}

FirstThread::~FirstThread()
{
}

void
FirstThread::run()
{
	FirstObject object( d->m_socket );

	exec();
}


/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Server include.
#include "second_thread.hpp"

// Como include.
#include <Como/Source>

// Qt include.
#include <QTimer>


//
// SecondObject::SecondObjectPrivate
//

struct SecondObject::SecondObjectPrivate {
	explicit SecondObjectPrivate( Como::ServerSocket * socket )
		:	m_source( Como::Source::Int,
				QString( "SecondObject" ),
				QString( "IntSource" ),
				QVariant( 0 ),
				QString( "This is example of usage\n"
					"Como::Source::Int source." ),
				socket )
	{}

	Como::Source m_source;
}; // struct SecondObject::SecondObjectPrivate


static const int c_delay = 750;

//
// FirstObject
//

SecondObject::SecondObject( Como::ServerSocket * socket,
	QObject * parent )
	:	QObject( parent )
	,	d( new SecondObjectPrivate( socket ) )
{
	QTimer::singleShot( c_delay, this, SLOT( slotSwitchToStateTwo() ) );
}

SecondObject::~SecondObject()
{
}

void
SecondObject::slotSwitchToStateOne()
{
	d->m_source.setValue( 0 );

	QTimer::singleShot( c_delay, this, SLOT( slotSwitchToStateTwo() ) );
}

void
SecondObject::slotSwitchToStateTwo()
{
	d->m_source.setValue( 50 );

	QTimer::singleShot( c_delay, this, SLOT( slotSwitchToStateThree() ) );
}

void
SecondObject::slotSwitchToStateThree()
{
	d->m_source.setValue( 100 );

	QTimer::singleShot( c_delay, this, SLOT( slotSwitchToStateOne() ) );
}


//
// SecondThread::SecondThreadPrivate
//

struct SecondThread::SecondThreadPrivate {
	explicit SecondThreadPrivate( Como::ServerSocket * socket )
		:	m_socket( socket )
	{
	}

	Como::ServerSocket * m_socket;
}; // struct SecondThread::SecondThreadPrivate


//
// SecondThread
//

SecondThread::SecondThread( Como::ServerSocket * socket,
	QObject * parent )
	:	QThread( parent )
	,	d( new SecondThreadPrivate( socket ) )
{
}

SecondThread::~SecondThread()
{
}

void
SecondThread::run()
{
	SecondObject object( d->m_socket );

	exec();
}

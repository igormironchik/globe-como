
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Server include.
#include "first_thread.hpp"
#include "second_thread.hpp"
#include "third_thread.hpp"

// Como include.
#include <Como/ServerSocket>
#include <Como/Source>

// Qt include.
#include <QCoreApplication>
#include <QMetaType>


int main( int argc, char ** argv )
{
	QCoreApplication app( argc, argv );

	qRegisterMetaType< Como::Source > ( "Como::Source" );

	Como::ServerSocket socket;

	FirstThread firstThread( &socket );
	SecondThread secondThread( &socket );
	ThirdThread thirdThread( &socket );

	firstThread.start();
	secondThread.start();
	thirdThread.start();

	socket.listen( QHostAddress::LocalHost, 4545 );

	return app.exec();
}

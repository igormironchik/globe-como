
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Como include.
#include <Como/ClientSocket>
#include <Como/Source>

// QTreeViewClient include.
#include "mainwindow.hpp"

// Qt include.
#include <QApplication>
#include <QMetaType>


int
main( int argc, char ** argv )
{
	qRegisterMetaType< Como::Source > ( "Como::Source" );

	QApplication app( argc, argv );

	Como::ClientSocket socket;

	MainWindow mainWindow( &socket );

	mainWindow.show();

	return app.exec();
}

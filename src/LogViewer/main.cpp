
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Qt include.
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QTimer>

// Args include.
#include <args-parser/all.hpp>

// LogViewer include.
#include <LogViewer/configuration.hpp>
#include <LogViewer/mainwindow.hpp>


int main( int argc, char ** argv )
{
	QString cfgFile = QLatin1String( "./etc/Globe.cfg" );;

	try{
		Args::CmdLine cmd;

		cmd.addArgWithFlagAndName( QChar( 'c' ), QLatin1String( "conf-file" ),
				true, false, QLatin1String(
					"Configuration file of the application." ) )
			.addHelp( true, argv[ 0 ], QLatin1String( "Globe event's log viewer." ) );

		cmd.parse( argc, argv );

		if( cmd.isDefined( QLatin1String( "-c" ) ) )
			cfgFile = cmd.value( QLatin1String( "-c" ) );
	}
	catch( const Args::HelpHasBeenPrintedException & )
	{
		return 0;
	}
	catch( const Args::BaseException & x )
	{
		qDebug() << x.what() << "\n";

		return 1;
	}

	QApplication app( argc, argv );

	QIcon appIcon( ":/img/viewer_128x128.png" );
	appIcon.addFile( ":/img/viewer_64x64.png" );
	appIcon.addFile( ":/img/viewer_48x48.png" );
	appIcon.addFile( ":/img/viewer_32x32.png" );
	appIcon.addFile( ":/img/viewer_22x22.png" );
	appIcon.addFile( ":/img/viewer_16x16.png" );
	app.setWindowIcon( appIcon );

	QTranslator globeTranslator;
	if( globeTranslator.load( "./tr/globe_" + QLocale::system().name() ) )
		app.installTranslator( &globeTranslator );

	QTranslator appTranslator;
	if( appTranslator.load( "./tr/logviewer_" + QLocale::system().name() ) )
		app.installTranslator( &appTranslator );

	LogViewer::Configuration::instance().setCfgFileName( cfgFile );

	QTimer::singleShot( 0, &LogViewer::MainWindow::instance(),
		&LogViewer::MainWindow::start );

	return app.exec();
}

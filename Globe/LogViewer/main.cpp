
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
#include <Args/all.hpp>

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
			.addHelp( argv[ 0 ], QLatin1String( "Globe event's log viewer." ) );

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
	globeTranslator.load( "./tr/globe_" + QLocale::system().name() );
	app.installTranslator( &globeTranslator );

	QTranslator appTranslator;
	appTranslator.load( "./tr/logviewer_" + QLocale::system().name() );
	app.installTranslator( &appTranslator );

	LogViewer::Configuration::instance().setCfgFileName( cfgFile );

	QTimer::singleShot( 0, &LogViewer::MainWindow::instance(),
		&LogViewer::MainWindow::start );

	return app.exec();
}

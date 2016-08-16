
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2014 - 2016 Igor Mironchik

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

// QtArg include.
#include <QtArg/CmdLine>
#include <QtArg/Arg>
#include <QtArg/Exceptions>
#include <QtArg/Help>

// LogViewer include.
#include <LogViewer/configuration.hpp>
#include <LogViewer/mainwindow.hpp>


int main( int argc, char ** argv )
{
	QString cfgFile = QLatin1String( "./etc/Globe.cfg" );;

	try{
		QtArgCmdLine cmdLine( argc, argv );

		QtArg cfgFileArg( QChar( 'c' ), QLatin1String( "conf-file" ),
			QLatin1String( "Configuration file of the application." ),
			false, true );

		QtArgHelp helpArg;
		helpArg.printer()->setProgramDescription( "Globe event's log viewer." );
		helpArg.printer()->setExecutableName( argv[0] );

		cmdLine.addParseable( cfgFileArg );
		cmdLine.addParseable( helpArg );

		cmdLine.parse();

		if( cfgFileArg.isDefined() )
			cfgFile = cfgFileArg.value();
	}
	catch( const QtArgHelpHasPrintedEx & )
	{
		return 0;
	}
	catch( const QtArgBaseException & x )
	{
		qDebug() << x.what();

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

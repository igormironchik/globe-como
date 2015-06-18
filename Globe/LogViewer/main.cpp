
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2014 Igor Mironchik

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

		QtArgHelp helpArg( &cmdLine );
		helpArg.printer()->setProgramDescription( "Globe event's log viewer." );
		helpArg.printer()->setExecutableName( argv[0] );

		cmdLine.addArg( &cfgFileArg );
		cmdLine.addArg( &helpArg );

		cmdLine.parse();

		if( cfgFileArg.isDefined() )
			cfgFile = cfgFileArg.value().toString();
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

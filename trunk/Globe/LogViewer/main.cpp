
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
#include <QSharedPointer>

// Globe icnlude.
#include <Globe/Core/configuration.hpp>
#include <Globe/Core/log_event_view_window.hpp>
#include <Globe/Core/log_sources_window.hpp>

// QtArg include.
#include <QtArg/CmdLine>
#include <QtArg/Arg>
#include <QtArg/Exceptions>
#include <QtArg/Help>


//
// viewerApplication
//

//! Singleton with QApplication.
static QSharedPointer< QApplication > viewerApplication( int argc = 0, char ** argv = 0 )
{
	static QSharedPointer< QApplication > app(
		new QApplication( argc, argv ) );

	return app;
} // viewerApplication


int main( int argc, char ** argv )
{
	QString cfgFile;

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

	QSharedPointer< QApplication > app = viewerApplication( argc, argv );

//	QIcon appIcon( ":/img/globe_256x256.png" );
//	appIcon.addFile( ":/img/globe_128x128.png" );
//	appIcon.addFile( ":/img/globe_64x64.png" );
//	appIcon.addFile( ":/img/globe_48x48.png" );
//	appIcon.addFile( ":/img/globe_32x32.png" );
//	appIcon.addFile( ":/img/globe_22x22.png" );
//	appIcon.addFile( ":/img/globe_16x16.png" );
//	appIcon.addFile( ":/img/globe_8x8.png" );
//	app->setWindowIcon( appIcon );

	QTranslator appTranslator;
	appTranslator.load( "./tr/globe_" + QLocale::system().name() );
	app->installTranslator( &appTranslator );

	Globe::Configuration::instance().setCfgFile( cfgFile );

	return app->exec();
}

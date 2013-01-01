
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2013 Igor Mironchik

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
#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QLocale>
#include <QtCore/QTextStream>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtCore/QList>

// Globe icnlude.
#include <Globe/mainwindow.hpp>
#include <Globe/channels.hpp>
#include <Globe/db.hpp>
#include <Globe/properties.hpp>
#include <Globe/tool_window_object.hpp>
#include <Globe/sources.hpp>
#include <Globe/sources_mainwindow.hpp>

// Como include.
#include <Como/Source>


static inline void printHelp( char * appName )
{
	QTextStream out( stdout );

	out << "Usage: " << appName << " [confFileName]";
}

static inline QString cfgFileName( char ** argv )
{
	return QString( argv[ 1 ] );
}


int main( int argc, char ** argv )
{
	qRegisterMetaType< Como::Source > ( "Como::Source" );

	QString cfgFile;

	if( argc == 2 )
		cfgFile = cfgFileName( argv );
	else if( argc > 2 )
	{
		printHelp( argv[ 0 ] );
		return 1;
	}

	QApplication app( argc, argv );

	QTranslator appTranslator;
	appTranslator.load( "./tr/" + QLocale::system().name() );
	app.installTranslator( &appTranslator );

	Globe::DB db;

	Globe::ChannelsManager channelsManager( &db );

	Globe::SourcesManager sourcesManager( &channelsManager );

	Globe::PropertiesManager propertiesManager( &sourcesManager, &channelsManager );

	Globe::SourcesMainWindow sourcesMainWindow( &sourcesManager, &channelsManager );

	QList< Globe::ToolWindowObject* > toolWindows;
	toolWindows.append( propertiesManager.toolWindowObject() );
	toolWindows.append( sourcesMainWindow.toolWindowObject() );

	Globe::MainWindow mainWindow( cfgFile, &channelsManager, &db,
		&propertiesManager, &sourcesMainWindow, toolWindows );

	QTimer::singleShot( 0, &mainWindow, SLOT( start() ) );

	return app.exec();
}

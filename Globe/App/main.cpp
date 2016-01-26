
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

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
#include <QTimer>
#include <QList>
#include <QDebug>
#include <QHostAddress>

// Globe icnlude.
#include <Globe/Core/mainwindow.hpp>
#include <Globe/Core/properties_manager.hpp>
#include <Globe/Core/tool_window_object.hpp>
#include <Globe/Core/sources_mainwindow.hpp>
#include <Globe/Core/launch_time.hpp>
#include <Globe/Core/configuration.hpp>
#include <Globe/Core/log_event_view_window.hpp>
#include <Globe/Core/log_sources_window.hpp>
#include <Globe/Core/utils.hpp>
#include <Globe/Core/sounds.hpp>

// Como include.
#include <Como/Source>

// QtArg include.
#include <QtArg/CmdLine>
#include <QtArg/Arg>
#include <QtArg/Exceptions>
#include <QtArg/Help>

int main( int argc, char ** argv )
{
	qRegisterMetaType< Como::Source > ( "Como::Source" );
	qRegisterMetaType< QHostAddress > ( "QHostAddress" );

	QString cfgFile;

	try{
		QtArgCmdLine cmdLine( argc, argv );

		QtArg cfgFileArg( QChar( 'c' ), QLatin1String( "conf-file" ),
			QLatin1String( "Configuration file of the application." ),
			false, true );

		QtArgHelp helpArg( &cmdLine );
		helpArg.printer()->setProgramDescription( "Tool for viewieng sources "
			"in the remote applications" );
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

	QIcon appIcon( ":/img/globe_256x256.png" );
	appIcon.addFile( ":/img/globe_128x128.png" );
	appIcon.addFile( ":/img/globe_64x64.png" );
	appIcon.addFile( ":/img/globe_48x48.png" );
	appIcon.addFile( ":/img/globe_32x32.png" );
	appIcon.addFile( ":/img/globe_22x22.png" );
	appIcon.addFile( ":/img/globe_16x16.png" );
	appIcon.addFile( ":/img/globe_8x8.png" );
	app.setWindowIcon( appIcon );

	QTranslator appTranslator;
	appTranslator.load( "./tr/globe_" + QLocale::system().name() );
	app.installTranslator( &appTranslator );

	Globe::checkDirAndCreateIfNotExists( QLatin1String( "./" ),
		QLatin1String( "etc" ) );

	Globe::LaunchTime::instance();

	Globe::Log::instance();

	QList< Globe::ToolWindowObject* > toolWindows;
	toolWindows.append( Globe::PropertiesManager::instance().toolWindowObject() );
	toolWindows.append( Globe::SourcesMainWindow::instance().toolWindowObject() );
	toolWindows.append( Globe::LogEventWindow::instance().toolWindowObject() );
	toolWindows.append( Globe::Sounds::instance().toolWindowObject() );
	toolWindows.append( Globe::LogSourcesWindow::instance().toolWindowObject() );

	Globe::Configuration::instance().setCfgFile( cfgFile );

	Globe::MainWindow::instance().init( toolWindows );

	QObject::connect( &app, &QApplication::commitDataRequest,
		&Globe::MainWindow::instance(),
		&Globe::MainWindow::sessionFinished );

	QTimer::singleShot( 0, &Globe::MainWindow::instance(),
		&Globe::MainWindow::start );

	return app.exec();
}

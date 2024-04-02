
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
#include <QTimer>
#include <QList>
#include <QDebug>
#include <QHostAddress>

// Globe icnlude.
#include <Core/mainwindow.hpp>
#include <Core/properties_manager.hpp>
#include <Core/tool_window_object.hpp>
#include <Core/sources_mainwindow.hpp>
#include <Core/launch_time.hpp>
#include <Core/configuration.hpp>
#include <Core/log_event_view_window.hpp>
#include <Core/log_sources_window.hpp>
#include <Core/utils.hpp>
#include <Core/sounds.hpp>

// Como include.
#include <Como/Source>

// Args include.
#include <args-parser/all.hpp>


int main( int argc, char ** argv )
{
	qRegisterMetaType< Como::Source > ( "Como::Source" );

	QString cfgFile;

	try{
		Args::CmdLine cmd;

		cmd.addArgWithFlagAndName( QChar( 'c' ), QLatin1String( "conf-file" ),
			true, false, QLatin1String( "Configuration file of the application." ) )
			.addHelp( true, argv[ 0 ], QLatin1String( "Tool for viewieng sources "
				"in the remote applications" ) );

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
		qDebug() << x.desc() << "\n";

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
	if( appTranslator.load( "./tr/globe_" + QLocale::system().name() ) )
		app.installTranslator( &appTranslator );

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

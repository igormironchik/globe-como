
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// LogViewer include
#include <LogViewer/configuration.hpp>

// Globe include.
#include <Core/application_cfg.hpp>
#include <Core/db_cfg.hpp>

// cfgfile include.
#include <cfgfile/all.hpp>

// Qt include.
#include <QCoreApplication>
#include <QFile>


namespace LogViewer {

static const QString defaultAppCfgFileName =
	QLatin1String( "./etc/Globe.cfg" );


//
// Configuration
//

Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}

static Configuration * configurationInstancePointer = 0;

void
Configuration::cleanup()
{
	delete configurationInstancePointer;

	configurationInstancePointer = 0;
}

Configuration &
Configuration::instance()
{
	if( !configurationInstancePointer )
	{
		configurationInstancePointer = new Configuration;

		qAddPostRoutine( &Configuration::cleanup );
	}

	return *configurationInstancePointer;
}

void
Configuration::setCfgFileName( const QString & file )
{
	m_cfgFileName = file;
}

void
Configuration::readConfiguration()
{
	if( m_cfgFileName.isEmpty() )
		m_cfgFileName = defaultAppCfgFileName;

	Globe::ApplicationCfg appCfg;

	{
		QFile file( m_cfgFileName );

		if( file.open( QIODevice::ReadOnly ) )
		{
			try {
				Globe::ApplicationCfgTag appCfgTag;

				QTextStream stream( &file );

				cfgfile::read_cfgfile( appCfgTag, stream, m_cfgFileName );

				file.close();

				appCfg = appCfgTag.cfg();
			}
			catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
			{
				file.close();

				emit error( tr( "Unable to load Globe's configuration file...\n\n%1" )
					.arg( x.desc() ) );

				return;
			}
		}
		else
		{
			emit error( tr( "Unable to load Globe's configuration file \"%1\"...\n\n"
				"Unable to open file." )
					.arg( m_cfgFileName ) );

			return;
		}
	}

	QFile file( appCfg.dbCfgFile() );

	if( file.open( QIODevice::ReadOnly ) )
	{
		try {
			Globe::DBTag tag;

			QTextStream stream( &file );

			cfgfile::read_cfgfile( tag, stream, appCfg.dbCfgFile() );

			file.close();

			m_dbFileName = tag.cfg().dbFileName();
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			emit error( tr( "Unable to read DB configuration...\n\n%1" )
				.arg( x.desc() ) );

			return;
		}
	}
	else
	{
		emit error( tr( "Unable to read DB configuration \"%1\"...\n\n"
			"Unable to open file." )
				.arg( appCfg.dbCfgFile() ) );

		return;
	}
}

const QString &
Configuration::dbFileName() const
{
	return m_dbFileName;
}

} /* namespace LogViewer */

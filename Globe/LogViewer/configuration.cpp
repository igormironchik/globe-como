
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

// LogViewer include
#include <LogViewer/configuration.hpp>

// Globe include.
#include <Globe/Core/application_cfg.hpp>
#include <Globe/Core/db_cfg.hpp>

// QtConfFile include.
#include <QtConfFile/Utils>
#include <QtConfFile/Exceptions>

// Qt include.
#include <QCoreApplication>


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

	try {
		Globe::ApplicationCfgTag appCfgTag;

		QtConfFile::readQtConfFile( appCfgTag,
			m_cfgFileName, QTextCodec::codecForName( "UTF-8" ) );

		appCfg = appCfgTag.cfg();
	}
	catch( const QtConfFile::Exception & x )
	{
		emit error( tr( "Unable to load Globe's configuration file...\n\n%1" )
			.arg( x.whatAsQString() ) );

		return;
	}

	try {
		Globe::DBTag tag;

		QtConfFile::readQtConfFile( tag, appCfg.dbCfgFile(),
			QTextCodec::codecForName( "UTF-8" ) );

		m_dbFileName = tag.cfg().dbFileName();
	}
	catch( const QtConfFile::Exception & x )
	{
		emit error( tr( "Unable to read DB configuration...\n\n%1" )
			.arg( x.whatAsQString() ) );

		return;
	}
}

const QString &
Configuration::dbFileName() const
{
	return m_dbFileName;
}

} /* namespace LogViewer */

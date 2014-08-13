
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

// LogViewer include
#include <LogViewer/configuration.hpp>

// Globe include.
#include <Globe/Core/application_cfg.hpp>
#include <Globe/Core/db_cfg.hpp>

// QtConfFile include.
#include <QtConfFile/Utils>
#include <QtConfFile/Exceptions>


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

Configuration &
Configuration::instance()
{
	static Configuration inst;

	return inst;
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

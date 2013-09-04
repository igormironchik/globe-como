
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

// Globe include
#include <Globe/application_cfg.hpp>


namespace Globe {

//
// ApplicationCfg
//

ApplicationCfg::ApplicationCfg()
{
}

ApplicationCfg::~ApplicationCfg()
{
}

ApplicationCfg::ApplicationCfg( const ApplicationCfg & other )
	:	m_mainWindowCfgFileName( other.mainWindowCfgFile() )
	,	m_channelsCfgFileName( other.channelsCfgFile() )
	,	m_propertiesCfgFileName( other.propertiesCfgFile() )
	,	m_sourcesMainWindowCfgFileName( other.sourcesMainWindowCfgFile() )
	,	m_windowsCfgFileName( other.windowsCfgFile() )
	,	m_colorsCfgFileName( other.colorsCfgFile() )
	,	m_dbCfgFileName( other.dbCfgFile() )
	,	m_logCfgFileName( other.logCfgFile() )
	,	m_logEventWindowCfgFileName( other.logEventWindowCfgFile() )
{
}

ApplicationCfg &
ApplicationCfg::operator = ( const ApplicationCfg & other )
{
	if( this != &other )
	{
		m_mainWindowCfgFileName = other.mainWindowCfgFile();
		m_channelsCfgFileName = other.channelsCfgFile();
		m_propertiesCfgFileName = other.propertiesCfgFile();
		m_sourcesMainWindowCfgFileName = other.sourcesMainWindowCfgFile();
		m_windowsCfgFileName = other.windowsCfgFile();
		m_colorsCfgFileName = other.colorsCfgFile();
		m_dbCfgFileName = other.dbCfgFile();
		m_logCfgFileName = other.logCfgFile();
		m_logEventWindowCfgFileName = other.logEventWindowCfgFile();
	}

	return *this;
}

const QString &
ApplicationCfg::mainWindowCfgFile() const
{
	return m_mainWindowCfgFileName;
}

void
ApplicationCfg::setMainWindowCfgFile( const QString & fileName )
{
	m_mainWindowCfgFileName = fileName;
}

const QString &
ApplicationCfg::channelsCfgFile() const
{
	return m_channelsCfgFileName;
}

void
ApplicationCfg::setChannelsCfgFile( const QString & fileName )
{
	m_channelsCfgFileName = fileName;
}

const QString &
ApplicationCfg::propertiesCfgFile() const
{
	return m_propertiesCfgFileName;
}

void
ApplicationCfg::setPropertiesCfgFile( const QString & fileName )
{
	m_propertiesCfgFileName = fileName;
}

const QString &
ApplicationCfg::sourcesMainWindowCfgFile() const
{
	return m_sourcesMainWindowCfgFileName;
}

void
ApplicationCfg::setSourcesMainWindowCfgFile( const QString & fileName )
{
	m_sourcesMainWindowCfgFileName = fileName;
}

const QString &
ApplicationCfg::windowsCfgFile() const
{
	return m_windowsCfgFileName;
}

void
ApplicationCfg::setWindowsCfgFile( const QString & fileName )
{
	m_windowsCfgFileName = fileName;
}

const QString &
ApplicationCfg::colorsCfgFile() const
{
	return m_colorsCfgFileName;
}

void
ApplicationCfg::setColorsCfgFile( const QString & fileName )
{
	m_colorsCfgFileName = fileName;
}

const QString &
ApplicationCfg::dbCfgFile() const
{
	return m_dbCfgFileName;
}

void
ApplicationCfg::setDbCfgFile( const QString & fileName )
{
	m_dbCfgFileName = fileName;
}

const QString &
ApplicationCfg::logCfgFile() const
{
	return m_logCfgFileName;
}

void
ApplicationCfg::setLogCfgFile( const QString & fileName )
{
	m_logCfgFileName = fileName;
}

const QString &
ApplicationCfg::logEventWindowCfgFile() const
{
	return m_logEventWindowCfgFileName;
}

void
ApplicationCfg::setLogEventWindowCfgFile( const QString & fileName )
{
	m_logEventWindowCfgFileName = fileName;
}


//
// ApplicationCfgTag
//

ApplicationCfgTag::ApplicationCfgTag()
	:	QtConfFile::TagNoValue( QLatin1String( "applicationCfg" ), true )
	,	m_mainWindowCfgFileName( *this, QLatin1String( "mainWindowCfgFileName" ),
			true )
	,	m_channelsCfgFileName( *this, QLatin1String( "channelsCfgFileName" ),
			true )
	,	m_propertiesCfgFileName( *this, QLatin1String( "propertiesCfgFileName" ),
			true )
	,	m_sourcesMainWindowCfgFileName( *this,
			QLatin1String( "sourcesMainWindowCfgFileName" ), true )
	,	m_windowsCfgFileName( *this,
			QLatin1String( "windowsCfgFileName" ), true )
	,	m_colorsCfgFileName( *this,
			QLatin1String( "colorsCfgFileName" ), true )
	,	m_dbCfgFileName( *this,
			QLatin1String( "dbCfgFileName" ), true )
	,	m_logCfgFileName( *this,
			QLatin1String( "logCfgFileName" ), true )
	,	m_logEventWindowCfgFileName( *this,
			QLatin1String( "logEventWindowCfgFileName" ), true )
{
}

ApplicationCfgTag::ApplicationCfgTag( const ApplicationCfg & cfg )
	:	QtConfFile::TagNoValue( QLatin1String( "applicationCfg" ), true )
	,	m_mainWindowCfgFileName( *this, QLatin1String( "mainWindowCfgFileName" ),
			true )
	,	m_channelsCfgFileName( *this, QLatin1String( "channelsCfgFileName" ),
			true )
	,	m_propertiesCfgFileName( *this, QLatin1String( "propertiesCfgFileName" ),
			true )
	,	m_sourcesMainWindowCfgFileName( *this,
			QLatin1String( "sourcesMainWindowCfgFileName" ), true )
	,	m_windowsCfgFileName( *this,
			QLatin1String( "windowsCfgFileName" ), true )
	,	m_colorsCfgFileName( *this,
			QLatin1String( "colorsCfgFileName" ), true )
	,	m_dbCfgFileName( *this,
			QLatin1String( "dbCfgFileName" ), true )
	,	m_logCfgFileName( *this,
			QLatin1String( "logCfgFileName" ), true )
	,	m_logEventWindowCfgFileName( *this,
			QLatin1String( "logEventWindowCfgFileName" ), true )
{
	m_mainWindowCfgFileName.setValue( cfg.mainWindowCfgFile() );
	m_channelsCfgFileName.setValue( cfg.channelsCfgFile() );
	m_propertiesCfgFileName.setValue( cfg.propertiesCfgFile() );
	m_sourcesMainWindowCfgFileName.setValue( cfg.sourcesMainWindowCfgFile() );
	m_windowsCfgFileName.setValue( cfg.windowsCfgFile() );
	m_colorsCfgFileName.setValue( cfg.colorsCfgFile() );
	m_dbCfgFileName.setValue( cfg.dbCfgFile() );
	m_logCfgFileName.setValue( cfg.logCfgFile() );
	m_logEventWindowCfgFileName.setValue( cfg.logEventWindowCfgFile() );

	setDefined();
}

ApplicationCfg
ApplicationCfgTag::cfg() const
{
	ApplicationCfg cfg;

	cfg.setMainWindowCfgFile( m_mainWindowCfgFileName.value() );
	cfg.setChannelsCfgFile( m_channelsCfgFileName.value() );
	cfg.setPropertiesCfgFile( m_propertiesCfgFileName.value() );
	cfg.setSourcesMainWindowCfgFile( m_sourcesMainWindowCfgFileName.value() );
	cfg.setWindowsCfgFile( m_windowsCfgFileName.value() );
	cfg.setColorsCfgFile( m_colorsCfgFileName.value() );
	cfg.setDbCfgFile( m_dbCfgFileName.value() );
	cfg.setLogCfgFile( m_logCfgFileName.value() );
	cfg.setLogEventWindowCfgFile( m_logEventWindowCfgFileName.value() );

	return cfg;
}

} /* namespace Globe */

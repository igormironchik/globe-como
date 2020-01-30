
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2020 Igor Mironchik

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

// Globe include
#include <Core/application_cfg.hpp>


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
	,	m_soundsCfgFileName( other.soundsCfgFile() )
	,	m_disabledSoundsCfgFileName( other.disabledSoundsCfgFile() )
	,	m_sourcesLogWindowCfgFileName( other.sourcesLogWindowCfgFile() )
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
		m_soundsCfgFileName = other.soundsCfgFile();
		m_disabledSoundsCfgFileName = other.disabledSoundsCfgFile();
		m_sourcesLogWindowCfgFileName = other.sourcesLogWindowCfgFile();
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

const QString &
ApplicationCfg::soundsCfgFile() const
{
	return m_soundsCfgFileName;
}

void
ApplicationCfg::setSoundsCfgFile( const QString & fileName )
{
	m_soundsCfgFileName = fileName;
}

const QString &
ApplicationCfg::disabledSoundsCfgFile() const
{
	return m_disabledSoundsCfgFileName;
}

void
ApplicationCfg::setDisabledSoundsCfgFile( const QString & fileName )
{
	m_disabledSoundsCfgFileName = fileName;
}

const QString &
ApplicationCfg::sourcesLogWindowCfgFile() const
{
	return m_sourcesLogWindowCfgFileName;
}

void
ApplicationCfg::setSourcesLogWindowCfgFile( const QString & fileName )
{
	m_sourcesLogWindowCfgFileName = fileName;
}


//
// ApplicationCfgTag
//

ApplicationCfgTag::ApplicationCfgTag()
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "applicationCfg" ), true )
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
	,	m_soundsCfgFileName( *this,
			QLatin1String( "soundsCfgFileName" ), true )
	,	m_disabledSoundsCfgFileName( *this,
			QLatin1String( "disabledSoundsCfgFileName" ), true )
	,	m_sourcesLogWindowCfgFileName( *this,
			QLatin1String( "sourcesLogWindowCfgFileName" ), true )
{
}

ApplicationCfgTag::ApplicationCfgTag( const ApplicationCfg & cfg )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "applicationCfg" ), true )
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
	,	m_soundsCfgFileName( *this,
			QLatin1String( "soundsCfgFileName" ), true )
	,	m_disabledSoundsCfgFileName( *this,
			QLatin1String( "disabledSoundsCfgFileName" ), true )
	,	m_sourcesLogWindowCfgFileName( *this,
			QLatin1String( "sourcesLogWindowCfgFileName" ), true )
{
	m_mainWindowCfgFileName.set_value( cfg.mainWindowCfgFile() );
	m_channelsCfgFileName.set_value( cfg.channelsCfgFile() );
	m_propertiesCfgFileName.set_value( cfg.propertiesCfgFile() );
	m_sourcesMainWindowCfgFileName.set_value( cfg.sourcesMainWindowCfgFile() );
	m_windowsCfgFileName.set_value( cfg.windowsCfgFile() );
	m_colorsCfgFileName.set_value( cfg.colorsCfgFile() );
	m_dbCfgFileName.set_value( cfg.dbCfgFile() );
	m_logCfgFileName.set_value( cfg.logCfgFile() );
	m_logEventWindowCfgFileName.set_value( cfg.logEventWindowCfgFile() );
	m_soundsCfgFileName.set_value( cfg.soundsCfgFile() );
	m_disabledSoundsCfgFileName.set_value( cfg.disabledSoundsCfgFile() );
	m_sourcesLogWindowCfgFileName.set_value( cfg.sourcesLogWindowCfgFile() );

	set_defined();
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
	cfg.setSoundsCfgFile( m_soundsCfgFileName.value() );
	cfg.setDisabledSoundsCfgFile( m_disabledSoundsCfgFileName.value() );
	cfg.setSourcesLogWindowCfgFile( m_sourcesLogWindowCfgFileName.value() );

	return cfg;
}

} /* namespace Globe */

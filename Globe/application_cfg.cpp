
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 Igor Mironchik

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

// C++ include.
#include <limits>


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
{
	m_mainWindowCfgFileName.setValue( cfg.mainWindowCfgFile() );
	m_channelsCfgFileName.setValue( cfg.channelsCfgFile() );
	m_propertiesCfgFileName.setValue( cfg.propertiesCfgFile() );

	setDefined();
}

ApplicationCfg
ApplicationCfgTag::cfg() const
{
	ApplicationCfg cfg;

	cfg.setMainWindowCfgFile( m_mainWindowCfgFileName.value() );
	cfg.setChannelsCfgFile( m_channelsCfgFileName.value() );
	cfg.setPropertiesCfgFile( m_propertiesCfgFileName.value() );

	return cfg;
}

} /* namespace Globe */

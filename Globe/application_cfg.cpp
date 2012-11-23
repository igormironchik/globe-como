
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
	,	m_availableScreenGeometry( other.availableScreenGeometry() )
{
}

ApplicationCfg &
ApplicationCfg::operator = ( const ApplicationCfg & other )
{
	if( this != &other )
	{
		m_mainWindowCfgFileName = other.mainWindowCfgFile();
		m_channelsCfgFileName = other.channelsCfgFile();
		m_availableScreenGeometry = other.availableScreenGeometry();
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

const QRect &
ApplicationCfg::availableScreenGeometry() const
{
	return m_availableScreenGeometry;
}

void
ApplicationCfg::setAvailableScreenGeometry( const QRect & rect )
{
	m_availableScreenGeometry = rect;
}


//
// AvailableScreenGeometryTag
//

AvailableScreenGeometryTag::AvailableScreenGeometryTag( QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_x( *this, QLatin1String( "x" ), true )
	,	m_y( *this, QLatin1String( "y" ), true )
	,	m_width( *this, QLatin1String( "width" ), true )
	,	m_height( *this, QLatin1String( "height" ), true )
	,	m_constraint( 0, std::numeric_limits< int >::max() )
{
	m_width.setConstraint( &m_constraint );
	m_height.setConstraint( &m_constraint );
}

AvailableScreenGeometryTag::AvailableScreenGeometryTag( const QRect & rect,
	QtConfFile::Tag & owner, const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_x( *this, QLatin1String( "x" ), true )
	,	m_y( *this, QLatin1String( "y" ), true )
	,	m_width( *this, QLatin1String( "width" ), true )
	,	m_height( *this, QLatin1String( "height" ), true )
	,	m_constraint( 0, std::numeric_limits< int >::max() )
{
	m_width.setConstraint( &m_constraint );
	m_height.setConstraint( &m_constraint );

	m_x.setValue( rect.x() );
	m_y.setValue( rect.y() );
	m_width.setValue( rect.width() );
	m_height.setValue( rect.height() );

	setDefined();
}

QRect
AvailableScreenGeometryTag::geometry() const
{
	return QRect( m_x.value(), m_y.value(),
		m_width.value(), m_height.value() );
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
	,	m_availableScreenGeometry( *this, QLatin1String( "availableScreenGeometry" ),
			true )
{
}

ApplicationCfgTag::ApplicationCfgTag( const ApplicationCfg & cfg )
	:	QtConfFile::TagNoValue( QLatin1String( "applicationCfg" ), true )
	,	m_mainWindowCfgFileName( *this, QLatin1String( "mainWindowCfgFileName" ),
			true )
	,	m_channelsCfgFileName( *this, QLatin1String( "channelsCfgFileName" ),
			true )
	,	m_availableScreenGeometry( cfg.availableScreenGeometry(), *this,
			QLatin1String( "availableScreenGeometry" ), true )
{
	m_mainWindowCfgFileName.setValue( cfg.mainWindowCfgFile() );
	m_channelsCfgFileName.setValue( cfg.channelsCfgFile() );

	setDefined();
}

ApplicationCfg
ApplicationCfgTag::cfg() const
{
	ApplicationCfg cfg;

	cfg.setMainWindowCfgFile( m_mainWindowCfgFileName.value() );
	cfg.setChannelsCfgFile( m_channelsCfgFileName.value() );
	cfg.setAvailableScreenGeometry( m_availableScreenGeometry.geometry() );

	return cfg;
}

} /* namespace Globe */

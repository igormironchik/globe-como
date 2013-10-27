
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

// Globe include.
#include <Globe/Core/color_for_level.hpp>
#include <Globe/Core/color_for_level_cfg.hpp>
#include <Globe/Core/log.hpp>

// QtConfFile include.
#include <QtConfFile/Utils>

// Qt include.
#include <QMessageBox>


namespace Globe {

//
// ColorForLevelPrivate
//

class ColorForLevelPrivate {
public:
	ColorForLevelPrivate()
		:	m_noneColor( defaultNoneColor )
		,	m_criticalColor( defaultCriticalColor )
		,	m_errorColor( defaultErrorColor )
		,	m_warningColor( defaultWarningColor )
		,	m_debugColor( defaultDebugColor )
		,	m_infoColor( defaultInfoColor )
		,	m_deregisteredColor( defaultDeregisteredColor )
		,	m_disconnectedColor( defaultDisconnectedColor )
	{
	}

	//! Color for "none" level.
	QColor m_noneColor;
	//! Color for "critical" level.
	QColor m_criticalColor;
	//! Color for "error" level.
	QColor m_errorColor;
	//! Color for "warning" level.
	QColor m_warningColor;
	//! Color for "debug" level.
	QColor m_debugColor;
	//! Color for "info" level.
	QColor m_infoColor;
	//! Color for deregistered sources.
	QColor m_deregisteredColor;
	//! Color for disconected sources.
	QColor m_disconnectedColor;
}; // class ColorForLevelPrivate


//
// ColorForLevel
//

ColorForLevel::ColorForLevel( QObject * parent )
	:	QObject( parent )
	,	d( new ColorForLevelPrivate )
{
}

ColorForLevel::~ColorForLevel()
{
}

ColorForLevel &
ColorForLevel::instance()
{
	static ColorForLevel inst;

	return inst;
}

const QColor &
ColorForLevel::color( Level level ) const
{
	switch( level )
	{
		case None : return d->m_noneColor;
		case Critical : return d->m_criticalColor;
		case Error : return d->m_errorColor;
		case Warning : return d->m_warningColor;
		case Debug : return d->m_debugColor;
		case Info : return d->m_infoColor;
		default : return d->m_infoColor;
	}
}

const QColor &
ColorForLevel::deregisteredColor() const
{
	return d->m_deregisteredColor;
}

const QColor &
ColorForLevel::disconnectedColor() const
{
	return d->m_disconnectedColor;
}

void
ColorForLevel::setColors( const QColor & none,
	const QColor & critical,
	const QColor & error,
	const QColor & warning,
	const QColor & debug,
	const QColor & info,
	const QColor & deregistered,
	const QColor & disconnected )
{
	d->m_noneColor = none;
	d->m_criticalColor = critical;
	d->m_errorColor = error;
	d->m_warningColor = warning;
	d->m_debugColor = debug;
	d->m_infoColor = info;
	d->m_deregisteredColor = deregistered;
	d->m_disconnectedColor = disconnected;

	emit changed();
}

void
ColorForLevel::saveCfg( const QString & fileName )
{
	try {
		ColorForLevelTag tag( this );

		QtConfFile::writeQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo,
			QString( "Colors configuration saved into file \"%1\"." )
				.arg( fileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError,
			QString( "Unable to save colors configuration to file \"%1\".\n"
				"%2" )
					.arg( fileName )
					.arg( x.whatAsQString() ) );

		QMessageBox::critical( 0,
			tr( "Unable to save colors correspondence configuration..." ),
			tr( "Unable to save colors correspondence configuration...\n\n%1" )
				.arg( x.whatAsQString() ) );
	}
}

void
ColorForLevel::readCfg( const QString & fileName )
{
	ColorForLevelTag tag;

	try {
		QtConfFile::readQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo,
			QString( "Colors configuration loaded from file \"%1\"." )
				.arg( fileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError,
			QString( "Unable to read colors configuration from file "
				"\"%1\".\n"
				"%2" )
					.arg( fileName )
					.arg( x.whatAsQString() ) );

		QMessageBox::critical( 0,
			tr( "Unable to read colors correspondence configuration..." ),
			tr( "Unable to read colors correspondence configuration...\n\n%1" )
				.arg( x.whatAsQString() ) );

		return;
	}

	tag.initColorForLevel( this );
}

} /* namespace Globe */

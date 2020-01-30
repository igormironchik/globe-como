
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

// Globe include.
#include <Core/color_for_level.hpp>
#include <Core/color_for_level_cfg.hpp>
#include <Core/log.hpp>

// cfgfile include.
#include <cfgfile/all.hpp>

// Qt include.
#include <QMessageBox>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>


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

static ColorForLevel * colorForLevelInstancePointer = 0;

void
ColorForLevel::cleanup()
{
	delete colorForLevelInstancePointer;

	colorForLevelInstancePointer = 0;
}

ColorForLevel &
ColorForLevel::instance()
{
	if( !colorForLevelInstancePointer )
	{
		colorForLevelInstancePointer = new ColorForLevel;

		qAddPostRoutine( &ColorForLevel::cleanup );
	}

	return *colorForLevelInstancePointer;
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
	QFile file( fileName );

	if( file.open( QIODevice::WriteOnly ) )
	{
		try {
			QTextStream stream( &file );
			stream.setCodec( QTextCodec::codecForName( "UTF-8" ) );

			ColorForLevelTag tag( this );

			cfgfile::write_cfgfile( tag, stream );

			file.close();

			Log::instance().writeMsgToEventLog( LogLevelInfo,
				QString( "Colors configuration saved into file \"%1\"." )
					.arg( fileName ) );
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			Log::instance().writeMsgToEventLog( LogLevelError,
				QString( "Unable to save colors configuration to file \"%1\".\n"
					"%2" )
						.arg( fileName )
						.arg( x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to save colors correspondence configuration..." ),
				tr( "Unable to save colors correspondence configuration...\n\n%1" )
					.arg( x.desc() ) );
		}
	}
	else
	{
		Log::instance().writeMsgToEventLog( LogLevelError,
			QString( "Unable to save colors configuration to file \"%1\"" )
					.arg( fileName ) );

		QMessageBox::critical( 0,
			tr( "Unable to save colors correspondence configuration..." ),
			tr( "Unable to save colors correspondence configuration...\n\n"
				"Unable to open file \"%1\"" )
					.arg( fileName ) );
	}
}

void
ColorForLevel::readCfg( const QString & fileName )
{
	ColorForLevelTag tag;

	QFile file( fileName );

	if( file.open( QIODevice::ReadOnly ) )
	{
		try {
			QTextStream stream( &file );
			stream.setCodec( QTextCodec::codecForName( "UTF-8" ) );

			cfgfile::read_cfgfile( tag, stream, fileName );

			file.close();

			Log::instance().writeMsgToEventLog( LogLevelInfo,
				QString( "Colors configuration loaded from file \"%1\"." )
					.arg( fileName ) );
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			Log::instance().writeMsgToEventLog( LogLevelError,
				QString( "Unable to read colors configuration from file "
					"\"%1\".\n"
					"%2" )
						.arg( fileName )
						.arg( x.desc() ) );

			QMessageBox::critical( 0,
				tr( "Unable to read colors correspondence configuration..." ),
				tr( "Unable to read colors correspondence configuration...\n\n%1" )
					.arg( x.desc() ) );

			return;
		}

		tag.initColorForLevel( this );
	}
	else
	{
		Log::instance().writeMsgToEventLog( LogLevelError,
			QString( "Unable to read colors configuration from file "
				"\"%1\"" )
					.arg( fileName ) );

		QMessageBox::critical( 0,
			tr( "Unable to read colors correspondence configuration..." ),
			tr( "Unable to read colors correspondence configuration...\n\n"
				"Unable to open file \"%1\"" )
				.arg( fileName ) );
	}
}

} /* namespace Globe */

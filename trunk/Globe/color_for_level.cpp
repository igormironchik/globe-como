
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
#include <Globe/color_for_level.hpp>
#include <Globe/mainwindow.hpp>
#include <Globe/color_for_level_cfg.hpp>

// QtConfFile include.
#include <QtConfFile/Utils>

// Qt include.
#include <QMessageBox>


namespace Globe {

static const QColor defaultNoneColor = Qt::white;
static const QColor defaultCriticalColor = Qt::red;
static const QColor defaultErrorColor = Qt::magenta;
static const QColor defaultWarningColor = Qt::yellow;
static const QColor defaultDebugColor = Qt::cyan;
static const QColor defaultInfoColor = Qt::green;
static const QColor defaultDeregisteredColor = Qt::lightGray;
static const QColor defaultDisconnectedColor = Qt::lightGray;

//
// ColorForLevelPrivate
//

class ColorForLevelPrivate {
public:
	explicit ColorForLevelPrivate( MainWindow * mainWindow )
		:	m_mainWindow( mainWindow )
		,	m_noneColor( defaultNoneColor )
		,	m_criticalColor( defaultCriticalColor )
		,	m_errorColor( defaultErrorColor )
		,	m_warningColor( defaultWarningColor )
		,	m_debugColor( defaultDebugColor )
		,	m_infoColor( defaultInfoColor )
		,	m_deregisteredColor( defaultDeregisteredColor )
		,	m_disconnectedColor( defaultDisconnectedColor )
	{
	}

	//! Main window.
	MainWindow * m_mainWindow;
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

ColorForLevel::ColorForLevel( MainWindow * mainWindow )
	:	QObject( mainWindow )
	,	d( new ColorForLevelPrivate( mainWindow ) )
{
}

ColorForLevel::~ColorForLevel()
{
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
	}
	catch( const QtConfFile::Exception & x )
	{
		QMessageBox::critical( d->m_mainWindow,
			tr( "Unable to save colors correspondence configuration..." ),
			x.whatAsQString() );
	}
}

void
ColorForLevel::readCfg( const QString & fileName )
{
	ColorForLevelTag tag;

	try {
		QtConfFile::readQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		QMessageBox::critical( d->m_mainWindow,
			tr( "Unable to read colors correspondence configuration..." ),
			x.whatAsQString() );

		return;
	}

	tag.initColorForLevel( this );
}

} /* namespace Globe */

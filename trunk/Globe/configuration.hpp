
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

#ifndef GLOBE__CONFIGURATION_HPP__INCLUDED
#define GLOBE__CONFIGURATION_HPP__INCLUDED

// Qt include.
#include <QObject>
#include <QScopedPointer>


namespace Globe {

//
// Configuration
//

class ConfigurationPrivate;

//! Configuration loader/saver.
class Configuration
	:	public QObject
{
	Q_OBJECT

private:
	Configuration( QObject * parent = 0 );

	~Configuration();

public:
	//! \return Instance.
	static Configuration & instance();

	//! Load configuration.
	void loadConfiguration();

	//! Save configuration.
	void saveConfiguration();

	//! Set configuration file name.
	void setCfgFile( const QString & fileName );

private:
	//! Read application's configuration.
	void readAppCfg( const QString & cfgFileName );
	//! Read main window's configuration and init main window.
	void readMainWindowCfg( const QString & cfgFileName );
	//! Read channels configuration.
	void readChannelsCfg( const QString & cfgFileName );
	//! Read properties configuration.
	void readPropertiesCfg( const QString & cfgFileName );
	//! Read sources main window configuration.
	void readSourcesMainWindowCfg( const QString & cfgFileName );
	//! Read windows configuration.
	void readWindowsCfg( const QString & cfgFileName );
	//! Read colors cfg.
	void readColorsCfg( const QString & cfgFileName );
	//! Read DB cfg.
	void readDbCfg( const QString & cfgFileName );
	//! Read log cfg.
	void readLogCfg( const QString & cfgFileName );
	//! Read event log window configuration.
	void readLogEventWindowCfg( const QString & cfgFileName );
	//! Read sounds configuration.
	void readSoundsCfg( const QString & cfgFileName );
	//! Read disabled sounds configuration.
	void readDisabledSoundsCfg( const QString & cfgFileName );
	//! Read sources log window configuration.
	void readSourcesLogWindowCfg( const QString & cfgFileName );

	//! Save application's configuration.
	void saveAppCfg( const QString & cfgFileName );
	//! Save main window's configuration.
	void saveMainWindowCfg( const QString & cfgFileName );
	//! Save channels configuration.
	void saveChannelsCfg( const QString & cfgFileName );
	//! Save properties configuration.
	void savePropertiesCfg( const QString & cfgFileName );
	//! Save sources main window configuration.
	void saveSourcesMainWindowCfg( const QString & cfgFileName );
	//! Save windows configuration.
	void saveWindowsCfg( const QString & cfgFileName );
	//! Save colors cfg.
	void saveColorsCfg( const QString & cfgFileName );
	//! Save DB cfg.
	void saveDbCfg( const QString & cfgFileName );
	//! Save log cfg.
	void saveLogCfg( const QString & cfgFileName );
	//! Save event log window configuration.
	void saveLogEventWindowCfg( const QString & cfgFileName );
	//! Save sounds configuration.
	void saveSoundsCfg( const QString & cfgFileName );
	//! Save disabled sounds configuration.
	void saveDisabledSoundsCfg( const QString & cfgFileName );
	//! Save sources log window configuration.
	void saveSourcesLogWindowCfg( const QString & cfgFileName );

private:
	Q_DISABLE_COPY( Configuration )

	QScopedPointer< ConfigurationPrivate > d;
}; // class Configuration

} /* namespace Globe */

#endif // GLOBE__CONFIGURATION_HPP__INCLUDED

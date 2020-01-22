
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

#ifndef GLOBE__CONFIGURATION_HPP__INCLUDED
#define GLOBE__CONFIGURATION_HPP__INCLUDED

// Qt include.
#include <QObject>
#include <QScopedPointer>

// Globe include.
#include <Globe/Core/export.hpp>


namespace Globe {

//
// Configuration
//

class ConfigurationPrivate;

//! Configuration loader/saver.
class CORE_EXPORT Configuration
	:	public QObject
{
	Q_OBJECT

private:
	Configuration( QObject * parent = 0 );

	~Configuration();

	static void cleanup();

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

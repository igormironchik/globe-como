
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__APPLICATION_CFG_HPP__INCLUDED
#define GLOBE__APPLICATION_CFG_HPP__INCLUDED

// Qt include.
#include <QString>

// cfgfile include.
#include <cfgfile/all.hpp>

// Globe include.
#include <Core/export.hpp>


namespace Globe {

//
// ApplicationCfg
//

//! Configuration of the application.
class CORE_EXPORT ApplicationCfg {
public:
	ApplicationCfg();

	~ApplicationCfg();

	ApplicationCfg( const ApplicationCfg & other );

	ApplicationCfg & operator = ( const ApplicationCfg & other );

	//! \return File name of the main window configuration.
	const QString & mainWindowCfgFile() const;
	//! Set file name of the main window configuration.
	void setMainWindowCfgFile( const QString & fileName );

	//! \return File name of the channels configuration.
	const QString & channelsCfgFile() const;
	//! Set file name of the channels configuration.
	void setChannelsCfgFile( const QString & fileName );

	//! \return File name of the properties configuration.
	const QString & propertiesCfgFile() const;
	//! Set file name of the properties configuration.
	void setPropertiesCfgFile( const QString & fileName );

	//! \return File name of the sources main window configuration.
	const QString & sourcesMainWindowCfgFile() const;
	//! Set file name of the sources main window configuration.
	void setSourcesMainWindowCfgFile( const QString & fileName );

	//! \return File name of the windows configuration.
	const QString & windowsCfgFile() const;
	//! Set file name of the windows configuration.
	void setWindowsCfgFile( const QString & fileName );

	//! \return File name of the colors correspondence configuration.
	const QString & colorsCfgFile() const;
	//! Set file name of the colors correspondence configuration.
	void setColorsCfgFile( const QString & fileName );

	//! \return File name of the DB configuration.
	const QString & dbCfgFile() const;
	//! Set file name of the DB configuration.
	void setDbCfgFile( const QString & fileName );

	//! \return File name of the log configuration.
	const QString & logCfgFile() const;
	//! Set file name of the log configuration.
	void setLogCfgFile( const QString & fileName );

	//! \return File name of the event's log window configuration.
	const QString & logEventWindowCfgFile() const;
	//! Set file name of the event's log window configuration.
	void setLogEventWindowCfgFile( const QString & fileName );

	//! \return File name of the sounds configuration.
	const QString & soundsCfgFile() const;
	//! Set file name of the sounds configuration.
	void setSoundsCfgFile( const QString & fileName );

	//! \return File name of the disabled sounds configuration.
	const QString & disabledSoundsCfgFile() const;
	//! Set file name of the disabled sounds configuration.
	void setDisabledSoundsCfgFile( const QString & fileName );

	//! \return File name of the sources log window configuration.
	const QString & sourcesLogWindowCfgFile() const;
	//! Set file name of the sources log window configuration.
	void setSourcesLogWindowCfgFile( const QString & fileName );

private:
	//! File name of the main window configuration.
	QString m_mainWindowCfgFileName;
	//! File name of the channels configuration.
	QString m_channelsCfgFileName;
	//! File name of the properties configuration.
	QString m_propertiesCfgFileName;
	//! File name of the sources main window configuration.
	QString m_sourcesMainWindowCfgFileName;
	//! File name of the windows configuration.
	QString m_windowsCfgFileName;
	//! File name of the colors correspondence configuration.
	QString m_colorsCfgFileName;
	//! File name of the DB configuration.
	QString m_dbCfgFileName;
	//! File name of the log configuration.
	QString m_logCfgFileName;
	//! File name of the event's log window configuration.
	QString m_logEventWindowCfgFileName;
	//! File name of the sounds configuration.
	QString m_soundsCfgFileName;
	//! File name of the disabled sounds configuration.
	QString m_disabledSoundsCfgFileName;
	//! File name of the sources log window configuration.
	QString m_sourcesLogWindowCfgFileName;
}; // class ApplicationCfg


//
// ApplicationCfgTag
//

//! Tag with the application's configuration.
class CORE_EXPORT ApplicationCfgTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	ApplicationCfgTag();

	explicit ApplicationCfgTag( const ApplicationCfg & cfg );

	//! \return Application's configuration.
	ApplicationCfg cfg() const;

private:
	//! File name of the main window configuration.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_mainWindowCfgFileName;
	//! File name of the channels configuration.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_channelsCfgFileName;
	//! File name of the properties configuration.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_propertiesCfgFileName;
	//! File name of the sources main window configuration.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_sourcesMainWindowCfgFileName;
	//! File name of the windows configuration.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_windowsCfgFileName;
	//! File name of the colors correspondence configuration.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_colorsCfgFileName;
	//! File name of the DB configuration.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_dbCfgFileName;
	//! File name of the log configuration.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_logCfgFileName;
	//! File name of the event's log window configuration.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_logEventWindowCfgFileName;
	//! File name of the sounds configuration.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_soundsCfgFileName;
	//!File name of the disabled sounds configuration.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_disabledSoundsCfgFileName;
	//! File name of the sources log window configuration.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_sourcesLogWindowCfgFileName;
}; // class ApplicationCfgTag

} /* namespace Globe */

#endif // GLOBE__APPLICATION_CFG_HPP__INCLUDED

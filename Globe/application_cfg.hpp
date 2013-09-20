
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

#ifndef GLOBE__APPLICATION_CFG_HPP__INCLUDED
#define GLOBE__APPLICATION_CFG_HPP__INCLUDED

// Qt include.
#include <QString>

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>
#include <QtConfFile/ConstraintMinMax>


namespace Globe {

//
// ApplicationCfg
//

//! Configuration of the application.
class ApplicationCfg {
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
}; // class ApplicationCfg


//
// ApplicationCfgTag
//

//! Tag with the application's configuration.
class ApplicationCfgTag
	:	public QtConfFile::TagNoValue
{
public:
	ApplicationCfgTag();

	explicit ApplicationCfgTag( const ApplicationCfg & cfg );

	//! \return Application's configuration.
	ApplicationCfg cfg() const;

private:
	//! File name of the main window configuration.
	QtConfFile::TagScalar< QString > m_mainWindowCfgFileName;
	//! File name of the channels configuration.
	QtConfFile::TagScalar< QString > m_channelsCfgFileName;
	//! File name of the properties configuration.
	QtConfFile::TagScalar< QString > m_propertiesCfgFileName;
	//! File name of the sources main window configuration.
	QtConfFile::TagScalar< QString > m_sourcesMainWindowCfgFileName;
	//! File name of the windows configuration.
	QtConfFile::TagScalar< QString > m_windowsCfgFileName;
	//! File name of the colors correspondence configuration.
	QtConfFile::TagScalar< QString > m_colorsCfgFileName;
	//! File name of the DB configuration.
	QtConfFile::TagScalar< QString > m_dbCfgFileName;
	//! File name of the log configuration.
	QtConfFile::TagScalar< QString > m_logCfgFileName;
	//! File name of the event's log window configuration.
	QtConfFile::TagScalar< QString > m_logEventWindowCfgFileName;
	//! File name of the sounds configuration.
	QtConfFile::TagScalar< QString > m_soundsCfgFileName;
	//!File name of the disabled sounds configuration.
	QtConfFile::TagScalar< QString > m_disabledSoundsCfgFileName;
}; // class ApplicationCfgTag

} /* namespace Globe */

#endif // GLOBE__APPLICATION_CFG_HPP__INCLUDED

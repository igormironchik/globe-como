
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2014 - 2016 Igor Mironchik

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

#ifndef LOGVIEWER__CONFIGURATION_HPP__INCLUDED
#define LOGVIEWER__CONFIGURATION_HPP__INCLUDED

// Qt include.
#include <QString>
#include <QObject>


namespace LogViewer {

//
// Configuration
//

//! Configuration.
class Configuration
	:	public QObject
{
	Q_OBJECT

signals:
	//! Emits when error occured.
	void error( const QString & );

private:
	Configuration();

	~Configuration();

	static void cleanup();

public:
	//! \return Instance.
	static Configuration & instance();

	//! Set cfg file name.
	void setCfgFileName( const QString & file );

	//! Read configuration.
	void readConfiguration();

	//! \return File name of the DB.
	const QString & dbFileName() const;

private:
	//! File name of the DB.
	QString m_dbFileName;
	//! Cfg file name.
	QString m_cfgFileName;
}; // class Configuration

} /* namespace LogViewer */

#endif // LOGVIEWER__CONFIGURATION_HPP__INCLUDED

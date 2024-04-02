
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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

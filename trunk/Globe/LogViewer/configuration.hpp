
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2014 Igor Mironchik

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


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

#ifndef GLOBE__LOG_SOURCES_SELECTOR_HPP__INCLUDED
#define GLOBE__LOG_SOURCES_SELECTOR_HPP__INCLUDED

// Qt include.
#include <QWidget>
#include <QScopedPointer>
#include <QDateTime>

// Como include.
#include <Como/Source>


namespace Globe {

class SelectQueryNavigation;
class Channel;


//
// LogSourcesSelector
//

class LogSourcesSelectorPrivate;

//! Selector for the event log.
class LogSourcesSelector
	:	public QWidget
{
	Q_OBJECT

public:
	LogSourcesSelector( QWidget * parent = 0, Qt::WindowFlags f = 0 );

	~LogSourcesSelector();

	//! \return Navigation widget.
	SelectQueryNavigation * navigationWidget();

	//! \return Date and time for begin selection from log.
	QDateTime startDateTime() const;

	//! \return Date and time for end slection from log.
	QDateTime endDateTime() const;

	//! \return Channel name.
	QString channelName() const;

	//! \return Type name.
	QString typeName() const;

	//! \return Source name.
	QString sourceName() const;

private slots:
	//! Set start time to the launching app time.
	void setStartTimeToLaunchTime();
	//! Set end time to the current time.
	void setEndTimeToCurrent();
	//! Channel name changed.
	void channelNameChanged( const QString & text );
	//! New channel.
	void chanelCreated( Channel * ch );
	//! Channel removed.
	void channelRemoved( Channel * ch );
	//! New sources available.
	void newSource( const Como::Source & source, const QString & channelName );
	//! Type changed.
	void typeChanged( const QString & text );

private:
	//! Init.
	void init();
	//! Clear types.
	void clearTypes();
	//! Clear names.
	void clearNames();

private:
	Q_DISABLE_COPY( LogSourcesSelector )

	QScopedPointer< LogSourcesSelectorPrivate > d;
}; // class LogSourcesSelector

} /* namespace Globe */

#endif // GLOBE__LOG_SOURCES_SELECTOR_HPP__INCLUDED

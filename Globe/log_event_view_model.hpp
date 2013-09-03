
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

#ifndef GLOBE__LOG_EVENT_VIEW_MODEL_HPP__INCLUDED
#define GLOBE__LOG_EVENT_VIEW_MODEL_HPP__INCLUDED

// Qt include.
#include <QAbstractTableModel>
#include <QScopedPointer>

// Globe include.
#include<Globe/log.hpp>


namespace Globe {

//
// LogEventRecord
//

//! Record in event's log.
class LogEventRecord {
public:
	LogEventRecord();

	LogEventRecord( LogLevel level,
		const QString & dt,
		const QString & msg );

	LogEventRecord( const LogEventRecord & other );

	LogEventRecord & operator = ( const LogEventRecord & other );

	//! \return Level.
	LogLevel level() const;
	//! Set level.
	void setLevel( LogLevel l );

	//! \return Date and time.
	const QString & dateTime() const;
	//! Set date and time.
	void setDateTime( const QString & dt );

	//! \return Message.
	const QString & message() const;
	//! Set message.
	void setMessage( const QString & msg );

private:
	//! Level.
	LogLevel m_level;
	//! Date and time.
	QString m_dateTime;
	//! Message.
	QString m_message;
}; // class LogEventRecord


//
// LogEventViewModel
//

class LogEventViewModelPrivate;

//! Model for the event log.
class LogEventViewModel
	:	public QAbstractTableModel
{
	Q_OBJECT

public:
	LogEventViewModel( QObject * parent = 0 );

	~LogEventViewModel();

	//! \return Record.
	const LogEventRecord & record( const QModelIndex & index ) const;

	//! Init model.
	void initModel( const QList< LogEventRecord > & data );

	//! Clear model.
	void clear();

	//! \return Count of the rows.
	int rowCount( const QModelIndex & parent = QModelIndex() ) const;
	//! \return Count of the columns.
	int columnCount( const QModelIndex & parent = QModelIndex() ) const;
	//! \return Data by the given index and role.
	QVariant data( const QModelIndex & index,
		int role = Qt::DisplayRole ) const;
	//! Set data.
	bool setData( const QModelIndex & index, const QVariant & value,
		int role = Qt::EditRole );
	//! \return Flags.
	Qt::ItemFlags flags( const QModelIndex & index ) const;
	//! \return Header data.
	QVariant headerData( int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole ) const;

private:
	Q_DISABLE_COPY( LogEventViewModel )

	QScopedPointer< LogEventViewModelPrivate > d;
}; // class LogEventViewModel

} /* namespace Globe */

#endif // GLOBE__LOG_EVENT_VIEW_MODEL_HPP__INCLUDED

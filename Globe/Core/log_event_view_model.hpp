
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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

#ifndef GLOBE__LOG_EVENT_VIEW_MODEL_HPP__INCLUDED
#define GLOBE__LOG_EVENT_VIEW_MODEL_HPP__INCLUDED

// Qt include.
#include <QAbstractTableModel>
#include <QScopedPointer>

// Globe include.
#include <Globe/Core/log.hpp>
#include <Globe/Core/export.hpp>


namespace Globe {

//
// LogEventRecord
//

//! Record in event's log.
class CORE_EXPORT LogEventRecord {
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
class CORE_EXPORT LogEventViewModel
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

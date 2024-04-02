
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__LOG_EVENT_VIEW_MODEL_HPP__INCLUDED
#define GLOBE__LOG_EVENT_VIEW_MODEL_HPP__INCLUDED

// Qt include.
#include <QAbstractTableModel>
#include <QScopedPointer>

// Globe include.
#include <Core/log.hpp>
#include <Core/export.hpp>


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


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__LOG_SOURCES_MODEL_HPP__INCLUDED
#define GLOBE__LOG_SOURCES_MODEL_HPP__INCLUDED

// Qt include.
#include <QAbstractTableModel>
#include <QScopedPointer>

// Como include.
#include <Como/Source>


namespace Globe {

//
// LogSourcesRecord
//

//! Record in sources log.
class LogSourcesRecord {
public:
	LogSourcesRecord();

	LogSourcesRecord( const QString & dt,
		const QString & channelName,
		const Como::Source & source );

	LogSourcesRecord( const LogSourcesRecord & other );

	LogSourcesRecord & operator = ( const LogSourcesRecord & other );

	//! \return Date and time.
	const QString & dateTime() const;
	//! Set date and time.
	void setDateTime( const QString & dt );

	//! \return Channel name.
	const QString & channelName() const;
	//! Set channel name.
	void setChannelName( const QString & name );

	//! \return Source.
	const Como::Source & source() const;
	//! Set source.
	void setSource( const Como::Source & s );

private:
	//! Date and time.
	QString m_dateTime;
	//! Channel name.
	QString m_channelName;
	//! Source.
	Como::Source m_source;
}; // class LogSourcesRecord


//
// LogSourcesModel
//

class LogSourcesModelPrivate;

//! Model for the sources log.
class LogSourcesModel
	:	public QAbstractTableModel
{
	Q_OBJECT

public:
	LogSourcesModel( QObject * parent = 0 );

	~LogSourcesModel();

	//! \return Record.
	const LogSourcesRecord & record( const QModelIndex & index ) const;

	//! Init model.
	void initModel( const QList< LogSourcesRecord > & data );

	//! Clear model.
	void clear();

	//! \return Count of the rows.
	int rowCount( const QModelIndex & parent = QModelIndex() ) const;
	//! \return Count of the columns.
	int columnCount( const QModelIndex & parent = QModelIndex() ) const;
	//! \return Data by the given index and role.
	QVariant data( const QModelIndex & index,
		int role = Qt::DisplayRole ) const;
	//! \return Flags.
	Qt::ItemFlags flags( const QModelIndex & index ) const;
	//! \return Header data.
	QVariant headerData( int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole ) const;

private:
	Q_DISABLE_COPY( LogSourcesModel )

	QScopedPointer< LogSourcesModelPrivate > d;
}; // class LogSourcesModel

} /* namespace Globe */

#endif // GLOBE__LOG_SOURCES_MODEL_HPP__INCLUDED

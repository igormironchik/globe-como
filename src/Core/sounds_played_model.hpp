
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SOUNDS_PLAYED_MODEL_HPP__INCLUDED
#define GLOBE__SOUNDS_PLAYED_MODEL_HPP__INCLUDED

// Qt include.
#include <QAbstractTableModel>
#include <QScopedPointer>

// Como include.
#include <Como/Source>

// Globe include.
#include <Core/condition.hpp>


namespace Globe {

//
// PlayedSoundsModelRecord
//

//! Record in the model of the played sounds.
class PlayedSoundsModelRecord {
public:
	PlayedSoundsModelRecord();

	PlayedSoundsModelRecord( const QDateTime & dt,
		Level level, const QString & channelName,
		const Como::Source & source );

	PlayedSoundsModelRecord( const PlayedSoundsModelRecord & other );

	PlayedSoundsModelRecord & operator = (
		const PlayedSoundsModelRecord & other );

	//! \return Date and time.
	const QDateTime & dateTime() const;
	//! Set date and time.
	void setDateTime( const QDateTime & dt );

	//! \return Level.
	Level level() const;
	//! Set level.
	void setLevel( Level l );

	//! \return Channel's name.
	const QString & channelName() const;
	//! Set channel's name.
	void setChannelName( const QString & name );

	//! \return Source.
	const Como::Source & source() const;
	//! \return Source.
	Como::Source & source();
	//! Set source.
	void setSource( const Como::Source & s );

private:
	//! Date and time.
	QDateTime m_dateTime;
	//! Level.
	Level m_level;
	//! Channel's name.
	QString m_channelName;
	//! Source.
	Como::Source m_source;
}; // class PlayedSoundsModelRecord


//
// PlayedSoundsModel
//

class PlayedSoundsModelPrivate;

//! Model for the played sounds.
class PlayedSoundsModel
	:	public QAbstractTableModel
{
	Q_OBJECT

public:
	PlayedSoundsModel( QObject * parent = 0 );

	~PlayedSoundsModel();

	//! Add record.
	void addRecord( const PlayedSoundsModelRecord & r );

	//! \return Record for the given index.
	const PlayedSoundsModelRecord & record( const QModelIndex & index ) const;

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
	Q_DISABLE_COPY( PlayedSoundsModel )

	QScopedPointer< PlayedSoundsModelPrivate > d;
}; // class PlayedSoundsModel

} /* namespace Globe */

#endif // GLOBE__SOUNDS_PLAYED_MODEL_HPP__INCLUDED

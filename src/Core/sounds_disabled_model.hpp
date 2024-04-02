
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SOUNDS_DISABLED_MODEL_HPP__INCLUDED
#define GLOBE__SOUNDS_DISABLED_MODEL_HPP__INCLUDED

// Qt include.
#include <QAbstractTableModel>
#include <QScopedPointer>

// Como include.
#include <Como/Source>


namespace Globe {

//
// DisabledSoundsModel
//

class DisabledSoundsModelPrivate;

//! Model with disabled sounds.
class DisabledSoundsModel
	:	public QAbstractTableModel
{
	Q_OBJECT

signals:
	//! Resort needed.
	void resortNeeded();

public:
	DisabledSoundsModel( QObject * parent = 0 );

	~DisabledSoundsModel();

	//! Enable sound.
	void enableSound( const QModelIndex & index );

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

private slots:
	//! Sounds disabled.
	void soundsDisabled( const Como::Source & source,
		const QString & channelName,
		const QDateTime & to );

	//! Sounds enabled.
	void soundsEnabled( const Como::Source & source,
		const QString & channelName );

private:
	Q_DISABLE_COPY( DisabledSoundsModel )

	QScopedPointer< DisabledSoundsModelPrivate > d;
}; // class DisabledSoundsModel

} /* namespace Globe */

#endif // GLOBE__SOUNDS_DISABLED_MODEL_HPP__INCLUDED

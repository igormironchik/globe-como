
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef COMO__SAMPLES__QLISTVIEW_CLIENT__MODEL_HPP__INCLUDED
#define COMO__SAMPLES__QLISTVIEW_CLIENT__MODEL_HPP__INCLUDED

// Qt include.
#include <QAbstractTableModel>
#include <QScopedPointer>
#include <QColor>

// Como include.
#include <Como/ClientSocket>
#include <Como/Source>


//
// Model
//

//! Model with Como::Source sources.
class Model
	:	public QAbstractTableModel
{
	Q_OBJECT

public:
	Model( Como::ClientSocket * socket,
		QObject * parent = 0 );
	~Model();

	//! \return Color for the item with index.
	QColor color( const QModelIndex & index );

	//! Clear model.
	void clear();

	//! \return Count of the rows.
	int rowCount( const QModelIndex & parent = QModelIndex() ) const;
	//! \return Count of the columns.
	int columnCount( const QModelIndex & parent = QModelIndex() ) const;
	//! \return Data by the given index and role.
	QVariant data( const QModelIndex & index,
		int role = Qt::DisplayRole ) const;
	//! Insert rows to the model.
	bool insertRows( int row, int count,
		const QModelIndex & parent = QModelIndex() );
	//! Remove rows from the model.
	bool removeRows( int row, int count,
		const QModelIndex & parent = QModelIndex() );
	//! Set data.
	bool setData( const QModelIndex & index, const QVariant & value,
		int role = Qt::EditRole );
	//! \return Flags.
	Qt::ItemFlags flags( const QModelIndex & index ) const;
	//! \return Header data.
	QVariant headerData( int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole ) const;
	//! Sort model.
	void sort( int column, Qt::SortOrder order = Qt::AscendingOrder );

private slots:
	//! Source has been deinitialized.
	void slotSourceHasBeenDeinitialized( const Como::Source & source );
	//! Source has updated his value.
	void slotSourceHasUpdatedValue( const Como::Source & source );

private:
	Q_DISABLE_COPY( Model )

	//! Private implementation.
	struct ModelPrivate;
	//! Private implementation.
	QScopedPointer< ModelPrivate > d;
}; // class Model

#endif // COMO__SAMPLES__QLISTVIEW_CLIENT__MODEL_HPP__INCLUDED

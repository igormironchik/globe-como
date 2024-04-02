
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__PROPERTIES_MODEL_HPP__INCLUDED
#define GLOBE__PROPERTIES_MODEL_HPP__INCLUDED

// Qt include.
#include <QAbstractTableModel>
#include <QScopedPointer>

// Globe include.
#include <Core/properties_map.hpp>


namespace Globe {

//
// PropertiesModel
//

class PropertiesModelPrivate;

//! Model with Como::Source sources.
class PropertiesModel
	:	public QAbstractTableModel
{
	Q_OBJECT

public:
	PropertiesModel( QObject * parent = 0 );
	~PropertiesModel();

	//! Init model with the properties map.
	void initModel( const PropertiesMap & exactlyThisSourceMap,
		const PropertiesMap & exactlyThisSourceInAnyChannelMap,
		const PropertiesMap & exactlyThisTypeOfSourceMap,
		const PropertiesMap & exactlyThisTypeOfSourceInAnyChannelMap );

	//! \return Properties key for the given row.
	PropertiesKey key( int row ) const;
	//! \return Row for the given key.
	int rowForKey( const PropertiesKey & key ) const;
	// Add propertie.
	void addPropertie( const PropertiesKey & key, const PropertiesValue & value );
	//! Remove propertie.
	void removePropertie( int row );
	//! Remove propertie.
	void removePropertie( const PropertiesKey & key );

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

private:
	Q_DISABLE_COPY( PropertiesModel )

	QScopedPointer< PropertiesModelPrivate > d;
}; // class PropertiesModel

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_MODEL_HPP__INCLUDED

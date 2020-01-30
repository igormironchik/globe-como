
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2020 Igor Mironchik

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

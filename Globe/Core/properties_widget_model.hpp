
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

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

#ifndef GLOBE__PROPERTIES_WIDGET_MODEL_HPP__INCLUDED
#define GLOBE__PROPERTIES_WIDGET_MODEL_HPP__INCLUDED

// Qt include.
#include <QAbstractTableModel>
#include <QScopedPointer>

// Globe include.
#include <Globe/Core/properties.hpp>


namespace Globe {

//
// PropertiesListModel
//

class PropertiesListModelPrivate;

//! Model with Como::Source sources.
class PropertiesListModel
	:	public QAbstractTableModel
{
	Q_OBJECT

signals:
	//! Wrong properties.
	void wrongProperties();
	//! Changed.
	void changed();

public:
	explicit PropertiesListModel( Como::Source::Type valueType,
		QObject * parent = 0 );
	~PropertiesListModel();

	//! \return Properties.
	Properties properties() const;
	//! Init model with the properties.
	void setProperties( const Properties & props );

	//! Clear model.
	void clear();

	//! \return Is otherwise condition exists?
	bool isOtherwiseConditionExists() const;

	//! Add condition.
	void addCondition();
	//! Add otherwise condition.
	void addOtherwiseCondition();
	//! Remove condition. \return Is operation completed successfully?
	bool removeCondition( int row );
	//! Move condition up. \return Is operation completed successfully?
	bool moveConditionUp( int row );
	//! Move condition down. \return Is operation completed successfully?
	bool moveConditionDown( int row );

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
	Q_DISABLE_COPY( PropertiesListModel )

	QScopedPointer< PropertiesListModelPrivate > d;
}; // class PropertiesListModel

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_WIDGET_MODEL_HPP__INCLUDED

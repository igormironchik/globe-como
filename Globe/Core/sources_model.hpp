
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

#ifndef GLOBE__SOURCES_MODEL_HPP__INCLUDED
#define GLOBE__SOURCES_MODEL_HPP__INCLUDED

// Qt include.
#include <QAbstractTableModel>
#include <QScopedPointer>

// Como include.
#include <Como/Source>


namespace Globe {

//
// SourcesModel
//

class SourcesModelPrivate;

//! Model with Como::Source sources.
class SourcesModel
	:	public QAbstractTableModel
{
	Q_OBJECT

public:
	SourcesModel( QObject * parent = 0 );
	~SourcesModel();

	//! Init model with the sources list.
	void initModel( const QList< Como::Source > & sources );

	//! Add item.
	void addItem( const Como::Source & source );

	//! Clear model.
	void clear();

	//! Set channel name.
	void setChannelName( const QString & name );

	//! \return Como source for the given index.
	const Como::Source & source( const QModelIndex & index ) const;

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

	QStringList mimeTypes() const;
	QMimeData * mimeData( const QModelIndexList & indexes ) const;

private:
	Q_DISABLE_COPY( SourcesModel )

	QScopedPointer< SourcesModelPrivate > d;
}; // class SourcesModel

} /* namespace Globe */

#endif // GLOBE__SOURCES_MODEL_HPP__INCLUDED

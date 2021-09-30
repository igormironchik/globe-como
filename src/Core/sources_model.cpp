
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

// Globe include.
#include <Core/sources_model.hpp>
#include <Core/utils.hpp>

// Qt include.
#include <QList>
#include <QByteArray>
#include <QDataStream>
#include <QMimeData>
#include <QStringList>
#include <QIODevice>


namespace Globe {

//
// SourcesModelPrivate
//

class SourcesModelPrivate {
public:
	//! Data.
	QList< Como::Source > m_data;
	//! Channel name.
	QString m_channelName;
}; // class SourcesModelPrivate


//
// SourcesModel
//

static const int sourceNameColumn = 0;
static const int sourceTypeNameColumn = 1;
static const int valueTypeColumn = 2;

SourcesModel::SourcesModel( QObject * parent )
	:	QAbstractTableModel( parent )
	,	d( new SourcesModelPrivate )
{
}

SourcesModel::~SourcesModel()
{
}

void
SourcesModel::initModel( const QList< Como::Source > & sources )
{
	clear();

	insertRows( 0, sources.size(), QModelIndex() );

	d->m_data = sources;

	emit dataChanged( QAbstractTableModel::index( 0, sourceNameColumn ),
		QAbstractTableModel::index( sources.size() - 1, valueTypeColumn ) );
}

void
SourcesModel::addItem( const Como::Source & source )
{
	insertRow( d->m_data.size() );

	const int row = d->m_data.size() - 1;

	d->m_data[ row ] = source;

	emit dataChanged( QAbstractTableModel::index( row, sourceNameColumn ),
		QAbstractTableModel::index( row, valueTypeColumn ) );
}

void
SourcesModel::clear()
{
	beginResetModel();
	d->m_data.clear();
	endResetModel();
}

void
SourcesModel::setChannelName( const QString & name )
{
	d->m_channelName = name;
}

const Como::Source &
SourcesModel::source( const QModelIndex & index ) const
{
	return d->m_data.at( index.row() );
}

int
SourcesModel::rowCount( const QModelIndex & parent ) const
{
	if( !parent.isValid() )
		return d->m_data.size();
	else
		return 0;
}

int
SourcesModel::columnCount( const QModelIndex & parent ) const
{
	Q_UNUSED( parent )

	return 3;
}

QVariant
SourcesModel::data( const QModelIndex & index, int role ) const
{
	const int column = index.column();

	if( role == Qt::DisplayRole )
	{
		switch( column )
		{
			case sourceNameColumn :
				return ( d->m_data[ index.row() ].name() );
			case sourceTypeNameColumn :
				return d->m_data[ index.row() ].typeName();
			case valueTypeColumn :
				return comoSourceTypeToString( d->m_data[ index.row() ].type() );
			default :
				return QVariant();
		}
	}
	else
		return QVariant();
}

bool
SourcesModel::insertRows( int row, int count, const QModelIndex & parent )
{
	Q_UNUSED( parent );

	if( count > 0 )
	{
		beginInsertRows( QModelIndex(), row, row + count - 1 );

		for( int i = 0; i < count; ++i )
			d->m_data.insert( row + i, Como::Source() );

		endInsertRows();

		return true;
	}
	else
		return false;
}

bool
SourcesModel::removeRows( int row, int count, const QModelIndex & parent )
{
	Q_UNUSED( parent );

	beginRemoveRows( QModelIndex(), row, row + count - 1 );

	for( int i = 0; i < count; ++i )
		d->m_data.removeAt( row );

	endRemoveRows();

	return true;
}

bool
SourcesModel::setData( const QModelIndex & index, const QVariant & value, int role )
{
	const int column = index.column();
	const int row = index.row();

	if( role == Qt::DisplayRole )
	{
		switch( column )
		{
			case sourceNameColumn :
				d->m_data[ row ].setName( value.toString() ); break;
			case sourceTypeNameColumn :
				d->m_data[ row ].setTypeName( value.toString() ); break;
			case valueTypeColumn :
				d->m_data[ row ].setType( stringToComoSourceType(
					value.toString() ) ); break;
		}
	}

	emit dataChanged( QAbstractTableModel::index( index.row(), column ),
		QAbstractTableModel::index( index.row(), column ) );

	return true;
}

Qt::ItemFlags
SourcesModel::flags( const QModelIndex & index ) const
{
	if( index.isValid() )
		return ( Qt::ItemIsDragEnabled | Qt::ItemIsSelectable |
			Qt::ItemIsEnabled );
	else
		return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
}

QVariant
SourcesModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
	if( role != Qt::DisplayRole )
		return QVariant();

	if( orientation == Qt::Horizontal )
	{
		switch ( section )
		{
			case sourceNameColumn : return tr( "Source name" );
			case sourceTypeNameColumn : return tr( "Type Name" );
			case valueTypeColumn : return tr( "Value Type" );
			default : return QVariant();
		}
	}

	return QVariant();
}

QStringList
SourcesModel::mimeTypes() const
{
	QStringList types;
	types << QLatin1String( "application/como.source" );
	return types;
}

QMimeData *
SourcesModel::mimeData( const QModelIndexList & indexes ) const
{
	QMimeData * mimeData = new QMimeData();
	QByteArray encodedData;

	QDataStream stream( &encodedData, QIODevice::WriteOnly );

	const Como::Source & s = source( indexes.first() );

	stream << d->m_channelName;
	stream << (quint16) s.type();
	stream << s.name();
	stream << s.typeName();
	stream << s.dateTime();
	stream << s.description();
	stream << s.value();

	mimeData->setData( QLatin1String( "application/como.source" ),
		encodedData );

	return mimeData;
}

} /* namespace Globe */

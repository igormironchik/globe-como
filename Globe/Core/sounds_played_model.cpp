
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
#include <Globe/Core/sounds_played_model.hpp>

// Qt include.
#include <QList>


namespace Globe {

//
// PlayedSoundsModelRecord
//

PlayedSoundsModelRecord::PlayedSoundsModelRecord()
	:	m_level( None )
{
}

PlayedSoundsModelRecord::PlayedSoundsModelRecord( const QDateTime & dt,
	Level level, const QString & channelName, const Como::Source & source )
	:	m_dateTime( dt )
	,	m_level( level )
	,	m_channelName( channelName )
	,	m_source( source )
{
}

PlayedSoundsModelRecord::PlayedSoundsModelRecord(
	const PlayedSoundsModelRecord & other )
	:	m_dateTime( other.dateTime() )
	,	m_level( other.level() )
	,	m_channelName( other.channelName() )
	,	m_source( other.source() )
{
}

PlayedSoundsModelRecord &
PlayedSoundsModelRecord::operator = ( const PlayedSoundsModelRecord & other )
{
	if( this != &other )
	{
		m_level = other.level();
		m_channelName = other.channelName();
		m_source = other.source();
		m_dateTime = other.dateTime();
	}

	return *this;
}

const QDateTime &
PlayedSoundsModelRecord::dateTime() const
{
	return m_dateTime;
}

void
PlayedSoundsModelRecord::setDateTime( const QDateTime & dt )
{
	m_dateTime = dt;
}

Level
PlayedSoundsModelRecord::level() const
{
	return m_level;
}

void
PlayedSoundsModelRecord::setLevel( Level l )
{
	m_level = l;
}

const QString &
PlayedSoundsModelRecord::channelName() const
{
	return m_channelName;
}

void
PlayedSoundsModelRecord::setChannelName( const QString & name )
{
	m_channelName = name;
}

const Como::Source &
PlayedSoundsModelRecord::source() const
{
	return m_source;
}

Como::Source &
PlayedSoundsModelRecord::source()
{
	return m_source;
}

void
PlayedSoundsModelRecord::setSource( const Como::Source & s )
{
	m_source = s;
}


//
// PlayedSoundsModelPrivate
//

class PlayedSoundsModelPrivate {
public:
	explicit PlayedSoundsModelPrivate( int maxRows )
		:	m_maxRows( maxRows )
	{
	}

	//! Data.
	QList< PlayedSoundsModelRecord > m_data;
	//! Max count of rows.
	int m_maxRows;
}; // class PlayedSoundsModelPrivate


//
// PlayedSoundsModel
//

static const int maxRowsCount = 100;
static const int dateTimeColumn = 0;
static const int channelNameColumn = 1;
static const int typeNameColumn = 2;
static const int sourceNameColumn = 3;

PlayedSoundsModel::PlayedSoundsModel( QObject * parent )
	:	QAbstractTableModel( parent )
	,	d( new PlayedSoundsModelPrivate( maxRowsCount ) )
{
}

PlayedSoundsModel::~PlayedSoundsModel()
{
}

void
PlayedSoundsModel::addRecord( const PlayedSoundsModelRecord & r )
{
	beginInsertRows( QModelIndex(), 0, 0 );

	d->m_data.prepend( r );

	endInsertRows();

	const int size = d->m_data.size();

	if( size > d->m_maxRows )
	{
		beginRemoveRows( QModelIndex(), size - 1, size - 1 );

		d->m_data.removeLast();

		endRemoveRows();
	}
}

const PlayedSoundsModelRecord &
PlayedSoundsModel::record( const QModelIndex & index ) const
{
	return d->m_data.at( index.row() );
}

int
PlayedSoundsModel::rowCount( const QModelIndex & parent ) const
{
	if( !parent.isValid() )
		return d->m_data.size();
	else
		return 0;
}

int
PlayedSoundsModel::columnCount( const QModelIndex & parent ) const
{
	Q_UNUSED( parent )

	return 4;
}

QVariant
PlayedSoundsModel::data( const QModelIndex & index, int role ) const
{
	const int column = index.column();

	if( role == Qt::DisplayRole )
	{
		switch( column )
		{
			case dateTimeColumn :
				return ( d->m_data[ index.row() ].dateTime() );
			case channelNameColumn :
				return ( d->m_data[ index.row() ].channelName() );
			case typeNameColumn :
				return d->m_data[ index.row() ].source().typeName();
			case sourceNameColumn :
				return d->m_data[ index.row() ].source().name();
			default :
				return QVariant();
		}
	}
	else
		return QVariant();
}

bool
PlayedSoundsModel::setData( const QModelIndex & index, const QVariant & value,
	int role )
{
	const int column = index.column();
	const int row = index.row();

	if( role == Qt::DisplayRole )
	{
		switch( column )
		{
			case dateTimeColumn :
				d->m_data[ row ].setDateTime( value.toDateTime() ); break;
			case channelNameColumn :
				d->m_data[ row ].setChannelName( value.toString() ); break;
			case typeNameColumn :
				d->m_data[ row ].source().setTypeName( value.toString() ); break;
			case sourceNameColumn :
				d->m_data[ row ].source().setName( value.toString() ); break;
		}
	}

	emit dataChanged( QAbstractTableModel::index( row, column ),
		QAbstractTableModel::index( row, column ) );

	return true;
}

Qt::ItemFlags
PlayedSoundsModel::flags( const QModelIndex & index ) const
{
	Q_UNUSED( index )

	return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
}

QVariant
PlayedSoundsModel::headerData( int section, Qt::Orientation orientation,
	int role ) const
{
	if( role != Qt::DisplayRole )
		return QVariant();

	if( orientation == Qt::Horizontal )
	{
		switch ( section )
		{
			case dateTimeColumn : return tr( "Date & Time" );
			case channelNameColumn : return tr( "Channel Name" );
			case typeNameColumn : return tr( "Type Name" );
			case sourceNameColumn : return tr( "Source Name" );
			default : return QVariant();
		}
	}

	return QVariant();
}

} /* namespace Globe */

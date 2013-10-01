
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2013 Igor Mironchik

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

// Globe include.
#include <Globe/sounds_played_model.hpp>

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

PlayedSoundsModelRecord::PlayedSoundsModelRecord( Level level,
	const QString & channelName, const Como::Source & source )
	:	m_level( level )
	,	m_channelName( channelName )
	,	m_source( source )
{
}

PlayedSoundsModelRecord::PlayedSoundsModelRecord(
	const PlayedSoundsModelRecord & other )
	:	m_level( other.level() )
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
	}

	return *this;
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
static const int channelNameColumn = 0;
static const int typeNameColumn = 1;
static const int sourceNameColumn = 2;

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

	return 3;
}

QVariant
PlayedSoundsModel::data( const QModelIndex & index, int role ) const
{
	const int column = index.column();

	if( role == Qt::DisplayRole )
	{
		switch( column )
		{
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
			case channelNameColumn : return tr( "Channel Name" );
			case typeNameColumn : return tr( "Type Name" );
			case sourceNameColumn : return tr( "Source Name" );
			default : return QVariant();
		}
	}

	return QVariant();
}

} /* namespace Globe */

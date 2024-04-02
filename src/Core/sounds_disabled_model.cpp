
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/sounds_disabled_model.hpp>
#include <Core/sounds_disabled.hpp>

// Qt include.
#include <QList>


namespace Globe {

//
// DisabledSoundsModelData
//

class DisabledSoundsModelData {
public:
	DisabledSoundsModelData()
	{
	}

	DisabledSoundsModelData( const QString & channelName,
		const Como::Source & source,
		const QDateTime & dt )
		:	m_channelName( channelName )
		,	m_source( source )
		,	m_to( dt )
	{
	}

	DisabledSoundsModelData( const DisabledSoundsModelData & other )
		:	m_channelName( other.m_channelName )
		,	m_source( other.m_source )
		,	m_to( other.m_to )
	{
	}

	DisabledSoundsModelData & operator = ( const DisabledSoundsModelData & other )
	{
		if( this != &other )
		{
			m_channelName = other.m_channelName;
			m_source = other.m_source;
			m_to = other.m_to;
		}

		return *this;
	}

	//! Channel name.
	QString m_channelName;
	//! Source.
	Como::Source m_source;
	//! To.
	QDateTime m_to;
}; // class DisabledSoundsModelData


//
// DisabledSoundsModelPrivate
//

class DisabledSoundsModelPrivate {
public:
	DisabledSoundsModelPrivate()
	{
	}

	//! \return Index for the data.
	int dataIndex( const QString & channelName,
		const Como::Source & source )
	{
		int index = 0;

		foreach( const DisabledSoundsModelData & data, m_data )
		{
			if( data.m_channelName == channelName &&
				data.m_source == source )
					return index;

			++index;
		}

		return -1;
	}

	//! Data.
	QList< DisabledSoundsModelData > m_data;
}; // class DisabledSoundsModelPrivate


//
// DisabledSoundsModel
//

static const int channelNameColumn = 0;
static const int typeNameColumn = 1;
static const int sourceNameColumn = 2;
static const int disabledToColumn = 3;

DisabledSoundsModel::DisabledSoundsModel( QObject * parent )
	:	QAbstractTableModel( parent )
	,	d( new DisabledSoundsModelPrivate )
{
	connect( &DisabledSounds::instance(), &DisabledSounds::soundsDisabled,
		this, &DisabledSoundsModel::soundsDisabled );

	connect( &DisabledSounds::instance(), &DisabledSounds::soundsEnabled,
		this, &DisabledSoundsModel::soundsEnabled );
}

DisabledSoundsModel::~DisabledSoundsModel()
{
}

void
DisabledSoundsModel::enableSound( const QModelIndex & index )
{
	if( index.isValid() )
	{
		DisabledSounds::instance().enableSounds(
			d->m_data.at( index.row() ).m_source,
			d->m_data.at( index.row() ).m_channelName );
	}
}

int
DisabledSoundsModel::rowCount( const QModelIndex & parent ) const
{
	if( !parent.isValid() )
		return d->m_data.size();
	else
		return 0;
}

int
DisabledSoundsModel::columnCount( const QModelIndex & parent ) const
{
	Q_UNUSED( parent )

	return 4;
}

QVariant
DisabledSoundsModel::data( const QModelIndex & index, int role ) const
{
	const int column = index.column();

	if( role == Qt::DisplayRole )
	{
		switch( column )
		{
			case channelNameColumn :
				return d->m_data[ index.row() ].m_channelName;
			case typeNameColumn :
				return d->m_data[ index.row() ].m_source.typeName();
			case sourceNameColumn :
				return d->m_data[ index.row() ].m_source.name();
			case disabledToColumn :
				return d->m_data[ index.row() ].m_to;
			default :
				return QVariant();
		}
	}
	else
		return QVariant();
}

bool
DisabledSoundsModel::setData( const QModelIndex & index, const QVariant & value,
	int role )
{
	const int column = index.column();
	const int row = index.row();

	if( role == Qt::DisplayRole )
	{
		switch( column )
		{
			case channelNameColumn :
				d->m_data[ row ].m_channelName = value.toString(); break;
			case typeNameColumn :
				d->m_data[ row ].m_source.setTypeName( value.toString() ); break;
			case sourceNameColumn :
				d->m_data[ row ].m_source.setName( value.toString() ); break;
			case disabledToColumn :
				d->m_data[ row ].m_to = value.toDateTime(); break;
		}
	}

	emit dataChanged( QAbstractTableModel::index( row, column ),
		QAbstractTableModel::index( row, column ) );

	return true;
}

Qt::ItemFlags
DisabledSoundsModel::flags( const QModelIndex & index ) const
{
	Q_UNUSED( index )

	return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
}

QVariant
DisabledSoundsModel::headerData( int section, Qt::Orientation orientation,
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
			case disabledToColumn : return tr( "Disabled To" );
			default : return QVariant();
		}
	}

	return QVariant();
}

void
DisabledSoundsModel::soundsDisabled( const Como::Source & source,
	const QString & channelName,
	const QDateTime & to )
{
	beginInsertRows( QModelIndex(), d->m_data.size(), d->m_data.size() );

	d->m_data.append( DisabledSoundsModelData( channelName, source, to ) );

	endInsertRows();

	emit resortNeeded();
}

void
DisabledSoundsModel::soundsEnabled( const Como::Source & source,
	const QString & channelName )
{
	const int index = d->dataIndex( channelName, source );

	if( index != -1 )
	{
		beginRemoveRows( QModelIndex(), index, index );

		d->m_data.removeAt( index );

		endRemoveRows();
	}
}

} /* namespace Globe */

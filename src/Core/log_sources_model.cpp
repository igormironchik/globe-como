
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/log_sources_model.hpp>

// Qt include.
#include <QList>


namespace Globe {

//
// LogSourcesRecord
//

LogSourcesRecord::LogSourcesRecord()
{
}

LogSourcesRecord::LogSourcesRecord( const QString & dt,
	const QString & channelName, const Como::Source & source )
	:	m_dateTime( dt )
	,	m_channelName( channelName )
	,	m_source( source )
{
}

LogSourcesRecord::LogSourcesRecord( const LogSourcesRecord & other )
	:	m_dateTime( other.dateTime() )
	,	m_channelName( other.channelName() )
	,	m_source( other.source() )
{
}

LogSourcesRecord &
LogSourcesRecord::operator = ( const LogSourcesRecord & other )
{
	if( this != &other )
	{
		m_dateTime = other.dateTime();
		m_channelName = other.channelName();
		m_source = other.source();
	}

	return *this;
}

const QString &
LogSourcesRecord::dateTime() const
{
	return m_dateTime;
}

void
LogSourcesRecord::setDateTime( const QString & dt )
{
	m_dateTime = dt;
}

const QString &
LogSourcesRecord::channelName() const
{
	return m_channelName;
}

void
LogSourcesRecord::setChannelName( const QString & name )
{
	m_channelName = name;
}

const Como::Source &
LogSourcesRecord::source() const
{
	return m_source;
}

void
LogSourcesRecord::setSource( const Como::Source & s )
{
	m_source = s;
}


//
// LogSourcesModelPrivate
//

class LogSourcesModelPrivate {
public:
	LogSourcesModelPrivate()
	{
	}

	//! Data.
	QList< LogSourcesRecord > m_data;
}; // class LogSourcesModelPrivate


//
// LogSourcesModel
//

LogSourcesModel::LogSourcesModel( QObject * parent )
	:	QAbstractTableModel( parent )
	,	d( new LogSourcesModelPrivate )
{
}

LogSourcesModel::~LogSourcesModel()
{
}

const LogSourcesRecord &
LogSourcesModel::record( const QModelIndex & index ) const
{
	return d->m_data.at( index.row() );
}

void
LogSourcesModel::initModel( const QList< LogSourcesRecord > & data )
{
	clear();

	if( !data.isEmpty() )
	{
		beginInsertRows( QModelIndex(), 0, data.size() - 1 );

		d->m_data = data;

		endInsertRows();
	}
}

void
LogSourcesModel::clear()
{
	beginResetModel();

	d->m_data.clear();

	endResetModel();
}

int
LogSourcesModel::rowCount( const QModelIndex & parent ) const
{
	if( !parent.isValid() )
		return d->m_data.size();
	else
		return 0;
}

int
LogSourcesModel::columnCount( const QModelIndex & parent ) const
{
	Q_UNUSED( parent )

	return 6;
}

static const int dateTimeColumn = 0;
static const int channelNameColumn = 1;
static const int typeNameColumn = 2;
static const int sourceNameColumn = 3;
static const int valueColumn = 4;
static const int descriptionColumn = 5;

QVariant
LogSourcesModel::data( const QModelIndex & index, int role ) const
{
	const int column = index.column();

	if( role == Qt::DisplayRole )
	{
		switch( column )
		{
			case dateTimeColumn :
				return d->m_data[ index.row() ].dateTime();
			case channelNameColumn :
				return d->m_data[ index.row() ].channelName();
			case typeNameColumn :
				return d->m_data[ index.row() ].source().typeName();
			case sourceNameColumn :
				return d->m_data[ index.row() ].source().name();
			case valueColumn :
				return d->m_data[ index.row() ].source().value();
			case descriptionColumn :
				return d->m_data[ index.row() ].source().description();
			default :
				return QVariant();
		}
	}
	else
		return QVariant();
}

Qt::ItemFlags
LogSourcesModel::flags( const QModelIndex & index ) const
{
	Q_UNUSED( index )

	return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
}

QVariant
LogSourcesModel::headerData( int section, Qt::Orientation orientation,
	int role ) const
{
	if( role != Qt::DisplayRole )
		return QVariant();

	if( orientation == Qt::Horizontal )
	{
		switch ( section )
		{
			case dateTimeColumn : return tr( "Date & Time" );
			case channelNameColumn : return tr( "Channel" );
			case typeNameColumn : return tr( "Type" );
			case sourceNameColumn : return tr( "Source" );
			case valueColumn : return tr( "Value" );
			case descriptionColumn : return tr( "Description" );
			default : return QVariant();
		}
	}

	return QVariant();
}

} /* namespace Globe */

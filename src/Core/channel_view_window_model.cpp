
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/channel_view_window_model.hpp>
#include <Core/properties_manager.hpp>
#include <Core/sources.hpp>
#include <Core/channels.hpp>

// Qt include.
#include <QList>
#include <QByteArray>
#include <QDataStream>
#include <QMimeData>


namespace Globe {

//
// ChannelViewWindowModelData
//

class ChannelViewWindowModelData {
public:
	ChannelViewWindowModelData()
		:	m_priority( 0 )
		,	m_isRegistered( false )
		,	m_level( None )
	{
	}

	ChannelViewWindowModelData( const Como::Source & source,
		int priority, bool isRegistered, Level level )
		:	m_source( source )
		,	m_priority( priority )
		,	m_isRegistered( isRegistered )
		,	m_level( level )
	{
	}

	//! Source.
	Como::Source m_source;
	//! Priority.
	int m_priority;
	//! Is source registered?
	bool m_isRegistered;
	//! Level.
	Level m_level;
}; // class ChannelViewWindowModelData


//
// ChannelViewWindowModelPrivate
//

class ChannelViewWindowModelPrivate {
public:
	ChannelViewWindowModelPrivate()
		:	m_isConnected( false )
	{
	}

	//! \return Index of the data with the given source.
	int findData( const Como::Source & source )
	{
		const int size = m_data.size();

		for( int i = 0; i < size; ++i )
			if( m_data.at( i ).m_source == source )
				return i;

		return -1;
	}

	//! Data.
	QList< ChannelViewWindowModelData > m_data;
	//! Channel name.
	QString m_channelName;
	//! Is channel connected?
	bool m_isConnected;
}; // class ChannelViewWindowModelPrivate


//
// ChannelViewWindowModel
//

ChannelViewWindowModel::ChannelViewWindowModel( QObject * parent )
	:	QAbstractTableModel( parent )
	,	d( new ChannelViewWindowModelPrivate )
{
	connect( &SourcesManager::instance(), &SourcesManager::newSource,
		this, &ChannelViewWindowModel::newSource );

	connect( &PropertiesManager::instance(),
		&PropertiesManager::propertiesChanged,
		this, &ChannelViewWindowModel::propertiesChanged );

	connect( &ChannelsManager::instance(),
		&ChannelsManager::channelRemoved,
		this, &ChannelViewWindowModel::channelRemoved );
}

ChannelViewWindowModel::~ChannelViewWindowModel()
{
}

const QString &
ChannelViewWindowModel::channelName() const
{
	return d->m_channelName;
}

void
ChannelViewWindowModel::initModel( const QString & channelName )
{
	if( !channelName.isEmpty() )
	{
		Channel * channel = ChannelsManager::instance()
			.channelByName( channelName );

		if( channel )
		{
			clear();

			d->m_channelName = channelName;

			d->m_isConnected = channel->isConnected();

			connect( channel, &Channel::connected,
				this, &ChannelViewWindowModel::connected );
			connect( channel, &Channel::disconnected,
				this, &ChannelViewWindowModel::disconnected );
			connect( channel, &Channel::sourceDeregistered,
				this, &ChannelViewWindowModel::sourceDeregistered );
			connect( channel, &Channel::sourceUpdated,
				this, &ChannelViewWindowModel::sourceUpdated );

			const QList< Como::Source > registered = SourcesManager::instance()
				.registeredSources( d->m_channelName );

			const QList< Como::Source > deregistered = SourcesManager::instance()
				.deregisteredSources( d->m_channelName );

			const int registeredCount = registered.size();
			const int deregisteredCount = deregistered.size();
			const int rows = registeredCount + deregisteredCount;

			if( rows > 0 )
			{
				beginInsertRows( QModelIndex(), 0, rows - 1 );

				for( int i = 0; i < registeredCount; ++i )
				{
					const Como::Source & source = registered.at( i );

					const Properties * props = PropertiesManager::instance()
						.findProperties( source, d->m_channelName, 0 );

					int priority = 0;
					Level level = None;

					if( props )
					{
						priority = props->priority();

						level = props->checkConditions( source.value(),
							source.type() ).level();
					}

					d->m_data.insert( i, ChannelViewWindowModelData( source, priority,
						true, level ) );
				}

				for( int i = 0; i < deregisteredCount; ++i )
				{
					const Como::Source & source = deregistered.at( i );

					const Properties * props = PropertiesManager::instance()
						.findProperties( source, d->m_channelName, 0 );

					int priority = 0;
					Level level = None;

					if( props )
					{
						priority = props->priority();

						level = props->checkConditions( source.value(),
							source.type() ).level();
					}

					d->m_data.insert( registeredCount + i,
						ChannelViewWindowModelData( source, priority,
							false, level ) );
				}

				endInsertRows();
			}
		}
	}
}

void
ChannelViewWindowModel::clear()
{
	beginResetModel();

	d->m_data.clear();

	d->m_isConnected = false;

	if( !d->m_channelName.isEmpty() )
	{
		Channel * oldChannel = ChannelsManager::instance()
			.channelByName( d->m_channelName );

		if( oldChannel )
			disconnect( oldChannel, 0, this, 0 );
	}

	endResetModel();
}

void
ChannelViewWindowModel::addItem( const Como::Source & source, bool isRegistered )
{
	const int size = d->m_data.size();

	beginInsertRows( QModelIndex(), size, size );

	const Properties * props = PropertiesManager::instance().findProperties(
		source, d->m_channelName, 0 );

	int priority = 0;
	Level level = None;

	if( props )
	{
		priority = props->priority();

		level = props->checkConditions( source.value(),
			source.type() ).level();
	}

	d->m_data.insert( size, ChannelViewWindowModelData( source, priority,
		isRegistered, level ) );

	endInsertRows();
}

const Como::Source &
ChannelViewWindowModel::source( const QModelIndex & index ) const
{
	return d->m_data.at( index.row() ).m_source;
}

bool
ChannelViewWindowModel::isRegistered( const QModelIndex & index ) const
{
	return d->m_data.at( index.row() ).m_isRegistered;
}

Level
ChannelViewWindowModel::level( const QModelIndex & index ) const
{
	return d->m_data.at( index.row() ).m_level;
}

int
ChannelViewWindowModel::priority( const QModelIndex & index ) const
{
	return d->m_data.at( index.row() ).m_priority;
}

bool
ChannelViewWindowModel::isConnected() const
{
	return d->m_isConnected;
}

void
ChannelViewWindowModel::sourceUpdated( const Como::Source & source )
{
	const int index = d->findData( source );

	if( index != -1 )
	{
		ChannelViewWindowModelData & data = d->m_data[ index ];

		data.m_source = source;

		const Properties * props = PropertiesManager::instance().findProperties(
			source, d->m_channelName, 0 );

		int priority = 0;
		Level level = None;

		if( props )
		{
			priority = props->priority();

			level = props->checkConditions( source.value(),
				source.type() ).level();
		}

		data.m_priority = priority;
		data.m_level = level;
		data.m_isRegistered = true;

		emit dataChanged( QAbstractTableModel::index( index, valueColumn ),
			QAbstractTableModel::index( index, priorityColumn ) );
	}
	else
		addItem( source, true );
}

void
ChannelViewWindowModel::sourceDeregistered( const Como::Source & source )
{
	const int index = d->findData( source );

	if( index != -1 )
	{
		ChannelViewWindowModelData & data = d->m_data[ index ];

		data.m_source = source;

		const Properties * props = PropertiesManager::instance().findProperties(
			source, d->m_channelName, 0 );

		int priority = 0;

		if( props )
			priority = props->priority();

		data.m_priority = priority;

		data.m_isRegistered = false;

		emit dataChanged( QAbstractTableModel::index( index, valueColumn ),
			QAbstractTableModel::index( index, priorityColumn ) );
	}
	else
		addItem( source, false );
}

void
ChannelViewWindowModel::connected()
{
	d->m_isConnected = true;

	beginResetModel();
	d->m_data.clear();
	endResetModel();
}

void
ChannelViewWindowModel::disconnected()
{
	d->m_isConnected = false;

	emit dataChanged( QAbstractTableModel::index( 0, valueColumn ),
		QAbstractTableModel::index( d->m_data.size() - 1, priorityColumn ) );
}

void
ChannelViewWindowModel::newSource( const Como::Source & source,
	const QString & channelName )
{
	if( channelName == d->m_channelName )
		sourceUpdated( source );
}

void
ChannelViewWindowModel::propertiesChanged()
{
	const int size = d->m_data.size();

	bool prChanged = false;

	for( int i = 0; i < size; ++i )
	{
		ChannelViewWindowModelData & data = d->m_data[ i ];

		const Properties * props = PropertiesManager::instance().findProperties(
			data.m_source, d->m_channelName, 0 );

		int priority = 0;
		Level level = None;

		if( props )
		{
			priority = props->priority();

			level = props->checkConditions( data.m_source.value(),
				data.m_source.type() ).level();
		}

		if( priority != data.m_priority )
			prChanged = true;

		if( priority != data.m_priority || level != data.m_level )
		{
			data.m_priority = priority;
			data.m_level = level;

			emit dataChanged( QAbstractTableModel::index( i, valueColumn ),
				QAbstractTableModel::index( i, priorityColumn ) );
		}
	}

	if( prChanged )
		emit priorityChanged();
}

void
ChannelViewWindowModel::channelRemoved( Globe::Channel * ch )
{
	if( ch->name() == d->m_channelName )
		disconnected();
}

int
ChannelViewWindowModel::rowCount( const QModelIndex & parent ) const
{
	if( !parent.isValid() )
		return d->m_data.size();
	else
		return 0;
}

int
ChannelViewWindowModel::columnCount( const QModelIndex & parent ) const
{
	Q_UNUSED( parent )

	return 5;
}

QVariant
ChannelViewWindowModel::data( const QModelIndex & index, int role ) const
{
	const int column = index.column();

	if( role == Qt::DisplayRole )
	{
		switch( column )
		{
			case sourceNameColumn :
				return ( d->m_data[ index.row() ].m_source.name() );
			case sourceTypeNameColumn :
				return d->m_data[ index.row() ].m_source.typeName();
			case valueColumn :
				return d->m_data[ index.row() ].m_source.value();
			case dateTimeColumn :
				return d->m_data[ index.row() ].m_source.dateTime();
			case priorityColumn :
				return d->m_data[ index.row() ].m_priority;
			default :
				return QVariant();
		}
	}
	else if( role == Qt::ToolTipRole )
		return d->m_data[ index.row() ].m_source.description();
	else
		return QVariant();
}

bool
ChannelViewWindowModel::setData( const QModelIndex & index, const QVariant & value, int role )
{
	const int column = index.column();
	const int row = index.row();

	if( role == Qt::DisplayRole )
	{
		switch( column )
		{
			case sourceNameColumn :
				d->m_data[ row ].m_source.setName( value.toString() ); break;
			case sourceTypeNameColumn :
				d->m_data[ row ].m_source.setTypeName( value.toString() ); break;
			case valueColumn :
				d->m_data[ row ].m_source.setValue(	value ); break;
			case dateTimeColumn :
				d->m_data[ row ].m_source.setDateTime( value.toDateTime() ); break;
			case priorityColumn :
				d->m_data[ row ].m_priority = value.toInt(); break;
		}
	}

	emit dataChanged( QAbstractTableModel::index( row, column ),
		QAbstractTableModel::index( row, column ) );

	return true;
}

Qt::ItemFlags
ChannelViewWindowModel::flags( const QModelIndex & index ) const
{
	if( index.isValid() )
		return ( Qt::ItemIsDragEnabled | Qt::ItemIsSelectable |
			Qt::ItemIsEnabled );
	else
		return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
}

QVariant
ChannelViewWindowModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
	if( role != Qt::DisplayRole )
		return QVariant();

	if( orientation == Qt::Horizontal )
	{
		switch ( section )
		{
			case sourceNameColumn : return tr( "Source Name" );
			case sourceTypeNameColumn : return tr( "Type Name" );
			case valueColumn : return tr( "Value" );
			case dateTimeColumn : return tr( "Date & Time" );
			case priorityColumn : return tr( "Pr." );
			default : return QVariant();
		}
	}

	return QVariant();
}

QStringList
ChannelViewWindowModel::mimeTypes() const
{
	QStringList types;
	types << QLatin1String( "application/como.source" );
	return types;
}

QMimeData *
ChannelViewWindowModel::mimeData( const QModelIndexList & indexes ) const
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

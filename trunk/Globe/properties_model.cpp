
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 Igor Mironchik

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
#include <Globe/properties_model.hpp>

// Qt include.
#include <QtCore/QList>


namespace Globe {

//
// Data
//

class Data {
public:
	Data()
	{
	}

	Data( const PropertiesKey & key, const PropertiesValue & value )
		:	m_sourceName( key.name() )
		,	m_typeName( key.typeName() )
		,	m_channelName( key.channelName() )
		,	m_valueType( value.valueType() )
		,	m_confFileName( value.confFileName() )
	{
	}

	Data & operator = ( const Data & other )
	{
		if( this != &other )
		{
			m_sourceName = other.m_sourceName;
			m_typeName = other.m_typeName;
			m_channelName = other.m_channelName;
			m_valueType = other.m_valueType;
			m_confFileName = other.m_confFileName;
		}

		return *this;
	}

	//! Source name.
	QString m_sourceName;
	//! Source type name
	QString m_typeName;
	//! Channel name.
	QString m_channelName;
	//! Value type.
	Como::Source::Type m_valueType;
	//! Conf file name.
	QString m_confFileName;
}; // class Data


//
// PropertiesModelPrivate
//

class PropertiesModelPrivate {
public:
	//! Data.
	QList< Data > m_data;
}; // class PropertiesPropertiesModelPrivate


//
// PropertiesModel
//

static const int sourceNameColumn = 0;
static const int sourceTypeNameColumn = 1;
static const int channelNameColumn = 2;
static const int valueTypeColumn = 3;
static const int confFileColumn = 4;

PropertiesModel::PropertiesModel( QObject * parent )
	:	QAbstractTableModel( parent )
	,	d( new PropertiesModelPrivate )
{
}

PropertiesModel::~PropertiesModel()
{
}

void
PropertiesModel::initModel( const PropertiesMap & map )
{
	clear();

	insertRows( 0, map.size(), QModelIndex() );

	int i = 0;

	for( PropertiesMap::ConstIterator it = map.begin(),
		last = map.end(); it != last; ++it, ++i )
			d->m_data[ i ] = Data( it.key(), it.value() );

	emit dataChanged( QAbstractTableModel::index( 0, sourceNameColumn ),
		QAbstractTableModel::index( i - 1, confFileColumn ) );
}

void
PropertiesModel::clear()
{
	beginResetModel();
	d->m_data.clear();
	endResetModel();
}

int
PropertiesModel::rowCount( const QModelIndex & parent ) const
{
	if( !parent.isValid() )
		return d->m_data.size();
	else
		return 0;
}

int
PropertiesModel::columnCount( const QModelIndex & parent ) const
{
	Q_UNUSED( parent )

	return 5;
}

static const QString intValueType = QLatin1String( "int" );
static const QString doubleValueType = QLatin1String( "double" );
static const QString stringValueType = QLatin1String( "string" );
static const QString unknownValueType = QLatin1String( "unknown" );

static inline QString valueTypeToString( Como::Source::Type type )
{
	switch( type )
	{
		case Como::Source::Int : return intValueType;
		case Como::Source::Double : return doubleValueType;
		case Como::Source::String : return stringValueType;
		default : return unknownValueType;
	}
}

QVariant
PropertiesModel::data( const QModelIndex & index, int role ) const
{
	static const QString anyNameOrChannel = tr( "any" );

	const int column = index.column();

	if( role == Qt::DisplayRole )
	{
		switch( column )
		{
			case sourceNameColumn :
				return ( d->m_data[ index.row() ].m_sourceName.isEmpty() ?
					anyNameOrChannel : d->m_data[ index.row() ].m_sourceName );
			case sourceTypeNameColumn :
				return d->m_data[ index.row() ].m_typeName;
			case channelNameColumn :
				return ( d->m_data[ index.row() ].m_channelName.isEmpty() ?
					anyNameOrChannel : d->m_data[ index.row() ].m_channelName );
			case valueTypeColumn :
				return valueTypeToString( d->m_data[ index.row() ].m_valueType );
			case confFileColumn :
				return d->m_data[ index.row() ].m_confFileName;
			default :
				return QVariant();
		}
	}
	else
		return QVariant();
}

bool
PropertiesModel::insertRows( int row, int count, const QModelIndex & parent )
{
	Q_UNUSED( parent );

	beginInsertRows( QModelIndex(), row, row + count - 1 );

	for( int i = 0; i < count; ++i )
		d->m_data.insert( row + i, Data() );

	endInsertRows();

	return true;
}

bool
PropertiesModel::removeRows( int row, int count, const QModelIndex & parent )
{
	Q_UNUSED( parent );

	beginRemoveRows( QModelIndex(), row, row + count - 1 );

	for( int i = 0; i < count; ++i )
		d->m_data.removeAt( row );

	endRemoveRows();

	return true;
}

static inline Como::Source::Type valueTypeFromString( const QString & type )
{
	if( type == intValueType )
		return Como::Source::Int;
	else if( type == doubleValueType )
		return Como::Source::Double;
	else
		return Como::Source::String;
}

bool
PropertiesModel::setData( const QModelIndex & index, const QVariant & value, int role )
{
	const int column = index.column();
	const int row = index.row();

	if( role == Qt::DisplayRole )
	{
		switch( column )
		{
			case sourceNameColumn :
				d->m_data[ row ].m_sourceName = value.toString(); break;
			case sourceTypeNameColumn :
				d->m_data[ row ].m_typeName = value.toString(); break;
			case channelNameColumn :
				d->m_data[ row ].m_channelName = value.toString(); break;
			case valueTypeColumn :
				d->m_data[ row ].m_valueType = valueTypeFromString(
					value.toString() ); break;
			case confFileColumn :
				d->m_data[ row ].m_confFileName = value.toString(); break;
		}
	}

	emit dataChanged( QAbstractTableModel::index( index.row(), column ),
		QAbstractTableModel::index( index.row(), column ) );

	return true;
}

Qt::ItemFlags
PropertiesModel::flags( const QModelIndex & index ) const
{
	Q_UNUSED( index )

	return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
}

QVariant
PropertiesModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
	if( role != Qt::DisplayRole )
		return QVariant();

	if( orientation == Qt::Horizontal )
	{
		switch ( section )
		{
			case sourceNameColumn : return tr( "Source name" );
			case sourceTypeNameColumn : return tr( "Type Name" );
			case channelNameColumn : return tr( "Channel Name" );
			case valueTypeColumn : return tr( "Value Type" );
			case confFileColumn : return tr( "Configuration file" );
			default : return QVariant();
		}
	}

	return QVariant();
}

} /* namespace Globe */

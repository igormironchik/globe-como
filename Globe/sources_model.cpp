
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
#include <Globe/sources_model.hpp>

// Qt include.
#include <QtCore/QList>


namespace Globe {

//
// SourcesModelPrivate
//

class SourcesModelPrivate {
public:
	//! Data.
	QList< Como::Source > m_data;
}; // class PropertiesSourcesModelPrivate


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

const Como::Source &
SourcesModel::source( const QModelIndex & index ) const
{
	return d->m_data.at( index.row() );
}

int
SourcesModel::rowCount( const QModelIndex & parent ) const
{
	Q_UNUSED( parent )

	return d->m_data.size();
}

int
SourcesModel::columnCount( const QModelIndex & parent ) const
{
	Q_UNUSED( parent )

	return 3;
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
SourcesModel::data( const QModelIndex & index, int role ) const
{
	static const QString anyNameOrChannel = tr( "any" );

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
				return valueTypeToString( d->m_data[ index.row() ].type() );
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

	beginInsertRows( QModelIndex(), row, row + count - 1 );

	for( int i = 0; i < count; ++i )
		d->m_data.insert( row + i, Como::Source() );

	endInsertRows();

	return true;
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
				d->m_data[ row ].setType( valueTypeFromString(
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
	Q_UNUSED( index )

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

} /* namespace Globe */

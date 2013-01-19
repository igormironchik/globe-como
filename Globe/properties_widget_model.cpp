
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
#include <Globe/properties_widget_model.hpp>
#include <Globe/condition.hpp>

// Qt include.
#include <QtCore/QList>


namespace Globe {

//
// ConditionType
//

//! Condition type.
enum ConditionType {
	//! Unknown condition type.
	UnknownCondition,
	//! "If" condition.
	IfCondition,
	//! Otherwise condition.
	OtherwiseCondition
}; // enum ConditionType

//
// PropertiesListModelData
//

class PropertiesListModelData {
public:
	PropertiesListModelData( ConditionType type, Expression expr, const QVariant & value,
		Level l, const QString & message )
		:	m_type( type )
		,	m_expression( expr )
		,	m_value( value )
		,	m_level( l )
		,	m_message( message )
	{
	}

	PropertiesListModelData()
		:	m_type( UnknownCondition )
		,	m_expression( IfEqual )
		,	m_level( None )
	{
	}

	PropertiesListModelData & operator = ( const PropertiesListModelData & other )
	{
		if( this != &other )
		{
			m_type = other.m_type;
			m_expression = other.m_expression;
			m_value = other.m_value;
			m_level = other.m_level;
			m_message = other.m_message;
		}

		return *this;
	}

	//! Condition type.
	ConditionType m_type;
	//! Expression type.
	Expression m_expression;
	//! Value.
	QVariant m_value;
	//! Level.
	Level m_level;
	//! Message.
	QString m_message;
}; // class PropertiesListModelData


static inline bool checkIntValue( const QVariant & value )
{
	bool ok = false;

	value.toInt( &ok );

	return ok;
}

static inline bool checkDoubleValue( const QVariant & value )
{
	bool ok = false;

	value.toDouble( &ok );

	return ok;
}

static inline bool checkStringValue( const QVariant & value )
{
	Q_UNUSED( value )

	return true;
}


//
// PropertiesListModelPrivate
//

class PropertiesListModelPrivate {
public:
	explicit PropertiesListModelPrivate( Como::Source::Type valueType )
		:	m_valueType( valueType )
		,	m_otherwiseConditionExists( false )
	{
	}

	//! Is properties OK?
	bool isPropertiesOk() const
	{
		foreach( const PropertiesListModelData & data, m_data )
		{
			if( data.m_type == IfCondition )
			{
				if( m_valueType == Como::Source::Int )
				{
					if( !checkIntValue( data.m_value ) )
						return false;
				}
				else if( m_valueType == Como::Source::Double )
				{
					if( !checkDoubleValue( data.m_value ) )
						return false;
				}
				else
				{
					if( !checkStringValue( data.m_value ) )
						return false;
				}
			}
		}

		return true;
	}

	//! PropertiesListModelData.
	QList< PropertiesListModelData > m_data;
	//! Type of the value.
	Como::Source::Type m_valueType;
	//! Is otherwise condition exists.
	bool m_otherwiseConditionExists;
}; // class PropertiesPropertiesListModelPrivate


//
// PropertiesListModel
//

static const int conditionTypeColumn = 0;
static const int expressionColumn = 1;
static const int valueColumn = 2;
static const int levelColumn = 3;
static const int messageColumn = 4;

PropertiesListModel::PropertiesListModel( Como::Source::Type valueType,
	QObject * parent )
	:	QAbstractTableModel( parent )
	,	d( new PropertiesListModelPrivate( valueType ) )
{
}

PropertiesListModel::~PropertiesListModel()
{
}

Properties
PropertiesListModel::properties() const
{
	Properties p;

	const int conditionsCount = d->m_data.size();

	for( int i = 0; i < conditionsCount; ++i )
	{
		const PropertiesListModelData & PropertiesListModelData = d->m_data.at( i );

		if( PropertiesListModelData.m_type == IfCondition )
		{
			Condition c;

			c.setType( PropertiesListModelData.m_expression );
			c.setValue( PropertiesListModelData.m_value );
			c.setLevel( PropertiesListModelData.m_level );
			c.setMessage( PropertiesListModelData.m_message );

			p.insertCondition( c, i );
		}
		else
		{
			Condition c;

			c.setLevel( PropertiesListModelData.m_level );
			c.setMessage( PropertiesListModelData.m_message );

			p.otherwise() = c;
		}
	}

	return p;
}

void
PropertiesListModel::setProperties( const Properties & props )
{
	clear();

	const int conditionsCount = props.conditionsAmount();

	const int rowsCount = conditionsCount +
		( props.otherwise().isValid() ? 1 : 0 );

	insertRows( 0, rowsCount, QModelIndex() );

	for( int i = 0; i < conditionsCount; ++i )
	{
		const Condition & c = props.conditionAt( i );

		d->m_data[ i ] = PropertiesListModelData( IfCondition, c.type(),
			 c.value(), c.level(), c.message() );
	}

	if( props.otherwise().isValid() )
	{
		const Condition & c = props.otherwise();

		d->m_data[ rowsCount - 1 ] = PropertiesListModelData( OtherwiseCondition, c.type(),
			c.value(), c.level(), c.message() );

		d->m_otherwiseConditionExists = true;
	}

	emit dataChanged( QAbstractTableModel::index( 0, conditionTypeColumn ),
		QAbstractTableModel::index( rowsCount - 1, messageColumn ) );

	emit changed();
}

void
PropertiesListModel::clear()
{
	beginResetModel();
	d->m_data.clear();
	endResetModel();

	emit changed();
}

bool
PropertiesListModel::isOtherwiseConditionExists() const
{
	return d->m_otherwiseConditionExists;
}

void
PropertiesListModel::addCondition()
{
	const int where = rowCount() - ( isOtherwiseConditionExists() ? 1 : 0 );

	insertRow( where );

	d->m_data[ where ] = PropertiesListModelData( IfCondition, IfLess,
		 QVariant(), None, QString() );

	emit dataChanged( QAbstractTableModel::index( where, conditionTypeColumn ),
		QAbstractTableModel::index( where, messageColumn ) );

	emit wrongProperties();
}

void
PropertiesListModel::addOtherwiseCondition()
{
	if( !d->m_otherwiseConditionExists )
	{
		d->m_otherwiseConditionExists = true;

		const int where = rowCount();

		insertRow( where );

		d->m_data[ where ] = PropertiesListModelData( OtherwiseCondition, IfLess,
		 QVariant(), None, QString() );

		emit dataChanged( QAbstractTableModel::index( where, conditionTypeColumn ),
			QAbstractTableModel::index( where, messageColumn ) );

		emit changed();
	}
}

bool
PropertiesListModel::removeCondition( int row )
{
	if( row < 0 || row >= d->m_data.size() )
		return false;

	if( d->m_otherwiseConditionExists && row == d->m_data.size() - 1 )
		d->m_otherwiseConditionExists = false;

	removeRow( row );

	return true;
}

bool
PropertiesListModel::moveConditionUp( int row )
{
	if( row < 0 || row >= d->m_data.size() )
		return false;

	if( d->m_otherwiseConditionExists && row == d->m_data.size() - 1 )
		return false;

	if( row == 0 )
		return false;

	d->m_data.swap( row, row - 1 );

	emit dataChanged( QAbstractTableModel::index( row - 1, conditionTypeColumn ),
		QAbstractTableModel::index( row, messageColumn ) );

	emit changed();

	return true;
}

bool
PropertiesListModel::moveConditionDown( int row )
{
	if( row < 0 || row >= d->m_data.size() )
		return false;

	if( d->m_otherwiseConditionExists )
	{
		if( row == d->m_data.size() - 1 || row == d->m_data.size() - 2 )
			return false;
	}
	else if( row == d->m_data.size() - 1 )
		return false;

	d->m_data.swap( row, row + 1 );

	emit dataChanged( QAbstractTableModel::index( row, conditionTypeColumn ),
		QAbstractTableModel::index( row + 1, messageColumn ) );

	emit changed();

	return true;
}

int
PropertiesListModel::rowCount( const QModelIndex & parent ) const
{
	if( !parent.isValid() )
		return d->m_data.size();
	else
		return 0;
}

int
PropertiesListModel::columnCount( const QModelIndex & parent ) const
{
	Q_UNUSED( parent )

	return 5;
}

static const QString ifConditionString = QLatin1String( "if" );
static const QString otherwiseConditionString = QLatin1String( "otherwise" );
static const QString unknownConditionString = QLatin1String( "unknown" );

static inline QString conditionTypeToString( ConditionType type )
{
	switch( type )
	{
		case IfCondition : return ifConditionString;
		case OtherwiseCondition : return otherwiseConditionString;
		default : return unknownConditionString;
	}
}

static const QString ifLessOrEqualString = QLatin1String( "<=" );
static const QString ifLessString = QLatin1String( "<" );
static const QString ifEqualString = QLatin1String( "==" );
static const QString ifGreaterString = QLatin1String( ">" );
static const QString ifGreaterOrEqualString = QLatin1String( ">=" );

static inline QString expressionToString( Expression expr )
{
	switch( expr )
	{
		case IfLessOrEqual : return ifLessOrEqualString;
		case IfLess : return ifLessString;
		case IfEqual : return ifEqualString;
		case IfGreater : return ifGreaterString;
		case IfGreaterOrEqual : return ifGreaterOrEqualString;
		default : return QString();
	}
}

static const QString noneLevelString = QLatin1String( "none" );
static const QString criticalLevelString = QLatin1String( "critical" );
static const QString errorLevelString = QLatin1String( "error" );
static const QString warningLevelString = QLatin1String( "warning" );
static const QString debugLevelString = QLatin1String( "debug" );
static const QString infoLevelString = QLatin1String( "info" );

static inline QString levelToString( Level l )
{
	switch( l )
	{
		case None : return noneLevelString;
		case Critical : return criticalLevelString;
		case Error : return errorLevelString;
		case Warning : return warningLevelString;
		case Debug : return debugLevelString;
		case Info : return infoLevelString;
		default : return QString();
	}
}

QVariant
PropertiesListModel::data( const QModelIndex & index, int role ) const
{
	if( index.isValid() && ( role == Qt::DisplayRole || role == Qt::EditRole ) )
	{
		const int column = index.column();
		const int row = index.row();

		switch( column )
		{
			case conditionTypeColumn :
				return conditionTypeToString( d->m_data[ row ].m_type );
			case expressionColumn :
			{
				if( d->m_otherwiseConditionExists )
				{
					if( row == d->m_data.size() - 1 )
						return QVariant();
					else
						return expressionToString( d->m_data[ row ].m_expression );
				}
				else
					return expressionToString( d->m_data[ row ].m_expression );
			}
			case valueColumn :
				return d->m_data[ row ].m_value;
			case levelColumn :
				return levelToString( d->m_data[ row ].m_level );
			case messageColumn :
				return d->m_data[ row ].m_message;
			default :
				return QVariant();
		}
	}
	else
		return QVariant();
}

bool
PropertiesListModel::insertRows( int row, int count, const QModelIndex & parent )
{
	Q_UNUSED( parent );

	beginInsertRows( QModelIndex(), row, row + count - 1 );

	for( int i = 0; i < count; ++i )
		d->m_data.insert( row + i, PropertiesListModelData() );

	endInsertRows();

	return true;
}

bool
PropertiesListModel::removeRows( int row, int count, const QModelIndex & parent )
{
	Q_UNUSED( parent );

	beginRemoveRows( QModelIndex(), row, row + count - 1 );

	for( int i = 0; i < count; ++i )
		d->m_data.removeAt( row );

	endRemoveRows();

	return true;
}

static inline ConditionType conditionTypeFromString( const QString & str )
{
	if( str == ifConditionString )
		return IfCondition;
	else if( str == otherwiseConditionString )
		return OtherwiseCondition;
	else
		return UnknownCondition;
}

static inline Expression expressionFromString( const QString & str )
{
	if( str == ifLessOrEqualString )
		return IfLessOrEqual;
	else if( str == ifLessString )
		return IfLess;
	else if( str == ifEqualString )
		return IfEqual;
	else if( str == ifGreaterString )
		return IfGreater;
	else if( str == ifGreaterOrEqualString )
		return IfGreaterOrEqual;
	else
		return IfEqual;
}

static inline Level levelFromString( const QString & str )
{
	if( str == noneLevelString )
		return None;
	else if( str == criticalLevelString )
		return Critical;
	else if( str == errorLevelString )
		return Error;
	else if( str == warningLevelString )
		return Warning;
	else if( str == debugLevelString )
		return Debug;
	else if( str == infoLevelString )
		return Info;
	else
		return None;
}

bool
PropertiesListModel::setData( const QModelIndex & index, const QVariant & value, int role )
{
	if( index.isValid() && ( role == Qt::DisplayRole || role == Qt::EditRole ) )
	{
		const int column = index.column();
		const int row = index.row();

		switch( column )
		{
			case conditionTypeColumn :
				d->m_data[ row ].m_type =
					conditionTypeFromString( value.toString() );
			break;

			case expressionColumn :
				d->m_data[ row ].m_expression =
					expressionFromString( value.toString() );

			break;

			case valueColumn :
				{
					d->m_data[ row ].m_value = value;

					switch( d->m_valueType )
					{
						case Como::Source::Int :
							if( !checkIntValue( value ) )
								emit wrongProperties();

						break;

						case Como::Source::Double :
							if( !checkDoubleValue( value ) )
								emit wrongProperties();

						break;

						default :
							if( !checkStringValue( value ) )
								emit wrongProperties();
					}
				}

			break;

			case levelColumn :
				d->m_data[ row ].m_level =
					levelFromString( value.toString() );

			break;

			case messageColumn :
				d->m_data[ row ].m_message = value.toString();

			break;
		}

		emit dataChanged( QAbstractTableModel::index( index.row(), column ),
			QAbstractTableModel::index( index.row(), column ) );

		if( d->isPropertiesOk() )
			emit changed();

		return true;
	}

	return false;
}

Qt::ItemFlags
PropertiesListModel::flags( const QModelIndex & index ) const
{
	if( index.isValid() )
	{
		const int column = index.column();

		switch( column )
		{
			case conditionTypeColumn :
				return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
			case expressionColumn :
				if( d->m_otherwiseConditionExists )
				{
					if( index.row() == d->m_data.size() - 1 )
						return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
					else
						return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled |
							Qt::ItemIsEditable );
				}
				else
					return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled |
						Qt::ItemIsEditable );

			case valueColumn :
				if( d->m_otherwiseConditionExists )
				{
					if( index.row() == d->m_data.size() - 1 )
						return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
					else
						return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled |
							Qt::ItemIsEditable );
				}
				else
					return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled |
						Qt::ItemIsEditable );

			case levelColumn :
			case messageColumn :
				return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled |
					Qt::ItemIsEditable );

			default :
				return Qt::NoItemFlags;
		}
	}
	else
		return Qt::NoItemFlags;
}

QVariant
PropertiesListModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
	if( role != Qt::DisplayRole )
		return QVariant();

	if( orientation == Qt::Horizontal )
	{
		switch ( section )
		{
			case conditionTypeColumn : return tr( "Type" );
			case expressionColumn : return tr( "Expression" );
			case valueColumn : return tr( "Value" );
			case levelColumn : return tr( "Level" );
			case messageColumn : return tr( "Message" );
			default : return QVariant();
		}
	}

	return QVariant();
}

} /* namespace Globe */

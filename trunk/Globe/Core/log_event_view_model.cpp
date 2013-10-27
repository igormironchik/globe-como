
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
#include <Globe/Core/log_event_view_model.hpp>

// Qt include.
#include <QList>


namespace Globe {

//
// LogEventRecord
//

LogEventRecord::LogEventRecord()
	:	m_level( LogLevelError )
{
}

LogEventRecord::LogEventRecord( LogLevel level,
	const QString & dt,
	const QString & msg )
	:	m_level( level )
	,	m_dateTime( dt )
	,	m_message( msg )
{
}

LogEventRecord::LogEventRecord( const LogEventRecord & other )
	:	m_level( other.level() )
	,	m_dateTime( other.dateTime() )
	,	m_message( other.message() )
{
}

LogEventRecord &
LogEventRecord::operator = ( const LogEventRecord & other )
{
	if( this != &other )
	{
		m_level = other.level();
		m_dateTime = other.dateTime();
		m_message = other.message();
	}

	return *this;
}

LogLevel
LogEventRecord::level() const
{
	return m_level;
}

void
LogEventRecord::setLevel( LogLevel l )
{
	m_level = l;
}

const QString &
LogEventRecord::dateTime() const
{
	return m_dateTime;
}

void
LogEventRecord::setDateTime( const QString & dt )
{
	m_dateTime = dt;
}

const QString &
LogEventRecord::message() const
{
	return m_message;
}

void
LogEventRecord::setMessage( const QString & msg )
{
	m_message = msg;
}


//
// LogEventViewModelPrivate
//

class LogEventViewModelPrivate {
public:
	LogEventViewModelPrivate()
	{
	}

	//! Data.
	QList< LogEventRecord > m_data;
}; // class LogEventViewModelPrivate


//
// LogEventViewModel
//

LogEventViewModel::LogEventViewModel( QObject * parent )
	:	QAbstractTableModel( parent )
	,	d( new LogEventViewModelPrivate )
{
}

LogEventViewModel::~LogEventViewModel()
{
}

const LogEventRecord &
LogEventViewModel::record( const QModelIndex & index ) const
{
	return d->m_data.at( index.row() );
}

void
LogEventViewModel::initModel( const QList< LogEventRecord > & data )
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
LogEventViewModel::clear()
{
	beginResetModel();

	d->m_data.clear();

	endResetModel();
}

int
LogEventViewModel::rowCount( const QModelIndex & parent ) const
{
	if( !parent.isValid() )
		return d->m_data.size();
	else
		return 0;
}

int
LogEventViewModel::columnCount( const QModelIndex & parent ) const
{
	Q_UNUSED( parent )

	return 2;
}

static const int dateTimeColumn = 0;
static const int messageColumn = 1;

QVariant
LogEventViewModel::data( const QModelIndex & index, int role ) const
{
	const int column = index.column();

	if( role == Qt::DisplayRole )
	{
		switch( column )
		{
			case dateTimeColumn :
				return d->m_data[ index.row() ].dateTime();
			case messageColumn :
				return d->m_data[ index.row() ].message();
			default :
				return QVariant();
		}
	}
	else
		return QVariant();
}

bool
LogEventViewModel::setData( const QModelIndex & index, const QVariant & value,
	int role )
{
	const int column = index.column();
	const int row = index.row();

	if( role == Qt::DisplayRole )
	{
		switch( column )
		{
			case dateTimeColumn :
				d->m_data[ row ].setDateTime( value.toString() ); break;
			case messageColumn :
				d->m_data[ row ].setMessage( value.toString() ); break;
		}
	}

	emit dataChanged( QAbstractTableModel::index( row, column ),
		QAbstractTableModel::index( row, column ) );

	return true;
}

Qt::ItemFlags
LogEventViewModel::flags( const QModelIndex & index ) const
{
	Q_UNUSED( index )

	return ( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
}

QVariant
LogEventViewModel::headerData( int section, Qt::Orientation orientation,
	int role ) const
{
	if( role != Qt::DisplayRole )
		return QVariant();

	if( orientation == Qt::Horizontal )
	{
		switch ( section )
		{
			case dateTimeColumn : return tr( "Date & Time" );
			case messageColumn : return tr( "Message" );
			default : return QVariant();
		}
	}

	return QVariant();
}

} /* namespace Globe */

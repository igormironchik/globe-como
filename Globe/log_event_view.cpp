
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
#include <Globe/log_event_view.hpp>
#include <Globe/log_event_view_model.hpp>
#include <Globe/log.hpp>

// Qt include.
#include <QPainter>
#include <QAction>
#include <QItemSelectionModel>
#include <QApplication>
#include <QClipboard>


namespace Globe {

//
// LogEventViewPrivate
//

class LogEventViewPrivate {
public:
	LogEventViewPrivate()
		:	m_model( 0 )
		,	m_copyAction( 0 )
		,	m_selectAllAction( 0 )
	{
	}

	//! Model.
	LogEventViewModel * m_model;
	//! Copy action.
	QAction * m_copyAction;
	//! Select all action.
	QAction * m_selectAllAction;
}; // class LogEventViewPrivate;


//
// LogEventView
//

LogEventView::LogEventView( QWidget * parent )
	:	QTreeView( parent )
	,	d( new LogEventViewPrivate )
{
	init();
}

LogEventView::~LogEventView()
{
}

LogEventViewModel *
LogEventView::model()
{
	return d->m_model;
}

void
LogEventView::init()
{
	setRootIsDecorated( false );
	setSortingEnabled( false );
	setSelectionMode( QAbstractItemView::ExtendedSelection );
	setSelectionBehavior( QAbstractItemView::SelectRows );
	setWordWrap( true );

	d->m_copyAction= new QAction( QIcon( ":/img/edit_copy_22x22.png" ),
		tr( "Copy" ), this );
	d->m_copyAction->setShortcut( QKeySequence( "Ctrl+C" ) );
	d->m_copyAction->setEnabled( false );

	d->m_selectAllAction = new QAction( QIcon( ":/img/edit_select_all_22x22.png" ),
		tr( "Select All" ), this );
	d->m_selectAllAction->setShortcut( QKeySequence( "Ctrl+A" ) );

	addAction( d->m_copyAction );
	addAction( d->m_selectAllAction );

	connect( d->m_copyAction, SIGNAL( triggered() ),
		this, SLOT( copyImplementation() ) );
	connect( d->m_selectAllAction, SIGNAL( triggered() ),
		this, SLOT( selectAllImplementation() ) );

	d->m_model = new LogEventViewModel( this );

	setModel( d->m_model );
}

void
LogEventView::selectionChanged( const QItemSelection & selected,
	const QItemSelection & deselected )
{
	if( !selected.isEmpty() )
		d->m_copyAction->setEnabled( true );
	else
		d->m_copyAction->setEnabled( false );

	QTreeView::selectionChanged( selected, deselected );
}

void
LogEventView::selectAllImplementation()
{
	selectAll();
}

static inline QString eventLogLevelToString( LogLevel l )
{
	switch( l )
	{
		case LogLevelInfo : return QLatin1String( "INFO" );
		case LogLevelWarning : return QLatin1String( "WARN" );
		case LogLevelError : return QLatin1String( "ERR" );
		default : return QString();
	}
}

static inline QString eventLogMessage( const QString & msg )
{
	static const QLatin1String blank( "                               " );

	QString res = msg;

	int i = 0;

	while( true )
	{
		i = res.indexOf( QLatin1String( "\n" ), i );

		if( i != -1 )
		{
			++i;
			res.insert( i, blank );
		}
		else
			break;
	}

	return res;
}

void
LogEventView::copyImplementation()
{
	const QModelIndexList indexes = selectionModel()->selectedRows();

	const int size = indexes.size();

	QClipboard * clipboard = QApplication::clipboard();

	QString text;

	for( int i = 0; i < size; ++i )
	{
		const LogEventRecord & r = d->m_model->record( indexes[ i ] );

		text.append( QLatin1String( "[" ) );
		text.append( eventLogLevelToString( r.level() ) );
		text.append( QLatin1String( "] " ) );
		text.append( r.dateTime() );
		text.append( QLatin1String( " " ) );
		text.append( eventLogMessage( r.message() ) );
		text.append( QLatin1String( "\n" ) );
	}

	clipboard->setText( text );

	clearSelection();
}

void
LogEventView::drawRow( QPainter * painter, const QStyleOptionViewItem & option,
	const QModelIndex & index ) const
{
	const LogLevel level = d->m_model->record( index ).level();

	if( level == LogLevelWarning )
		painter->fillRect( option.rect, Qt::yellow );
	else if( level == LogLevelError )
		painter->fillRect( option.rect, Qt::red );

	QTreeView::drawRow( painter, option, index );
}

} /* namespace Globe */


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/log_event_view.hpp>
#include <Core/log_event_view_model.hpp>
#include <Core/log.hpp>
#include <Core/word_wrap_delegate.hpp>

// Qt include.
#include <QPainter>
#include <QAction>
#include <QItemSelectionModel>
#include <QApplication>
#include <QClipboard>
#include <QContextMenuEvent>
#include <QMenu>
#include <QHeaderView>


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
		,	m_delegate( nullptr )
	{
	}

	//! Model.
	LogEventViewModel * m_model;
	//! Copy action.
	QAction * m_copyAction;
	//! Select all action.
	QAction * m_selectAllAction;
	//! Delegate.
	WordWrapItemDelegate * m_delegate;
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

	d->m_delegate = new WordWrapItemDelegate( this );
	setItemDelegate( d->m_delegate );

	d->m_copyAction= new QAction( QIcon( ":/img/edit_copy_22x22.png" ),
		tr( "Copy" ), this );
	d->m_copyAction->setShortcut( QKeySequence( "Ctrl+C" ) );
	d->m_copyAction->setEnabled( false );

	d->m_selectAllAction = new QAction( QIcon( ":/img/edit_select_all_22x22.png" ),
		tr( "Select All" ), this );
	d->m_selectAllAction->setShortcut( QKeySequence( "Ctrl+A" ) );

	addAction( d->m_copyAction );
	addAction( d->m_selectAllAction );

	connect( d->m_copyAction, &QAction::triggered,
		this, &LogEventView::copyImplementation );
	connect( d->m_selectAllAction, &QAction::triggered,
		this, &LogEventView::selectAllImplementation );
	connect( header(), &QHeaderView::sectionResized,
		this, &LogEventView::sectionResized );

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

void
LogEventView::contextMenuEvent( QContextMenuEvent * event )
{
	QMenu menu( this );

	const QModelIndexList indexes = selectionModel()->selectedRows();

	if( !indexes.isEmpty() )
		menu.addAction( d->m_copyAction );

	menu.addAction( d->m_selectAllAction );

	menu.exec( event->globalPos() );

	event->accept();
}

void
LogEventView::sectionResized( int section, int, int )
{
	for( int i = 0; i < d->m_model->rowCount(); ++i )
		emit d->m_delegate->sizeHintChanged( d->m_model->index( i, section ) );
}

} /* namespace Globe */

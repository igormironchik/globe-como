
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Globe include.
#include <Globe/Core/channel_timeout_widget.hpp>

// Qt include.
#include <QPainter>
#include <QMouseEvent>
#include <QToolTip>


namespace Globe {

const int columnWidth = 5;
const int columnOffset = 1;
const int columnHeight = 2;
const int columnsCount = 6;
const int widgetWidth = columnWidth * columnsCount +
	columnOffset * ( columnsCount - 1 );
const int widgetHeight = columnsCount * columnHeight;

const int timeout1 = 5000;
const int timeout2 = 3000;
const int timeout3 = 2000;
const int timeout4 = 1000;
const int timeout5 = 500;
const int timeout6 = 0;

//
// ChannelTimeoutWidgetPrivate
//

class ChannelTimeoutWidgetPrivate {
public:
	explicit ChannelTimeoutWidgetPrivate( int timeout )
		:	m_timeout( timeout )
		,	m_mousePressed( false )
		,	m_timeoutChanged( false )
	{
	}

	//! \return Columns count with green color.
	int greenColumns() const
	{
		if( m_timeout >= timeout1 )
			return 1;
		else if( m_timeout >= timeout2 )
			return 2;
		else if( m_timeout >= timeout3 )
			return 3;
		else if( m_timeout >= timeout4 )
			return 4;
		else if( m_timeout >= timeout5 )
			return 5;
		else
			return 6;
	}

	//! \return Column index for the given position.
	int column( int x ) const
	{
		static const int columnAreaWidth = columnWidth + columnOffset;

		return ( x / columnAreaWidth );
	}

	//! Set timeout for the given column.
	int timeoutForColumn( int column ) const
	{
		switch( column )
		{
			case 0 : return timeout1;
			case 1 : return timeout2;
			case 2 : return timeout3;
			case 3 : return timeout4;
			case 4 : return timeout5;
			case 5 : return timeout6;
			default : return timeout6;
		}
	}

	//! Timeout.
	int m_timeout;
	//! Mouse was pressed.
	bool m_mousePressed;
	//! Timeout was changed.
	bool m_timeoutChanged;
}; // class ChannelTimeoutWidgetPrivate


//
// ChannelTimeoutWidget
//

ChannelTimeoutWidget::ChannelTimeoutWidget( int timeout,
	QWidget * parent, Qt::WindowFlags f )
	:	QWidget( parent, f )
	,	d( new ChannelTimeoutWidgetPrivate( timeout ) )
{
	setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
}

ChannelTimeoutWidget::~ChannelTimeoutWidget()
{
}

QSize
ChannelTimeoutWidget::sizeHint() const
{
	return minimumSizeHint();
}

QSize
ChannelTimeoutWidget::minimumSizeHint() const
{
	return QSize( widgetWidth, widgetHeight );
}

void
ChannelTimeoutWidget::paintEvent( QPaintEvent * event )
{
	Q_UNUSED( event )

	QPainter painter( this );

	painter.setPen( Qt::NoPen );
	painter.setBrush( Qt::darkGreen );

	painter.setWindow( 0, 0, widgetWidth, widgetHeight );

	for( int i = 0; i < columnsCount; ++i )
	{
		const int x = i * columnWidth + i * columnOffset;

		painter.drawRect( x, widgetHeight - ( i + 1 ) * columnHeight,
			columnWidth, columnHeight * ( i + 1 ) );

		if( d->greenColumns() == i + 1 )
			painter.setBrush( Qt::darkRed );
	}
}

void
ChannelTimeoutWidget::mouseMoveEvent( QMouseEvent * event )
{
	if( d->m_mousePressed )
	{
		const int column = d->column( event->x() );
		const int timeout = d->timeoutForColumn( column );
		if( d->m_timeout != timeout )
		{
			d->m_timeoutChanged = true;
			d->m_timeout = timeout;
			update();

			const QPoint point = mapToGlobal( QPoint( 0, 0 ) );

			QToolTip::showText( point, prepareToolTip(), this, rect() );
		}
	}
}

void
ChannelTimeoutWidget::mousePressEvent( QMouseEvent * event )
{
	d->m_mousePressed = true;
	const int column = d->column( event->x() );
	const int timeout = d->timeoutForColumn( column );

	if( d->m_timeout != timeout )
	{
		d->m_timeout = timeout;
		update();

		emit timeoutChanged( d->m_timeout );
	}
}

void
ChannelTimeoutWidget::mouseReleaseEvent( QMouseEvent * event )
{
	Q_UNUSED( event )

	if( d->m_timeoutChanged )
		emit timeoutChanged( d->m_timeout );

	d->m_timeoutChanged = false;
	d->m_mousePressed = false;
}

bool
ChannelTimeoutWidget::event( QEvent * event )
{
	if( event->type() == QEvent::ToolTip )
	{
		toolTipEvent( event );

		return true;
	}
	else
		return QWidget::event( event );
}

void
ChannelTimeoutWidget::toolTipEvent( QEvent * event )
{
	const QPoint point = mapToGlobal( QPoint( 0, 0 ) );

	QToolTip::showText( point, prepareToolTip(), this, rect() );

	event->accept();
}

QString
ChannelTimeoutWidget::prepareToolTip() const
{
	if( d->m_timeout == 0 )
		return tr( "Without timeout." );
	else
	{
		QString result;

		result.append( tr( "Timeout in channel is " ) );
		result.append( QString::number( (double) d->m_timeout / 1000.0 ) );
		result.append( tr( " seconds." ) );

		return result;
	}
}

} /* namespace Globe */

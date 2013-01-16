
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
#include <Globe/properties_widget.hpp>
#include <Globe/condition_widget.hpp>
#include <Globe/otherwise_condition_widget.hpp>
#include <Globe/color_frame_widget.hpp>

// Qt include.
#include <QtGui/QContextMenuEvent>
#include <QtGui/QMouseEvent>
#include <QtCore/QList>
#include <QtGui/QAction>
#include <QtGui/QMenu>

#include <QtCore/QDebug>


namespace Globe {

//
// PropertiesListPrivate
//

class PropertiesListPrivate {
public:
	PropertiesListPrivate( QWidget * parent, Como::Source::Type valueType )
		:	m_parent( parent )
		,	m_valueType( valueType )
		,	m_otherwiseCondition( 0 )
		,	m_currentFrameIndex( -1 )
		,	m_contextMenuRequestedIndex( -1 )
	{
	}

	//! Resize and place widgets.
	void resizeAndPlace( const QSize size = QSize() )
	{
		if( m_frames.isEmpty() )
		{
			m_parent->resize( QSize() );
			return;
		}

		const int width = qMax( size.width(),
			m_frames.at( 0 )->minimumSizeHint().width() );

		const int framesCount = m_frames.size();

		int height = 0;

		for( int i = 0; i < framesCount; ++i )
		{
			ColorFrameWidget *  frame = m_frames.at( i );

			frame->move( 0, height );

			const int frameHeight = frame->minimumSizeHint().height();

			frame->resize( width, frameHeight );
			height += frameHeight;
		}

		m_size = QSize( width, height );

		m_parent->resize( m_size );
	}

	//! \return Index of the frame under cursor \arg pos position.
	int indexUnderCursor( const QPoint & pos )
	{
		int index = 0;

		foreach( ColorFrameWidget * w, m_frames )
		{
			if( w->geometry().contains( pos ) )
				return index;

			++index;
		}

		if( m_otherwiseCondition &&
			m_otherwiseCondition->geometry().contains( pos ) )
				return index;

		return -1;
	}

	//! Operation mode.
	enum OperationMode {
		//! Operation for the current item.
		OperationForCurrentItem,
		//! Operation for item under cursor.
		OperationForItemUnderCursor
	}; // enum OperationMode

	//! Delete condition.
	void deleteCondition( int index, OperationMode opMode )
	{
		if( index == -1 )
			return;

		if( m_otherwiseCondition )
		{
			if( index == m_frames.size() - 1 )
			{
				m_frames.at( index )->deleteLater();
				m_frames.removeAt( index );
				m_otherwiseCondition = 0;

				if( opMode == OperationForCurrentItem )
					m_currentFrameIndex = -1;
				else if( opMode == OperationForItemUnderCursor )
					m_contextMenuRequestedIndex = -1;

				resizeAndPlace( m_size );

				return;
			}
		}

		m_frames.at( index )->deleteLater();
		m_frames.removeAt( index );
		m_conditions.removeAt( index );

		if( opMode == OperationForCurrentItem )
		{
			m_currentFrameIndex = -1;

			if( m_contextMenuRequestedIndex == index )
				m_contextMenuRequestedIndex = -1;
		}
		else if( opMode == OperationForItemUnderCursor )
		{
			m_contextMenuRequestedIndex = -1;

			if( m_currentFrameIndex == index )
				m_currentFrameIndex = -1;
		}

		resizeAndPlace( m_size );
	}

	//! Move condition up.
	void moveConditionUp( int index, OperationMode opMode )
	{
		if( index == 0 || index == -1 ||
			( m_otherwiseCondition && index == m_frames.size() - 1 ) )
				return;

		m_frames.swap( index, index - 1 );
		m_conditions.swap( index, index - 1 );

		resizeAndPlace( m_size );

		if( opMode == OperationForCurrentItem )
		{
			--m_currentFrameIndex;

			if( m_contextMenuRequestedIndex == index )
				--m_contextMenuRequestedIndex;
		}
		else if( opMode == OperationForItemUnderCursor )
		{
			--m_contextMenuRequestedIndex;

			if( m_currentFrameIndex == index )
				--m_currentFrameIndex;
		}
	}

	//! Move condition down.
	void moveConditionDown( int index, OperationMode opMode )
	{
		if( m_otherwiseCondition )
		{
			const int framesCount = m_frames.size();

			if( index == framesCount - 2 || index == framesCount - 1 || index == -1 )
				return;
		}
		else if( index == m_frames.size() - 1 || index == -1 )
			return;

		m_frames.swap( index, index + 1 );
		m_conditions.swap( index, index + 1 );

		resizeAndPlace( m_size );

		if( opMode == OperationForCurrentItem )
		{
			++m_currentFrameIndex;

			if( m_contextMenuRequestedIndex == index )
				++m_contextMenuRequestedIndex;
		}
		else if( opMode == OperationForItemUnderCursor )
		{
			++m_contextMenuRequestedIndex;

			if( m_currentFrameIndex == index )
				++m_currentFrameIndex;
		}
	}

	//! Parent.
	QWidget * m_parent;
	//! Value type.
	Como::Source::Type m_valueType;
	//! Frames.
	QList< ColorFrameWidget* > m_frames;
	//! Conditions.
	QList< ConditionWidget* > m_conditions;
	//! Otherwise condition.
	OtherwiseConditionWidget * m_otherwiseCondition;
	//! Current frame index.
	int m_currentFrameIndex;
	//! Size.
	QSize m_size;
	//! "Context menu requested" index.
	int m_contextMenuRequestedIndex;
}; // class PropertiesListPrivate


//
// PropertiesList
//

PropertiesList::PropertiesList( Como::Source::Type valueType,
	QWidget * parent, Qt::WindowFlags f )
	:	ScrolledWidget( parent, f )
	,	d( new PropertiesListPrivate( this, valueType ) )
{
}

PropertiesList::~PropertiesList()
{
	foreach( ColorFrameWidget * w, d->m_frames )
		w->deleteLater();
}

Properties
PropertiesList::properties() const
{
	Properties p;

	int i = 0;

	foreach( ConditionWidget * w, d->m_conditions )
	{
		p.insertCondition( w->condition(), i );

		++i;
	}

	if( d->m_otherwiseCondition != 0 )
		p.otherwise() = d->m_otherwiseCondition->condition();

	return p;
}

void
PropertiesList::setProperties( const Properties & p )
{
	d->m_otherwiseCondition = 0;
	d->m_conditions.clear();

	foreach( ColorFrameWidget * w, d->m_frames )
		w->deleteLater();

	const int conditionsCount = p.conditionsAmount();

	for( int i = 0; i < conditionsCount; ++i )
	{
		ColorFrameWidget * frame = new ColorFrameWidget( this );
		ConditionWidget * widget = new ConditionWidget( d->m_valueType, this );
		frame->setWidget( widget );
		frame->show();

		connect( widget, SIGNAL( wrongCondition() ),
			this, SLOT( wrongCondition() ) );
		connect( widget, SIGNAL( changed() ),
			this, SLOT( conditionChanged() ) );

		d->m_frames.append( frame );
		d->m_conditions.append( widget );

		widget->setCondition( p.conditionAt( i ) );
	}

	if( p.otherwise().isValid() )
	{
		ColorFrameWidget * frame = new ColorFrameWidget( this );
		d->m_otherwiseCondition = new OtherwiseConditionWidget( this );
		frame->setWidget( d->m_otherwiseCondition );
		frame->show();

		connect( d->m_otherwiseCondition, SIGNAL( changed() ),
			this, SLOT( otherwiseConditionChanged() ) );

		d->m_frames.append( frame );

		d->m_otherwiseCondition->setCondition( p.otherwise() );
	}

	d->resizeAndPlace();
}

int
PropertiesList::currentFrameIndex() const
{
	return d->m_currentFrameIndex;
}

int
PropertiesList::framesCount() const
{
	return d->m_frames.count();
}

bool
PropertiesList::isOtherwiseConditionExists() const
{
	return ( d->m_otherwiseCondition != 0 );
}

bool
PropertiesList::isPropertiesOk() const
{
	foreach( ConditionWidget * w, d->m_conditions )
		if( !w->isConditionOk() )
			return false;

	return true;
}

void
PropertiesList::moveCurrentUp()
{
	d->moveConditionUp( currentFrameIndex(),
		PropertiesListPrivate::OperationForCurrentItem );
}

void
PropertiesList::moveCurrentDown()
{
	d->moveConditionDown( currentFrameIndex(),
		PropertiesListPrivate::OperationForCurrentItem );
}

void
PropertiesList::deleteCurrent()
{
	d->deleteCondition( currentFrameIndex(),
		PropertiesListPrivate::OperationForCurrentItem );
}

void
PropertiesList::addCondition()
{
	int index = d->m_frames.size();

	if( d->m_otherwiseCondition )
		--index;

	ColorFrameWidget * frame = new ColorFrameWidget( this );
	ConditionWidget * widget = new ConditionWidget( d->m_valueType, this );
	frame->setWidget( widget );
	frame->show();

	connect( widget, SIGNAL( wrongCondition() ),
		this, SLOT( wrongCondition() ) );
	connect( widget, SIGNAL( changed() ),
		this, SLOT( conditionChanged() ) );

	d->m_frames.insert( index, frame );
	d->m_conditions.append( widget );

	d->resizeAndPlace( d->m_size );

	if( isPropertiesOk() )
		emit changed();
	else
		emit wrongProperties();
}

void
PropertiesList::addOtherwiseCondition()
{
	if( d->m_otherwiseCondition )
		return;

	ColorFrameWidget * frame = new ColorFrameWidget( this );
	d->m_otherwiseCondition = new OtherwiseConditionWidget( this );
	frame->setWidget( d->m_otherwiseCondition );
	frame->show();

	connect( d->m_otherwiseCondition, SIGNAL( changed() ),
		this, SLOT( otherwiseConditionChanged() ) );

	d->m_frames.append( frame );

	if( isPropertiesOk() )
		emit changed();
}

void
PropertiesList::wrongCondition()
{
	ConditionWidget * widget = qobject_cast< ConditionWidget* > ( sender() );

	const int index = d->m_conditions.indexOf( widget );

	if( index != -1 )
	{
		d->m_frames.at( index )->highlightAsWrong();

		emit wrongProperties();
	}
}

void
PropertiesList::conditionChanged()
{
	ConditionWidget * widget = qobject_cast< ConditionWidget* > ( sender() );

	const int index = d->m_conditions.indexOf( widget );

	if( index != -1 )
	{
		d->m_frames.at( index )->highlightAsNormal();

		if( isPropertiesOk() )
			emit changed();
	}
}

void
PropertiesList::otherwiseConditionChanged()
{
	if( isPropertiesOk() )
		emit changed();
}

void
PropertiesList::moveUnderCursorUp()
{
	d->moveConditionUp( d->m_contextMenuRequestedIndex,
		PropertiesListPrivate::OperationForItemUnderCursor );
}

void
PropertiesList::moveUnderCursorDown()
{
	d->moveConditionDown( d->m_contextMenuRequestedIndex,
		PropertiesListPrivate::OperationForItemUnderCursor );
}

void
PropertiesList::deleteUnderCursor()
{
	d->deleteCondition( d->m_contextMenuRequestedIndex,
		PropertiesListPrivate::OperationForItemUnderCursor );
}

void
PropertiesList::mousePressEvent( QMouseEvent * event )
{
	qDebug() << "mousePressEvent";

	const int currentIndex = d->indexUnderCursor( event->pos() );

	qDebug() << "currentIndex" << currentIndex;

	if( event->button() == Qt::LeftButton )
	{
		if( d->m_currentFrameIndex != -1 )
			d->m_frames.at( d->m_currentFrameIndex )->removeCurrentHighlightMode();

		if( currentIndex != -1 )
			d->m_frames.at( currentIndex )->highlightAsCurrent();

		d->m_currentFrameIndex = currentIndex;

		event->accept();

		return;
	}
	else if( event->button() == Qt::RightButton )
	{
		d->m_contextMenuRequestedIndex = currentIndex;

		if( currentIndex != -1 )
			d->m_frames.at( d->m_contextMenuRequestedIndex )->
				highlightAsContextMenuRequested();

		event->accept();

		return;
	}

	event->ignore();
}

void
PropertiesList::mouseMoveEvent( QMouseEvent * event )
{
	if( d->m_contextMenuRequestedIndex != -1 )
	{
		const int currentIndex = d->indexUnderCursor( event->pos() );

		if( d->m_contextMenuRequestedIndex != currentIndex )
		{
			d->m_frames.at( d->m_contextMenuRequestedIndex )->
				removeContextMenuRequestedHighlight();

			d->m_contextMenuRequestedIndex = currentIndex;

			d->m_frames.at( d->m_contextMenuRequestedIndex )->
				highlightAsContextMenuRequested();
		}

		event->accept();

		return;
	}

	event->ignore();
}

void
PropertiesList::contextMenuEvent( QContextMenuEvent * event )
{
	qDebug() << "contextMenuEvent";

	QMenu menu( this );

	const int index = d->m_contextMenuRequestedIndex;

	qDebug() << index;

	if( index > 0 )
	{
		if( d->m_otherwiseCondition )
		{
			if( index < d->m_frames.size() - 1 )
				menu.addAction( QIcon( ":/img/up_22x22.png" ), tr( "Move up" ),
					this, SLOT( moveUnderCursorUp() ) );
		}
		else
			menu.addAction( QIcon( ":/img/up_22x22.png" ), tr( "Move up" ),
					this, SLOT( moveUnderCursorUp() ) );
	}

	if( index < d->m_frames.size() - 1 && index != -1 )
	{
		if( d->m_otherwiseCondition )
		{
			if( index < d->m_frames.size() - 2 )
				menu.addAction( QIcon( ":/img/down_22x22.png" ), tr( "Move down" ),
					this, SLOT( moveUnderCursorDown() ) );
		}
		else
			if( index < d->m_frames.size() - 2 )
				menu.addAction( QIcon( ":/img/down_22x22.png" ), tr( "Move down" ),
					this, SLOT( moveUnderCursorDown() ) );
	}

	menu.addAction( QIcon( ":/img/add_22x22.png" ), tr( "Add condition" ),
		this, SLOT( addCondition() ) );

	if( !d->m_otherwiseCondition )
		menu.addAction( QIcon( ":/img/add_22x22.png" ), tr( "Add otherwise condition" ),
			this, SLOT( addOtherwiseCondition() ) );

	if( index != -1 )
		menu.addAction( QIcon( ":/img/remove_22x22.png" ), tr( "Delete condition" ),
			this, SLOT( deleteUnderCursor() ) );

	menu.exec( event->globalPos() );

	event->accept();

	if( d->m_contextMenuRequestedIndex != -1 )
		d->m_frames.at( d->m_contextMenuRequestedIndex )->
			removeContextMenuRequestedHighlight();

	d->m_contextMenuRequestedIndex = -1;
}

void
PropertiesList::resizeWidget( const QSize & size )
{
	d->resizeAndPlace( size );
}

} /* namespace Globe */

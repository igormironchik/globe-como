
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Scheme/selectable.hpp>

// Qt include.
#include <QRectF>
#include <QApplication>


namespace Globe {

namespace Scheme {

//
// SelectablePrivate
//

SelectablePrivate::SelectablePrivate( Selection * selection, Scene * scene )
	:	m_resizeMode( NoResize )
	,	m_mode( ViewScene )
	,	m_editMode( EditSceneSelect )
	,	m_selection( selection )
	,	m_scene( scene )
	,	m_state( ItemNotSelected )
	,	m_leftButtonPressed( false )
	,	m_width( 50.0 )
	,	m_height( 25.0 )
{
}

SelectablePrivate::~SelectablePrivate()
{
}


//
// Selectable
//

Selectable::~Selectable()
{
}

Selectable::Selectable( SelectablePrivate * dd )
	:	d( dd )
{
}

void
Selectable::detectResizeMode( const QPointF & pos,
	const QRectF & boundingRect )
{
	const QRectF topLeftRect( 0, 0, 3, 3 );
	const QRectF topRightRect( boundingRect.width() - 3, 0, 3, 3 );
	const QRectF bottomLeftRect( 0, boundingRect.height() - 3, 3, 3 );
	const QRectF bottomRightRect( boundingRect.width() - 3,
		boundingRect.height() - 3, 3, 3 );

	if( topLeftRect.contains( pos ) )
	{
		d->m_resizeMode = ResizeTopLeft;
		QApplication::setOverrideCursor( QCursor( Qt::SizeFDiagCursor ) );
	}
	else if( topRightRect.contains( pos ) )
	{
		d->m_resizeMode = ResizeTopRight;
		QApplication::setOverrideCursor( QCursor( Qt::SizeBDiagCursor ) );
	}
	else if( bottomLeftRect.contains( pos ) )
	{
		d->m_resizeMode = ResizeBottomLeft;
		QApplication::setOverrideCursor( QCursor( Qt::SizeBDiagCursor ) );
	}
	else if( bottomRightRect.contains( pos ) )
	{
		d->m_resizeMode = ResizeBottomRight;
		QApplication::setOverrideCursor( QCursor( Qt::SizeFDiagCursor ) );
	}
	else
	{
		d->m_resizeMode = NoResize;
		QApplication::setOverrideCursor( QCursor( Qt::ArrowCursor ) );
	}
}

} /* namespace Scheme */

} /* namespace Globe */

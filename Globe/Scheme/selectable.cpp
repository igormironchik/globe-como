
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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
#include <Globe/Scheme/selectable.hpp>

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

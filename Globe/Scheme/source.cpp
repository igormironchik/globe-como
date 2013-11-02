
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
#include <Globe/Scheme/source.hpp>

// Qt include.
#include <QPainter>


namespace Globe {

namespace Scheme {

//
// SourcePrivate
//

class SourcePrivate {
public:
	SourcePrivate( const Como::Source & source, const QString & channelName )
		:	m_source( source )
		,	m_channelName( channelName )
	{
	}

	//! Source.
	Como::Source m_source;
	//! Channel name.
	QString m_channelName;
}; // class SourcePrivate


//
// Source
//

Source::Source( const Como::Source & source, const QString & channelName )
	:	d( new SourcePrivate( source, channelName ) )
{
}

QRectF
Source::boundingRect() const
{
	return QRectF( 0, 0, 50, 25 );
}

void
Source::paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
	QWidget * widget )
{
	Q_UNUSED( option )
	Q_UNUSED( widget )

	painter->setPen( Qt::black );

	painter->setBrush( Qt::white );

	painter->drawRect( boundingRect() );

	painter->drawText( boundingRect(), Qt::AlignCenter | Qt::TextWordWrap,
		d->m_source.value().toString() );
}

} /* namespace Scheme */

} /* namespace Globe */

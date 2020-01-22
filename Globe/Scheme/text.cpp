
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2020 Igor Mironchik

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
#include <Globe/Scheme/text.hpp>
#include <Globe/Scheme/scene.hpp>
#include <Globe/Scheme/text_dialog.hpp>

// Qt include.
#include <QPainter>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QApplication>


namespace Globe {

namespace Scheme {

//
// TextPrivate
//

class TextPrivate
	:	public SelectablePrivate
{
public:
	TextPrivate( const QString & text, Selection * selection, Scene * scene )
		:	SelectablePrivate( selection, scene )
		,	m_text( text )
	{
	}

	~TextPrivate()
	{
	}

	//! Text.
	QString m_text;
}; // class TextPrivate


//
// Text
//

Text::Text( const QString & text, Selection * selection, Scene * scene )
	:	BaseItem( new TextPrivate( text, selection, scene ) )
{
}

Text::~Text()
{
}

void
Text::deleteItem()
{
	d_ptr()->m_scene->removeText( this );

	deleteLater();
}

TextCfg
Text::cfg() const
{
	TextCfg cfg;

	auto * dd = d_ptr();

	cfg.setText( dd->m_text );
	cfg.setPos( pos() );
	cfg.setSize( QSizeF( dd->m_width, dd->m_height ) );

	if( QApplication::font() != dd->m_font )
		cfg.setFont( dd->m_font );

	return cfg;
}

void
Text::setCfg( const TextCfg & cfg )
{
	auto * dd = d_ptr();

	if( cfg.isFontSet() )
		dd->m_font = cfg.font();

	setPos( cfg.pos() );

	dd->m_width = cfg.size().width();
	dd->m_height = cfg.size().height();

	update();
}

void
Text::paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
	QWidget * widget )
{
	Q_UNUSED( option )
	Q_UNUSED( widget )

	auto * dd = d_ptr();

	if( dd->m_state == ItemSelected )
	{
		painter->setPen( Qt::blue );
		painter->drawRect( boundingRect() );

		painter->setBrush( Qt::blue );
		painter->drawRect( 0, 0, 3, 3 );
		painter->drawRect( boundingRect().width() - 3, 0, 3, 3 );
		painter->drawRect( 0, boundingRect().height() - 3, 3, 3 );
		painter->drawRect( boundingRect().width() - 3,
			boundingRect().height() - 3, 3, 3 );
	}

	painter->setPen( Qt::black );

	painter->setFont( dd->m_font );

	painter->drawText( boundingRect(), Qt::AlignCenter | Qt::TextWordWrap,
		dd->m_text );
}

void
Text::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{
	auto * dd = d_ptr();

	if( dd->m_mode == EditScene && dd->m_editMode == EditSceneSelect )
	{
		event->accept();

		QMenu menu;

		menu.addAction( QIcon( ":/img/add_text_22x22.png" ),
			tr( "Change Text" ), this, SLOT( changeText() ) );
		menu.addAction( QIcon( ":/img/character_set_22x22.png" ),
			tr( "Change Font" ), this, SLOT( changeFont() ) );
		menu.addAction( QIcon( ":/img/transform_scale_22x22.png" ),
			tr( "Change Size" ), this, SLOT( changeSize() ) );
		menu.addAction( QIcon( ":/img/remove_22x22.png" ),
			tr( "Delete Text" ), this, SLOT( removeItemFromScene() ) );

		menu.exec( event->screenPos() );
	}
}

void
Text::changeText()
{
	auto * dd = d_ptr();

	QString text = dd->m_text;

	TextDialog dlg( text );

	if( dlg.exec() == QDialog::Accepted )
	{
		dd->m_text = text;
		update();
	}
}

TextPrivate *
Text::d_ptr()
{
	return static_cast< TextPrivate* > ( d.data() );
}

const TextPrivate *
Text::d_ptr() const
{
	return static_cast< const TextPrivate* > ( d.data() );
}

} /* namespace Scheme */

} /* namespace Globe */

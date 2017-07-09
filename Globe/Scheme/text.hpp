
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

#ifndef GLOBE__SCHEME__TEXT_HPP__INCLUDED
#define GLOBE__SCHEME__TEXT_HPP__INCLUDED

// Globe include.
#include <Globe/Scheme/base_item.hpp>
#include <Globe/Scheme/text_cfg.hpp>


namespace Globe {

namespace Scheme {

class Selection;
class Scene;


//
// Text
//

class TextPrivate;

//! Graphics item that will display text on scheme.
class Text
	:	public BaseItem
{
	Q_OBJECT

public:
	Text( const QString & text,
		Selection * selection, Scene * scene );
	~Text();

	//! Delete item.
	void deleteItem() Q_DECL_OVERRIDE;

	//! \return Configuration.
	TextCfg cfg() const;
	//! Set configuration.
	void setCfg( const TextCfg & cfg );

	//! Paint item.
	void paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
		QWidget * widget ) Q_DECL_OVERRIDE;

protected:
	void contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
		Q_DECL_OVERRIDE;

private slots:
	//! Change text.
	void changeText();

private:
	TextPrivate * d_ptr();
	const TextPrivate * d_ptr() const;

private:
	Q_DISABLE_COPY( Text )
}; // class Text

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__TEXT_HPP__INCLUDED

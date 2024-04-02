
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SCHEME__TEXT_HPP__INCLUDED
#define GLOBE__SCHEME__TEXT_HPP__INCLUDED

// Globe include.
#include <Scheme/base_item.hpp>
#include <Scheme/text_cfg.hpp>


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

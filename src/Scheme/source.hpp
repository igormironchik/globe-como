
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

#ifndef GLOBE__SCHEME__SOURCE_HPP__INCLUDED
#define GLOBE__SCHEME__SOURCE_HPP__INCLUDED

// Como include.
#include <Como/Source>

// Globe include.
#include <Scheme/source_cfg.hpp>
#include <Scheme/base_item.hpp>


namespace Globe {

namespace Scheme {

class Selection;
class Scene;


//
// Source
//

class SourcePrivate;

//! Graphics item that will display Como source on scheme.
class Source
	:	public BaseItem
{
	Q_OBJECT

public:
	Source( const Como::Source & source, const QString & channelName,
		Selection * selection, Scene * scene );
	~Source();

	//! Delete item.
	void deleteItem() Q_DECL_OVERRIDE;

	//! \return Channel name.
	const QString & channelName() const;

	//! \return Source.
	const Como::Source & source() const;
	//! Set source.
	void setSource( const Como::Source & source );

	//! \return Configuration.
	SourceCfg cfg() const;
	//! Set configuration.
	void setCfg( const SourceCfg & cfg );

	//! Notify about disconnecting.
	void disconnected();

	//! Notify about deregistering.
	void deregistered();

	//! Notify about changes in properties.
	void propertiesChanged();

	//! Paint item.
	void paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
		QWidget * widget ) Q_DECL_OVERRIDE;

protected:
	void contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
		Q_DECL_OVERRIDE;

private slots:
	//! Add properties.
	void addProperties();
	//! Edit properties.
	void editProperties();
	//! Delete properties.
	void deleteProperties();
	//! Promote properties.
	void promoteProperties();

private:
	SourcePrivate * d_ptr();
	const SourcePrivate * d_ptr() const;

private:
	Q_DISABLE_COPY( Source )
}; // class Source

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__SOURCE_HPP__INCLUDED

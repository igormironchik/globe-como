
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

#ifndef GLOBE__SCHEME__AGGREGATE_HPP__INCLUDED
#define GLOBE__SCHEME__AGGREGATE_HPP__INCLUDED

// Globe include.
#include <Globe/Scheme/base_item.hpp>
#include <Globe/Scheme/scheme_cfg.hpp>

// Como include.
#include <Como/Source>

// Qt include.
#include <QString>
#include <QList>
#include <QPair>


namespace Globe {

namespace Scheme {

class Selection;
class Scene;


//
// Aggregate
//

class AggregatePrivate;

//! Graphics item that will display aggregated scheme on the scheme.
class Aggregate
	:	public BaseItem
{
	Q_OBJECT

public:
	Aggregate( Selection * selection, Scene * scene );
	~Aggregate();

	//! Delete item.
	void deleteItem() Q_DECL_OVERRIDE;

	//! \return Configuration.
	SchemeCfg cfg() const;
	//! Set configuration.
	void setCfg( const SchemeCfg & cfg );

	//! \return List of channels.
	const QStringList & listOfChannels() const;

	//! \return Sources in the aggregate.
	QList< QPair< Como::Source, QString > > sources() const;

	//! Sync source.
	void syncSource( const Como::Source & source,
		const QString & channel, bool isRegistered );

	//! Paint item.
	void paint( QPainter * painter, const QStyleOptionGraphicsItem * option,
		QWidget * widget ) Q_DECL_OVERRIDE;

	//! Properties changed.
	void propertiesChanged();

	//! Channel has been disconnected.
	void channelDisconnected( const QString & name );

	//! Channel has been deregistered.
	void channelDeregistered( const QString & name );

protected:
	void contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
		Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent( QGraphicsSceneMouseEvent * event );


private slots:
	//! Show scheme.
	void showScheme();
	//! Scheme changed.
	void schemeChanged();

private:
	AggregatePrivate * d_ptr();
	const AggregatePrivate * d_ptr() const;

private:
	Q_DISABLE_COPY( Aggregate )
}; // class Text

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__AGGREGATE_HPP__INCLUDED

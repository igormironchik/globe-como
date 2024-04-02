
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SCHEME__AGGREGATE_HPP__INCLUDED
#define GLOBE__SCHEME__AGGREGATE_HPP__INCLUDED

// Globe include.
#include <Scheme/base_item.hpp>
#include <Scheme/scheme_cfg.hpp>

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
	void mouseDoubleClickEvent( QGraphicsSceneMouseEvent * event ) Q_DECL_OVERRIDE;


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

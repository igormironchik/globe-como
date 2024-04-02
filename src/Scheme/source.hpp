
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__CHANNEL_VIEW_WINDOW_CFG_HPP__INCLUDED
#define GLOBE__CHANNEL_VIEW_WINDOW_CFG_HPP__INCLUDED

// cfgfile include.
#include <cfgfile/all.hpp>

// Globe include.
#include <Core/window_state_cfg.hpp>


namespace Globe {

//
// HeaderColumnCfg
//

//! Configuration of the column in the header view.
class HeaderColumnCfg {
public:
	HeaderColumnCfg();

	HeaderColumnCfg( int size, int pos );

	HeaderColumnCfg( const HeaderColumnCfg & other );

	HeaderColumnCfg & operator = ( const HeaderColumnCfg & other );

	//! \return Size of the column.
	int size() const;
	//! Set size of the column.
	void setSize( int s );

	//! \return Position of the column.
	int pos() const;
	//! Set position of the column.
	void setPos( int p );

private:
	//! Size of the column.
	int m_size;
	//!Position of the column.
	int m_pos;
}; // class HeaderColumnCfg


//
// ViewHeaderCfg
//

//! Configuration of the header of the view.
class ViewHeaderCfg {
public:
	ViewHeaderCfg();

	ViewHeaderCfg( int sortColumn, Qt::SortOrder sortOrder,
		const HeaderColumnCfg & sn,
		const HeaderColumnCfg & tn,
		const HeaderColumnCfg & v,
		const HeaderColumnCfg dt,
		const HeaderColumnCfg & p );

	ViewHeaderCfg( const ViewHeaderCfg & other );

	ViewHeaderCfg & operator = ( const ViewHeaderCfg & other );

	//! \return Sort column.
	int sortColumn() const;
	//! Set sort column.
	void setSortColumn( int c );

	//! \return Sort order.
	Qt::SortOrder sortOrder() const;
	//! Set sort order.
	void setSortOrder( Qt::SortOrder order );

	//! \return Configuration of the source name column.
	const HeaderColumnCfg & sourceNameColumn() const;
	//! Set configuration of the source name column.
	void setSourceNameColumn( const HeaderColumnCfg & cfg );

	//! \return Configuration of the type name column.
	const HeaderColumnCfg & typeNameColumn() const;
	//! Set configuration of the type name column.
	void setTypeNameColumn( const HeaderColumnCfg & cfg );

	//! \return Configuration of the value column.
	const HeaderColumnCfg & valueColumn() const;
	//! Set configuration of the value column.
	void setValueColumn( const HeaderColumnCfg & cfg );

	//! \return Configuration of the date/time column.
	const HeaderColumnCfg & dateTimeColumn() const;
	//! Set configuration of the date/time column.
	void setDateTimeColumn( const HeaderColumnCfg & cfg );

	//! \return Configuration of the priority column.
	const HeaderColumnCfg & priorityColumn() const;
	//! Set configuration of the priority column.
	void setPriorityColumn( const HeaderColumnCfg & cfg );

private:
	//! Sort column.
	int m_sortColumn;
	//! Sort order.
	Qt::SortOrder m_sortOrder;
	//! Configuration of the source name column.
	HeaderColumnCfg m_sourceNameColumn;
	//! Configuration of the type name column.
	HeaderColumnCfg m_typeNameColumn;
	//! Configuration of the value column.
	HeaderColumnCfg m_valueColumn;
	//! Configuration of the date/time column.
	HeaderColumnCfg m_dateTimeColumn;
	//! Configuration of the priority column.
	HeaderColumnCfg m_priorityColumn;
}; // class ViewHeaderCfg


//
// ChannelViewWindowCfg
//

//! Configuration of the channel view window.
class ChannelViewWindowCfg {
public:
	ChannelViewWindowCfg();

	ChannelViewWindowCfg( const QString & channelName,
		const WindowStateCfg & windowCfg,
		const ViewHeaderCfg & viewHeaderCfg );

	~ChannelViewWindowCfg();

	ChannelViewWindowCfg( const ChannelViewWindowCfg & other );

	ChannelViewWindowCfg & operator = ( const ChannelViewWindowCfg & other );

	//! \return Name of the channel.
	const QString & channelName() const;
	//! Set name of the channel.
	void setChannelName( const QString & name );

	//! \return Window state cfg.
	const WindowStateCfg & windowStateCfg() const;
	//! Set window state cfg.
	void setWindowStateCfg( const WindowStateCfg & cfg );

	//! \return View header configuration.
	const ViewHeaderCfg & viewHeaderCfg() const;
	//! Set view header configuration.
	void setViewHeaderCfg( const ViewHeaderCfg & cfg );

private:
	//! Name of the channel.
	QString m_channelName;
	//! Window state cfg.
	WindowStateCfg m_windowState;
	//! View header configuration.
	ViewHeaderCfg m_viewHeader;
}; // class ChannelViewWindowCfg


//
// HeaderColumnTag
//

//! Tag for header column configuration.
class HeaderColumnTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	HeaderColumnTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	HeaderColumnTag( const HeaderColumnCfg & cfg,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
		bool isMandatory = false );

	//! \return Configuration of the header column.
	HeaderColumnCfg cfg() const;

private:
	//! Size of the column.
	cfgfile::tag_scalar_t< int, cfgfile::qstring_trait_t > m_size;
	//! Pos of the column.
	cfgfile::tag_scalar_t< int, cfgfile::qstring_trait_t > m_pos;
	//! Constraint for pos.
	cfgfile::constraint_min_max_t< int > m_posConstraint;
	//! Constraint for size.
	cfgfile::constraint_min_max_t< int > m_sizeConstraint;
}; // class HeaderColumnTag


//
// SortOrderTag
//

//! Tag with sort order.
class SortOrderTag
	:	public cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t >
{
public:
	SortOrderTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
		bool isMandatory = false );

	SortOrderTag( Qt::SortOrder sortOrder,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
		bool isMandatory = false );

	//! \return Sort order.
	Qt::SortOrder sortOrder() const;

private:
	//! Init.
	void init();

private:
	//! Constraint.
	cfgfile::constraint_one_of_t< QString > m_constraint;
}; // class SortOrderTag


//
// ViewHeaderTag
//

//! Tag with configuration of the view header.
class ViewHeaderTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	ViewHeaderTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	ViewHeaderTag( const ViewHeaderCfg & cfg,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	//! \return Configuration of the header.
	ViewHeaderCfg cfg() const;

	void on_finish( const cfgfile::parser_info_t< cfgfile::qstring_trait_t > & info );

private:
	//! Sort column.
	cfgfile::tag_scalar_t< int, cfgfile::qstring_trait_t > m_sortColumn;
	//! sort column constraint.
	cfgfile::constraint_min_max_t< int > m_sortColumnConstraint;
	//! Sort order.
	SortOrderTag m_sortOrder;
	//! Configuration of the source name column.
	HeaderColumnTag m_sourceNameColumn;
	//! Configuration of the type name column.
	HeaderColumnTag m_typeNameColumn;
	//! Configuration of the value column.
	HeaderColumnTag m_valueColumn;
	//! Configuration of the date/time column.
	HeaderColumnTag m_dateTimeColumn;
	//! Configuration of the priority column.
	HeaderColumnTag m_priorityColumn;
}; // class ViewHeaderTag


//
// ChannelViewWindowTag
//

//! Tag with configuration of the channel view window.
class ChannelViewWindowTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	explicit ChannelViewWindowTag( const QString & name,
		bool isMandatory = false );

	ChannelViewWindowTag( const ChannelViewWindowCfg & cfg,
		const QString & name, bool isMandatory = false );

	~ChannelViewWindowTag();

	//! \return Configuration.
	ChannelViewWindowCfg cfg() const;

private:
	//! Name of the channel.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_channelName;
	//! Window state cfg.
	WindowStateCfgTag m_windowState;
	//! View header configuration.
	ViewHeaderTag m_viewHeader;
}; // class ChannelViewWindowCfg

} /* namespace Globe */

#endif // GLOBE__CHANNEL_VIEW_WINDOW_CFG_HPP__INCLUDED

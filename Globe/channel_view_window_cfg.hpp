
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

#ifndef GLOBE__CHANNEL_VIEW_WINDOW_CFG_HPP__INCLUDED
#define GLOBE__CHANNEL_VIEW_WINDOW_CFG_HPP__INCLUDED

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>
#include <QtConfFile/ConstraintMinMax>
#include <QtConfFile/ConstraintOneOf>

// Globe include.
#include <Globe/window_state_cfg.hpp>


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
	:	public QtConfFile::TagNoValue
{
public:
	HeaderColumnTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	HeaderColumnTag( const HeaderColumnCfg & cfg,
		QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	//! \return Configuration of the header column.
	HeaderColumnCfg cfg() const;

private:
	//! Size of the column.
	QtConfFile::TagScalar< int > m_size;
	//! Pos of the column.
	QtConfFile::TagScalar< int > m_pos;
	//! Constraint for pos.
	QtConfFile::ConstraintMinMax< int > m_posConstraint;
	//! Constraint for size.
	QtConfFile::ConstraintMinMax< int > m_sizeConstraint;
}; // class HeaderColumnTag


//
// SortOrderTag
//

//! Tag with sort order.
class SortOrderTag
	:	public QtConfFile::TagScalar< QString >
{
public:
	SortOrderTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	SortOrderTag( Qt::SortOrder sortOrder,
		QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	//! \return Sort order.
	Qt::SortOrder sortOrder() const;

private:
	//! Init.
	void init();

private:
	//! Constraint.
	QtConfFile::ConstraintOneOf< QString > m_constraint;
}; // class SortOrderTag


//
// ViewHeaderTag
//

//! Tag with configuration of the view header.
class ViewHeaderTag
	:	public QtConfFile::TagNoValue
{
public:
	ViewHeaderTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	ViewHeaderTag( const ViewHeaderCfg & cfg, QtConfFile::Tag & owner,
		const QString & name, bool isMandatory = false );

	//! \return Configuration of the header.
	ViewHeaderCfg cfg() const;

	void onFinish( const QtConfFile::ParserInfo & info );

private:
	//! Sort column.
	QtConfFile::TagScalar< int > m_sortColumn;
	//! sort column constraint.
	QtConfFile::ConstraintMinMax< int > m_sortColumnConstraint;
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
	:	public QtConfFile::TagNoValue
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
	QtConfFile::TagScalar< QString > m_channelName;
	//! Window state cfg.
	WindowStateCfgTag m_windowState;
	//! View header configuration.
	ViewHeaderTag m_viewHeader;
}; // class ChannelViewWindowCfg

} /* namespace Globe */

#endif // GLOBE__CHANNEL_VIEW_WINDOW_CFG_HPP__INCLUDED

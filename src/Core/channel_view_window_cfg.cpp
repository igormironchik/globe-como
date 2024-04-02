
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/channel_view_window_cfg.hpp>


namespace Globe {

//
// HeaderColumnCfg
//

HeaderColumnCfg::HeaderColumnCfg()
	:	m_size( -1 )
	,	m_pos( -1 )
{
}

HeaderColumnCfg::HeaderColumnCfg( int size, int pos )
	:	m_size( size )
	,	m_pos( pos )
{
}

HeaderColumnCfg::HeaderColumnCfg( const HeaderColumnCfg & other )
	:	m_size( other.size() )
	,	m_pos( other.pos() )
{
}

HeaderColumnCfg &
HeaderColumnCfg::operator = ( const HeaderColumnCfg & other )
{
	if( this != &other )
	{
		m_size = other.size();
		m_pos = other.pos();
	}

	return *this;
}

int
HeaderColumnCfg::size() const
{
	return m_size;
}

void
HeaderColumnCfg::setSize( int s )
{
	m_size = s;
}

int
HeaderColumnCfg::pos() const
{
	return m_pos;
}

void
HeaderColumnCfg::setPos( int p )
{
	m_pos = p;
}


//
// ViewHeaderCfg
//

ViewHeaderCfg::ViewHeaderCfg()
	:	m_sortColumn( 0 )
	,	m_sortOrder( Qt::AscendingOrder )
{

}

ViewHeaderCfg::ViewHeaderCfg( int sortColumn, Qt::SortOrder sortOrder,
	const HeaderColumnCfg & sn,
	const HeaderColumnCfg & tn,
	const HeaderColumnCfg & v,
	const HeaderColumnCfg dt,
	const HeaderColumnCfg & p )
	:	m_sortColumn( sortColumn )
	,	m_sortOrder( sortOrder )
	,	m_sourceNameColumn( sn )
	,	m_typeNameColumn( tn )
	,	m_valueColumn( v )
	,	m_dateTimeColumn( dt )
	,	m_priorityColumn( p )
{
}

ViewHeaderCfg::ViewHeaderCfg( const ViewHeaderCfg & other )
	:	m_sortColumn( other.sortColumn() )
	,	m_sortOrder( other.sortOrder() )
	,	m_sourceNameColumn( other.sourceNameColumn() )
	,	m_typeNameColumn( other.typeNameColumn() )
	,	m_valueColumn( other.valueColumn() )
	,	m_dateTimeColumn( other.dateTimeColumn() )
	,	m_priorityColumn( other.priorityColumn() )
{
}

ViewHeaderCfg &
ViewHeaderCfg::operator = ( const ViewHeaderCfg & other )
{
	if( this != &other )
	{
		m_sortColumn = other.sortColumn();
		m_sortOrder = other.sortOrder();
		m_sourceNameColumn = other.sourceNameColumn();
		m_typeNameColumn = other.typeNameColumn();
		m_valueColumn = other.valueColumn();
		m_dateTimeColumn = other.dateTimeColumn();
		m_priorityColumn = other.priorityColumn();
	}

	return *this;
}

int
ViewHeaderCfg::sortColumn() const
{
	return m_sortColumn;
}

void
ViewHeaderCfg::setSortColumn( int c )
{
	m_sortColumn = c;
}

Qt::SortOrder
ViewHeaderCfg::sortOrder() const
{
	return m_sortOrder;
}

void
ViewHeaderCfg::setSortOrder( Qt::SortOrder order )
{
	m_sortOrder = order;
}

const HeaderColumnCfg &
ViewHeaderCfg::sourceNameColumn() const
{
	return m_sourceNameColumn;
}

void
ViewHeaderCfg::setSourceNameColumn( const HeaderColumnCfg & cfg )
{
	m_sourceNameColumn = cfg;
}

const HeaderColumnCfg &
ViewHeaderCfg::typeNameColumn() const
{
	return m_typeNameColumn;
}

void
ViewHeaderCfg::setTypeNameColumn( const HeaderColumnCfg & cfg )
{
	m_typeNameColumn = cfg;
}

const HeaderColumnCfg &
ViewHeaderCfg::valueColumn() const
{
	return m_valueColumn;
}

void
ViewHeaderCfg::setValueColumn( const HeaderColumnCfg & cfg )
{
	m_valueColumn = cfg;
}

const HeaderColumnCfg &
ViewHeaderCfg::dateTimeColumn() const
{
	return m_dateTimeColumn;
}

void
ViewHeaderCfg::setDateTimeColumn( const HeaderColumnCfg & cfg )
{
	m_dateTimeColumn = cfg;
}

const HeaderColumnCfg &
ViewHeaderCfg::priorityColumn() const
{
	return m_priorityColumn;
}

void
ViewHeaderCfg::setPriorityColumn( const HeaderColumnCfg & cfg )
{
	m_priorityColumn = cfg;
}


//
// ChannelViewWindowCfg
//

ChannelViewWindowCfg::ChannelViewWindowCfg()
{
}

ChannelViewWindowCfg::ChannelViewWindowCfg( const QString & channelName,
	const WindowStateCfg & windowCfg,
	const ViewHeaderCfg & viewHeaderCfg )
	:	m_channelName( channelName )
	,	m_windowState( windowCfg )
	,	m_viewHeader( viewHeaderCfg )
{
}

ChannelViewWindowCfg::~ChannelViewWindowCfg()
{
}

ChannelViewWindowCfg::ChannelViewWindowCfg( const ChannelViewWindowCfg & other )
	:	m_channelName( other.channelName() )
	,	m_windowState( other.windowStateCfg() )
	,	m_viewHeader( other.viewHeaderCfg() )
{
}

ChannelViewWindowCfg &
ChannelViewWindowCfg::operator = ( const ChannelViewWindowCfg & other )
{
	if( this != &other )
	{
		m_channelName = other.channelName();
		m_windowState = other.windowStateCfg();
		m_viewHeader = other.viewHeaderCfg();
	}

	return *this;
}

const QString &
ChannelViewWindowCfg::channelName() const
{
	return m_channelName;
}

void
ChannelViewWindowCfg::setChannelName( const QString & name )
{
	m_channelName = name;
}

const WindowStateCfg &
ChannelViewWindowCfg::windowStateCfg() const
{
	return m_windowState;
}

void
ChannelViewWindowCfg::setWindowStateCfg( const WindowStateCfg & cfg )
{
	m_windowState = cfg;
}

const ViewHeaderCfg &
ChannelViewWindowCfg::viewHeaderCfg() const
{
	return m_viewHeader;
}

void
ChannelViewWindowCfg::setViewHeaderCfg( const ViewHeaderCfg & cfg )
{
	m_viewHeader = cfg;
}


//
// HeaderColumnTag
//

HeaderColumnTag::HeaderColumnTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_size( *this, QLatin1String( "size" ), true )
	,	m_pos( *this, QLatin1String( "pos" ), true )
	,	m_posConstraint( 0, 4 )
	,	m_sizeConstraint( 0, 9999 )
{
	m_size.set_constraint( &m_sizeConstraint );
	m_pos.set_constraint( &m_posConstraint );
}

HeaderColumnTag::HeaderColumnTag( const HeaderColumnCfg & cfg,
	cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_size( *this, QLatin1String( "size" ), true )
	,	m_pos( *this, QLatin1String( "pos" ), true )
	,	m_posConstraint( 0, 4 )
	,	m_sizeConstraint( 0, 9999 )
{
	m_size.set_constraint( &m_sizeConstraint );
	m_pos.set_constraint( &m_posConstraint );

	m_size.set_value( cfg.size() );
	m_pos.set_value( cfg.pos() );

	set_defined();
}

HeaderColumnCfg
HeaderColumnTag::cfg() const
{
	return HeaderColumnCfg( m_size.value(), m_pos.value() );
}


//
// SortOrderTag
//

static const QString ascendingOrder = QLatin1String( "ascending" );
static const QString descendingOrder = QLatin1String( "descending" );

SortOrderTag::SortOrderTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
	const QString & name, bool isMandatory )
	:	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > ( owner, name, isMandatory )
{
	init();
}

static QString sortOrderToString( Qt::SortOrder order )
{
	if( order == Qt::AscendingOrder )
		return ascendingOrder;
	else
		return descendingOrder;
}

SortOrderTag::SortOrderTag( Qt::SortOrder sortOrder,
	cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
{
	init();

	set_value( sortOrderToString( sortOrder ) );
}

static Qt::SortOrder sortOrderFromString( const QString & order )
{
	if( order == ascendingOrder )
		return Qt::AscendingOrder;
	else
		return Qt::DescendingOrder;
}

Qt::SortOrder
SortOrderTag::sortOrder() const
{
	return sortOrderFromString( value() );
}

void
SortOrderTag::init()
{
	m_constraint.add_value( ascendingOrder );
	m_constraint.add_value( descendingOrder );

	set_constraint( &m_constraint );
}


//
// ViewHeaderTag
//

ViewHeaderTag::ViewHeaderTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_sortColumn( *this, QLatin1String( "sortColumn" ), true )
	,	m_sortColumnConstraint( 0, 4 )
	,	m_sortOrder( *this, QLatin1String( "sortOrder" ), true )
	,	m_sourceNameColumn( *this, QLatin1String( "sourceNameColumn" ), true )
	,	m_typeNameColumn( *this, QLatin1String( "typeNameColumn" ), true )
	,	m_valueColumn( *this, QLatin1String( "valueColumn" ), true )
	,	m_dateTimeColumn( *this, QLatin1String( "dateTimeColumn" ), true )
	,	m_priorityColumn( *this, QLatin1String( "priorityColumn" ), true )
{
	m_sortColumn.set_constraint( &m_sortColumnConstraint );
}

ViewHeaderTag::ViewHeaderTag( const ViewHeaderCfg & cfg, cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
	const QString & name, bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_sortColumn( *this, QLatin1String( "sortColumn" ), true )
	,	m_sortColumnConstraint( 0, 4 )
	,	m_sortOrder( cfg.sortOrder(), *this,
			QLatin1String( "sortOrder" ), true )
	,	m_sourceNameColumn( cfg.sourceNameColumn(), *this,
			QLatin1String( "sourceNameColumn" ), true )
	,	m_typeNameColumn( cfg.typeNameColumn(), *this,
			QLatin1String( "typeNameColumn" ), true )
	,	m_valueColumn( cfg.valueColumn(), *this,
			QLatin1String( "valueColumn" ), true )
	,	m_dateTimeColumn( cfg.dateTimeColumn(), *this,
			QLatin1String( "dateTimeColumn" ), true )
	,	m_priorityColumn( cfg.priorityColumn(), *this,
			QLatin1String( "priorityColumn" ), true )
{
	m_sortColumn.set_constraint( &m_sortColumnConstraint );

	m_sortColumn.set_value( cfg.sortColumn() );

	set_defined();
}

ViewHeaderCfg
ViewHeaderTag::cfg() const
{
	return ViewHeaderCfg( m_sortColumn.value(),
		m_sortOrder.sortOrder(),
		m_sourceNameColumn.cfg(),
		m_typeNameColumn.cfg(),
		m_valueColumn.cfg(),
		m_dateTimeColumn.cfg(),
		m_priorityColumn.cfg() );
}

void
ViewHeaderTag::on_finish( const cfgfile::parser_info_t< cfgfile::qstring_trait_t > & info )
{
	if( m_sourceNameColumn.cfg().pos() +
		m_typeNameColumn.cfg().pos() +
		m_valueColumn.cfg().pos() +
		m_dateTimeColumn.cfg().pos() +
		m_priorityColumn.cfg().pos() != 10 )
			throw cfgfile::exception_t< cfgfile::qstring_trait_t >( QString( "Wrong positions of the columns. "
				"Where parent is \"%1\". In file \"%2\" on line %3." )
					.arg( name(), info.file_name(), QString::number( info.line_number() ) ) );

	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >::on_finish( info );
}


//
// ChannelViewWindowTag
//

ChannelViewWindowTag::ChannelViewWindowTag( const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > ( name, isMandatory )
	,	m_channelName( *this, QLatin1String( "channelName" ), true )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
	,	m_viewHeader( *this, QLatin1String( "header" ), false )
{
}

ChannelViewWindowTag::ChannelViewWindowTag( const ChannelViewWindowCfg & cfg,
	const QString & name, bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > ( name, isMandatory )
	,	m_channelName( *this, QLatin1String( "channelName" ), true )
	,	m_windowState( cfg.windowStateCfg(), *this,
			QLatin1String( "windowState" ), true )
	,	m_viewHeader( cfg.viewHeaderCfg(), *this,
			QLatin1String( "header" ), true )
{
	m_channelName.set_value( cfg.channelName() );

	set_defined();
}

ChannelViewWindowTag::~ChannelViewWindowTag()
{
}

ChannelViewWindowCfg
ChannelViewWindowTag::cfg() const
{
	ChannelViewWindowCfg cfg;

	cfg.setChannelName( m_channelName.value() );
	cfg.setWindowStateCfg( m_windowState.cfg() );

	if( m_viewHeader.is_defined() )
		cfg.setViewHeaderCfg( m_viewHeader.cfg() );

	return cfg;
}

} /* namespace Globe */

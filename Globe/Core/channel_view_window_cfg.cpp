
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

// Globe include.
#include <Globe/Core/channel_view_window_cfg.hpp>


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

HeaderColumnTag::HeaderColumnTag( QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_size( *this, QLatin1String( "size" ), true )
	,	m_pos( *this, QLatin1String( "pos" ), true )
	,	m_posConstraint( 0, 4 )
	,	m_sizeConstraint( 0, 9999 )
{
	m_size.setConstraint( &m_sizeConstraint );
	m_pos.setConstraint( &m_posConstraint );
}

HeaderColumnTag::HeaderColumnTag( const HeaderColumnCfg & cfg,
	QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_size( *this, QLatin1String( "size" ), true )
	,	m_pos( *this, QLatin1String( "pos" ), true )
	,	m_posConstraint( 0, 4 )
	,	m_sizeConstraint( 0, 9999 )
{
	m_size.setConstraint( &m_sizeConstraint );
	m_pos.setConstraint( &m_posConstraint );

	m_size.setValue( cfg.size() );
	m_pos.setValue( cfg.pos() );

	setDefined();
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

SortOrderTag::SortOrderTag( QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagScalar< QString > ( owner, name, isMandatory )
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
	QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagScalar< QString > ( owner, name, isMandatory )
{
	init();

	setValue( sortOrderToString( sortOrder ) );
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
	m_constraint.addValue( ascendingOrder );
	m_constraint.addValue( descendingOrder );

	setConstraint( &m_constraint );
}


//
// ViewHeaderTag
//

ViewHeaderTag::ViewHeaderTag( QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_sortColumn( *this, QLatin1String( "sortColumn" ), true )
	,	m_sortColumnConstraint( 0, 4 )
	,	m_sortOrder( *this, QLatin1String( "sortOrder" ), true )
	,	m_sourceNameColumn( *this, QLatin1String( "sourceNameColumn" ), true )
	,	m_typeNameColumn( *this, QLatin1String( "typeNameColumn" ), true )
	,	m_valueColumn( *this, QLatin1String( "valueColumn" ), true )
	,	m_dateTimeColumn( *this, QLatin1String( "dateTimeColumn" ), true )
	,	m_priorityColumn( *this, QLatin1String( "priorityColumn" ), true )
{
	m_sortColumn.setConstraint( &m_sortColumnConstraint );
}

ViewHeaderTag::ViewHeaderTag( const ViewHeaderCfg & cfg, QtConfFile::Tag & owner,
	const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
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
	m_sortColumn.setConstraint( &m_sortColumnConstraint );

	m_sortColumn.setValue( cfg.sortColumn() );

	setDefined();
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
ViewHeaderTag::onFinish( const QtConfFile::ParserInfo & info )
{
	if( m_sourceNameColumn.cfg().pos() +
		m_typeNameColumn.cfg().pos() +
		m_valueColumn.cfg().pos() +
		m_dateTimeColumn.cfg().pos() +
		m_priorityColumn.cfg().pos() != 10 )
			throw QtConfFile::Exception( QString( "Wrong positions of the columns. "
				"Where parent is \"%1\". In file \"%2\" on line %3." )
					.arg( name() )
					.arg( info.fileName() )
					.arg( info.lineNumber() ) );

	QtConfFile::TagNoValue::onFinish( info );
}


//
// ChannelViewWindowTag
//

ChannelViewWindowTag::ChannelViewWindowTag( const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_channelName( *this, QLatin1String( "channelName" ), true )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
	,	m_viewHeader( *this, QLatin1String( "header" ), false )
{
}

ChannelViewWindowTag::ChannelViewWindowTag( const ChannelViewWindowCfg & cfg,
	const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_channelName( *this, QLatin1String( "channelName" ), true )
	,	m_windowState( cfg.windowStateCfg(), *this,
			QLatin1String( "windowState" ), true )
	,	m_viewHeader( cfg.viewHeaderCfg(), *this,
			QLatin1String( "header" ), true )
{
	m_channelName.setValue( cfg.channelName() );

	setDefined();
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

	if( m_viewHeader.isDefined() )
		cfg.setViewHeaderCfg( m_viewHeader.cfg() );

	return cfg;
}

} /* namespace Globe */

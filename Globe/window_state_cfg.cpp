
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 Igor Mironchik

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
#include <Globe/window_state_cfg.hpp>

// C++ include.
#include <limits>


namespace Globe {

//
// WindowStateCfg
//

WindowStateCfg::WindowStateCfg()
	:	m_state( NormalWindow )
	,	m_isActive( false )
{
}

WindowStateCfg::WindowStateCfg( const QPoint & pos, const QSize & size,
	WindowState state, bool isActive )
	:	m_pos( pos )
	,	m_size( size )
	,	m_state( state )
	,	m_isActive( isActive )
{
}

WindowStateCfg::~WindowStateCfg()
{
}

WindowStateCfg::WindowStateCfg( const WindowStateCfg & other )
	:	m_pos( other.pos() )
	,	m_size( other.size() )
	,	m_state( other.state() )
	,	m_isActive( other.isActive() )
{
}

WindowStateCfg &
WindowStateCfg::operator = ( const WindowStateCfg & other )
{
	if( this != &other )
	{
		m_pos = other.pos();
		m_size = other.size();
		m_state = other.state();
		m_isActive = other.isActive();
	}

	return *this;
}

const QPoint &
WindowStateCfg::pos() const
{
	return m_pos;
}

void
WindowStateCfg::setPos( const QPoint & pos )
{
	m_pos = pos;
}

const QSize &
WindowStateCfg::size() const
{
	return m_size;
}

void
WindowStateCfg::setSize( const QSize & size )
{
	m_size = size;
}

WindowState
WindowStateCfg::state() const
{
	return m_state;
}

void
WindowStateCfg::setState( WindowState state )
{
	m_state = state;
}

bool
WindowStateCfg::isActive() const
{
	return m_isActive;
}

void
WindowStateCfg::setActive( bool on )
{
	m_isActive = on;
}


//
// PosTag
//

PosTag::PosTag( QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_x( *this, QLatin1String( "x" ), true )
	,	m_y( *this, QLatin1String( "y" ), true )
{
}

PosTag::PosTag( const QPoint & pos,
	QtConfFile::Tag & owner, const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_x( *this, QLatin1String( "x" ), true )
	,	m_y( *this, QLatin1String( "y" ), true )
{
	m_x.setValue( pos.x() );
	m_y.setValue( pos.y() );

	setDefined();
}

QPoint
PosTag::pos() const
{
	return QPoint( m_x.value(), m_y.value() );
}


//
// SizeTag
//

SizeTag::SizeTag( QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_width( *this, QLatin1String( "width" ), true )
	,	m_height( *this, QLatin1String( "height" ), true )
	,	m_constraint( 0, std::numeric_limits< int >::max() )
{
	m_width.setConstraint( &m_constraint );
	m_height.setConstraint( &m_constraint );
}

SizeTag::SizeTag( const QSize & size,
	QtConfFile::Tag & owner, const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_width( *this, QLatin1String( "width" ), true )
	,	m_height( *this, QLatin1String( "height" ), true )
	,	m_constraint( 0, std::numeric_limits< int >::max() )
{
	m_width.setConstraint( &m_constraint );
	m_height.setConstraint( &m_constraint );

	m_width.setValue( size.width() );
	m_height.setValue( size.height() );

	setDefined();
}

QSize
SizeTag::size() const
{
	return QSize( m_width.value(), m_height.value() );
}


//
// StateTag
//

static const QString normalWindow = QLatin1String( "normalWindow" );
static const QString minimizedWindow = QLatin1String( "minimizedWindow" );
static const QString maximizedWindow = QLatin1String( "maximizedWindow" );
static const QString hiddenWindow = QLatin1String( "hiddenWindow" );

static inline QString windowStateToString( WindowState state )
{
	if( state == NormalWindow )
		return normalWindow;
	else if( state == MinimizedWindow )
		return minimizedWindow;
	else if( state == HiddenWindow )
		return hiddenWindow;
	else
		return maximizedWindow;
}

static inline WindowState stringToWindowState( const QString & v )
{
	if( v == normalWindow )
		return NormalWindow;
	else if( v == minimizedWindow )
		return MinimizedWindow;
	else if( v == hiddenWindow )
		return HiddenWindow;
	else
		return MaximizedWindow;
}

StateTag::StateTag( QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagScalar< QString >( owner, name, isMandatory )
{
	init();
}

StateTag::StateTag( const WindowState & state,
	QtConfFile::Tag & owner, const QString & name, bool isMandatory )
	:	QtConfFile::TagScalar< QString >( owner, name, isMandatory )
{
	init();

	setValue( windowStateToString( state ) );
}

void
StateTag::init()
{
	m_constraint.addValue( normalWindow );
	m_constraint.addValue( minimizedWindow );
	m_constraint.addValue( maximizedWindow );
	m_constraint.addValue( hiddenWindow );

	setConstraint( &m_constraint );
}

WindowState
StateTag::state() const
{
	return stringToWindowState( value() );
}


//
// WindowStateCfgTag
//

WindowStateCfgTag::WindowStateCfgTag( const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( name, isMandatory )
	,	m_pos( *this, QLatin1String( "position" ), true )
	,	m_size( *this, QLatin1String( "size" ), true )
	,	m_state( *this, QLatin1String( "state" ), true )
	,	m_isActive( *this, QLatin1String( "activeWindow" ), false )
{
}

WindowStateCfgTag::WindowStateCfgTag( QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_pos( *this, QLatin1String( "position" ), true )
	,	m_size( *this, QLatin1String( "size" ), true )
	,	m_state( *this, QLatin1String( "state" ), true )
	,	m_isActive( *this, QLatin1String( "activeWindow" ), false )
{

}

WindowStateCfgTag::WindowStateCfgTag( const WindowStateCfg & cfg,
	QtConfFile::Tag & owner, const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_pos( cfg.pos(), *this, QLatin1String( "position" ), true )
	,	m_size( cfg.size(), *this, QLatin1String( "size" ), true )
	,	m_state( cfg.state(), *this, QLatin1String( "state" ), true )
	,	m_isActive( *this, QLatin1String( "activeWindow" ), false )
{
	if( cfg.isActive() )
		m_isActive.setDefined();

	setDefined();
}

WindowStateCfg
WindowStateCfgTag::cfg() const
{
	WindowStateCfg cfg;

	cfg.setPos( m_pos.pos() );
	cfg.setSize( m_size.size() );
	cfg.setState( m_state.state() );
	cfg.setActive( m_isActive.isDefined() );

	return cfg;
}

} /* namespace Globe */

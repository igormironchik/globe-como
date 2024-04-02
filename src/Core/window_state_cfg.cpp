
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/window_state_cfg.hpp>

// Qt include.
#include <QWidget>
#include <QScreen>
#include <QApplication>


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
// windowState
//

static inline WindowState state( const QWidget * w )
{
	Qt::WindowStates st = w->windowState();

	if( w->isHidden() )
		return HiddenWindow;
	else if( st & Qt::WindowNoState )
		return NormalWindow;
	else if( st & Qt::WindowMinimized )
		return MinimizedWindow;
	else if( st & Qt::WindowMaximized )
		return MaximizedWindow;
	else
		return NormalWindow;
}

WindowStateCfg
windowStateCfg( const QWidget * window )
{
	WindowStateCfg cfg;

	cfg.setPos( window->pos() );
	cfg.setSize( QSize( window->width(), window->height() ) );
	cfg.setState( state( window ) );
	cfg.setActive( window->isActiveWindow() );

	return cfg;
}


//
// restoreWindowState
//

void
restoreWindowState( const WindowStateCfg & cfg, QWidget * window )
{
	static const QRect screenGeometry =
		QApplication::primaryScreen()->availableGeometry();

	QPoint pos = cfg.pos();

	if( !screenGeometry.contains( pos ) )
	{
		if( pos.x() < screenGeometry.x() )
			pos.setX( screenGeometry.x() + 10 );
		else if( pos.x() >= screenGeometry.x() + screenGeometry.width() )
			pos.setX( screenGeometry.x() + 10 );

		if( pos.y() < screenGeometry.y() )
			pos.setY( screenGeometry.y() + 10 );
		else if( pos.y() >= screenGeometry.y() + screenGeometry.height() )
			pos.setY( screenGeometry.y() + 10 );
	}

	window->move( pos );

	if( cfg.size().isValid() )
		window->resize( cfg.size() );

	if( cfg.state() == HiddenWindow )
		window->hide();
	else if( cfg.state() == MinimizedWindow )
		window->showMinimized();
	else if( cfg.state() == MaximizedWindow )
		window->showMaximized();
	else
		window->show();
}


//
// toRelativePos
//

QPointF toRelativePos( const QPoint & p )
{
	const QRect geometry = QApplication::primaryScreen()->geometry();

	return QPointF( (qreal) p.x() / (qreal) geometry.width(),
		(qreal) p.y() / (qreal) geometry.height() );
}


//
// fromRelativePos
//

QPoint fromRelativePos( const QPointF & p )
{
	const QRect geometry = QApplication::primaryScreen()->geometry();

	return QPoint( p.x() * geometry.width(), p.y() * geometry.height() );
}


//
// PosTag
//

PosTag::PosTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_x( *this, QLatin1String( "x" ), true )
	,	m_y( *this, QLatin1String( "y" ), true )
{
}

PosTag::PosTag( const QPoint & pos,
	cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name, bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_x( *this, QLatin1String( "x" ), true )
	,	m_y( *this, QLatin1String( "y" ), true )
{
	const QPointF fp = toRelativePos( pos );

	m_x.set_value( fp.x() );
	m_y.set_value( fp.y() );

	set_defined();
}

QPoint
PosTag::pos() const
{
	const QPointF fp( m_x.value(), m_y.value() );

	return fromRelativePos( fp );
}


//
// toRelativeSize
//

QSizeF toRelativeSize( const QSize & s )
{
	const QRect geometry = QApplication::primaryScreen()->geometry();

	return QSizeF( (qreal) s.width() / (qreal) geometry.width(),
		(qreal) s.height() / (qreal) geometry.height() );
}


//
// fromRelativeSize
//

QSize fromRelativeSize( const QSizeF & s )
{
	const QRect geometry = QApplication::primaryScreen()->geometry();

	return QSize( s.width() * geometry.width(),
		s.height() * geometry.height() );
}


//
// SizeTag
//

SizeTag::SizeTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_width( *this, QLatin1String( "width" ), true )
	,	m_height( *this, QLatin1String( "height" ), true )
	,	m_constraint( 0.0, 1.0 )
{
	m_width.set_constraint( &m_constraint );
	m_height.set_constraint( &m_constraint );
}

SizeTag::SizeTag( const QSize & size,
	cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name, bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_width( *this, QLatin1String( "width" ), true )
	,	m_height( *this, QLatin1String( "height" ), true )
	,	m_constraint( 0.0, 1.0 )
{
	m_width.set_constraint( &m_constraint );
	m_height.set_constraint( &m_constraint );

	const QSizeF fs = toRelativeSize( size );

	m_width.set_value( fs.width() );
	m_height.set_value( fs.height() );

	set_defined();
}

QSize
SizeTag::size() const
{
	const QSizeF fs( m_width.value(), m_height.value() );

	return fromRelativeSize( fs );
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

StateTag::StateTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
{
	init();
}

StateTag::StateTag( const WindowState & state,
	cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name, bool isMandatory )
	:	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
{
	init();

	set_value( windowStateToString( state ) );
}

void
StateTag::init()
{
	m_constraint.add_value( normalWindow );
	m_constraint.add_value( minimizedWindow );
	m_constraint.add_value( maximizedWindow );
	m_constraint.add_value( hiddenWindow );

	set_constraint( &m_constraint );
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
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > ( name, isMandatory )
	,	m_pos( *this, QLatin1String( "position" ), true )
	,	m_size( *this, QLatin1String( "size" ), true )
	,	m_state( *this, QLatin1String( "state" ), true )
	,	m_isActive( *this, QLatin1String( "activeWindow" ), false )
{
}

WindowStateCfgTag::WindowStateCfgTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_pos( *this, QLatin1String( "position" ), true )
	,	m_size( *this, QLatin1String( "size" ), true )
	,	m_state( *this, QLatin1String( "state" ), true )
	,	m_isActive( *this, QLatin1String( "activeWindow" ), false )
{

}

WindowStateCfgTag::WindowStateCfgTag( const WindowStateCfg & cfg,
	cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name, bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_pos( cfg.pos(), *this, QLatin1String( "position" ), true )
	,	m_size( cfg.size(), *this, QLatin1String( "size" ), true )
	,	m_state( cfg.state(), *this, QLatin1String( "state" ), true )
	,	m_isActive( *this, QLatin1String( "activeWindow" ), false )
{
	if( cfg.isActive() )
		m_isActive.set_defined();

	set_defined();
}

WindowStateCfg
WindowStateCfgTag::cfg() const
{
	WindowStateCfg cfg;

	cfg.setPos( m_pos.pos() );
	cfg.setSize( m_size.size() );
	cfg.setState( m_state.state() );
	cfg.setActive( m_isActive.is_defined() );

	return cfg;
}

} /* namespace Globe */

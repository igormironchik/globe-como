
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

#ifndef GLOBE__WINDOW_STATE_CFG_HPP__INCLUDED
#define GLOBE__WINDOW_STATE_CFG_HPP__INCLUDED

// Qt include.
#include <QPoint>
#include <QSize>

// cfgfile include.
#include <cfgfile/all.hpp>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE


namespace Globe {

//
// WindowState
//

//! Possible states of the window.
enum WindowState {
	//! Normal window.
	NormalWindow = 0x00,
	//! Minimized window.
	MinimizedWindow = 0x01,
	//! Maximized window.
	MaximizedWindow = 0x02,
	//! Hidden window.
	HiddenWindow = 0x04
}; // enum WindowState


//
// WindowStateCfg
//

//! Configuration of the window's state.
class WindowStateCfg {
public:
	WindowStateCfg();

	WindowStateCfg( const QPoint & pos, const QSize & size,
		WindowState state, bool isActive = false );

	~WindowStateCfg();

	WindowStateCfg( const WindowStateCfg & other );

	WindowStateCfg & operator = ( const WindowStateCfg & other );

	//! \return Position of the window.
	const QPoint & pos() const;
	//! Set position of the window.
	void setPos( const QPoint & pos );

	//! \return Size of the window.
	const QSize & size() const;
	//! Set size of the window.
	void setSize( const QSize & size );

	//! \return Window state.
	WindowState state() const;
	//! Set window state.
	void setState( WindowState state );

	//! \return Is this window active?
	bool isActive() const;
	//! Set active this window or not.
	void setActive( bool on = true );

private:
	//! Position of the window.
	QPoint m_pos;
	//! Size of the window.
	QSize m_size;
	//! State of the window.
	WindowState m_state;
	//! Is window active?
	bool m_isActive;
}; // class WindowStateCfg


//
// windowState
//

//! \return Window state cfg structure for the given window.
WindowStateCfg windowStateCfg( const QWidget * window );


//
// restoreWindowState
//

//! Restore window state.
void restoreWindowState( const WindowStateCfg & cfg, QWidget * window );


//
// PosTag
//

//! Tag with position.
class PosTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	PosTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	PosTag( const QPoint & pos,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	//! \return Position.
	QPoint pos() const;

private:
	//! X coordinates.
	cfgfile::tag_scalar_t< double, cfgfile::qstring_trait_t > m_x;
	//! Y coordinates.
	cfgfile::tag_scalar_t< double, cfgfile::qstring_trait_t > m_y;
}; // class PosTag


//
// SizeTag
//

//! Tag with size.
class SizeTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	SizeTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	SizeTag( const QSize & size,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	//! \return Size.
	QSize size() const;

private:
	//! Width.
	cfgfile::tag_scalar_t< double, cfgfile::qstring_trait_t > m_width;
	//! Height.
	cfgfile::tag_scalar_t< double, cfgfile::qstring_trait_t > m_height;
	//! Constraint for width and height.
	cfgfile::constraint_min_max_t< double > m_constraint;
}; // class SizeTag


//
// StateTag
//

//! Tag with state.
class StateTag
	:	public cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t >
{
public:
	StateTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	StateTag( const WindowState & state,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	//! \return State.
	WindowState state() const;

private:
	//! Init.
	void init();

private:
	//! Constraint.
	cfgfile::constraint_one_of_t< QString > m_constraint;
}; // class StateTag


//
// WindowStateCfgTag
//

//! Tag in the conf file with the state of the window.
class WindowStateCfgTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	explicit WindowStateCfgTag( const QString & name, bool isMandatory = false );

	WindowStateCfgTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	WindowStateCfgTag( const WindowStateCfg & cfg,
		cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
		const QString & name, bool isMandatory = false );

	//! \return Configuration.
	WindowStateCfg cfg() const;

private:
	//! Position.
	PosTag m_pos;
	//! Size.
	SizeTag m_size;
	//! State.
	StateTag m_state;
	//! Is window active?
	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > m_isActive;
}; // class WindowStateCfgTag

} /* namespace Globe */

#endif // GLOBE__WINDOW_STATE_CFG_HPP__INCLUDED

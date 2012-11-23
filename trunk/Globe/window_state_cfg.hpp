
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

#ifndef GLOBE__WINDOW_STATE_CFG_HPP__INCLUDED
#define GLOBE__WINDOW_STATE_CFG_HPP__INCLUDED

// Qt include.
#include <QtCore/QPoint>
#include <QtCore/QSize>

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>
#include <QtConfFile/ConstraintOneOf>
#include <QtConfFile/ConstraintMinMax>


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
// PosTag
//

//! Tag with position.
class PosTag
	:	public QtConfFile::TagNoValue
{
public:
	PosTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	PosTag( const QPoint & pos,
		QtConfFile::Tag & owner, const QString & name, bool isMandatory = false );

	//! \return Position.
	QPoint pos() const;

private:
	//! X coordinates.
	QtConfFile::TagScalar< int > m_x;
	//! Y coordinates.
	QtConfFile::TagScalar< int > m_y;
}; // class PosTag


//
// SizeTag
//

//! Tag with size.
class SizeTag
	:	public QtConfFile::TagNoValue
{
public:
	SizeTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	SizeTag( const QSize & size,
		QtConfFile::Tag & owner, const QString & name, bool isMandatory = false );

	//! \return Size.
	QSize size() const;

private:
	//! Width.
	QtConfFile::TagScalar< int > m_width;
	//! Height.
	QtConfFile::TagScalar< int > m_height;
	//! Constraint for width and height.
	QtConfFile::ConstraintMinMax< int > m_constraint;
}; // class SizeTag


//
// StateTag
//

//! Tag with state.
class StateTag
	:	public QtConfFile::TagScalar< QString >
{
public:
	StateTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	StateTag( const WindowState & state,
		QtConfFile::Tag & owner, const QString & name, bool isMandatory = false );

	//! \return State.
	WindowState state() const;

private:
	//! Init.
	void init();

private:
	//! Constraint.
	QtConfFile::ConstraintOneOf< QString > m_constraint;
}; // class StateTag


//
// WindowStateCfgTag
//

//! Tag in the conf file with the state of the window.
class WindowStateCfgTag
	:	public QtConfFile::TagNoValue
{
public:
	explicit WindowStateCfgTag( const QString & name, bool isMandatory = false );

	WindowStateCfgTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	WindowStateCfgTag( const WindowStateCfg & cfg,
		QtConfFile::Tag & owner, const QString & name, bool isMandatory = false );

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
	QtConfFile::TagNoValue m_isActive;
}; // class WindowStateCfgTag

} /* namespace Globe */

#endif // GLOBE__WINDOW_STATE_CFG_HPP__INCLUDED


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

#ifndef GLOBE__CONDITION_CFG_HPP__INCLUDED
#define GLOBE__CONDITION_CFG_HPP__INCLUDED

// Globe include.
#include <Globe/condition.hpp>

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>
#include <QtConfFile/ConstraintOneOf>


namespace Globe {

//
// FIX ME! For perfomance increase IfStatementTag and ConditionTag
// must be templated. Due to changes of QVariant value every time in
// calculating condition (look at Condition::check()).
// But it's neccessary to confirm with profiler.
// First implementation will so as is.
//

//
// IfStatementTag
//

//! Tag with logical relation.
class IfStatementTag
	:	public QtConfFile::TagScalar< QString >
{
public:
	IfStatementTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	IfStatementTag( const QVariant & value, QtConfFile::Tag & owner,
		const QString & name, bool isMandatory = false );

	//! \return Value for the if-statement.
	QString value() const;
}; // class IfStatementTag


//
// ConditionTag
//

//! Configuration's tag for condition.
class ConditionTag
	:	public QtConfFile::TagNoValue
{
public:
	explicit ConditionTag( const QString & name, bool isMandatory = false );

	ConditionTag( const Condition & cond, const QString & name,
		bool isMandatory = false );

	//! Called when tag parsing finished.
	void onFinish( const QtConfFile::ParserInfo & info );

	//! \return Condition.
	Condition condition() const;

private:
	//! If greater or equal.
	IfStatementTag m_greaterOrEqual;
	//! If greater.
	IfStatementTag m_greater;
	//! If equal.
	IfStatementTag m_equal;
	//! If less.
	IfStatementTag m_less;
	//! If less or equal.
	IfStatementTag m_lessOrEqual;
	//! Level.
	QtConfFile::TagScalar< QString > m_level;
	//! Constraint for level.
	QtConfFile::ConstraintOneOf< QString > m_levelConstraint;
	//! Message.
	QtConfFile::TagScalar< QString > m_message;
}; // class ConditionTag


//
// OtherwiseTag
//

//! Configuration's tag for otherwise condition.
class OtherwiseTag
	:	public QtConfFile::TagNoValue
{
public:
	OtherwiseTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	OtherwiseTag( const Condition & cond, QtConfFile::Tag & owner,
		const QString & name, bool isMandatory = false );

	//! \return Condition.
	Condition value() const;

private:
	//! Level.
	QtConfFile::TagScalar< QString > m_level;
	//! Constraint for level.
	QtConfFile::ConstraintOneOf< QString > m_levelConstraint;
	//! Message.
	QtConfFile::TagScalar< QString > m_message;
}; // class OtherwiseTag

} /* namespace Globe */

#endif // GLOBE__CONDITION_CFG_HPP__INCLUDED

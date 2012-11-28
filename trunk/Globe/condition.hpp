
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

#ifndef GLOBE__CONDITION_HPP__INCLUDED
#define GLOBE__CONDITION_HPP__INCLUDED

// Qt include.
#include <QtCore/QVariant>
#include <QtCore/QString>

// Como include.
#include <Como/Source>

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>
#include <QtConfFile/ConstraintOneOf>


namespace Globe {

//! Expression in the condition
enum Expression {
	//! If less or equal.
	IfLessOrEqual = 0x01,
	//! If less.
	IfLess = 0x02,
	//! If equal.
	IfEqual = 0x03,
	//! If greater.
	IfGreater = 0x04,
	//! If greater or equal.
	IfGreaterOrEqual = 0x05
}; // enum Expression


//! Level of severity of the condition.
enum Level {
	//! Critical state of the source.
	Critical = 0x01,
	//! Error state of the source.
	Error = 0x02,
	//! Warning state of the source.
	Warning = 0x03,
	//! Debug state of the source.
	Debug = 0x04,
	//! Info state of the source (all is ok).
	Info = 0x05
}; // enum Level


//
// Condition
//

//! Condition in the properties of the Como source.
class Condition {
public:
	Condition();

	Condition( const Condition & other );

	Condition & operator = ( const Condition & other );

	//! Check if this condition is match the given value.
	bool check( const QVariant & val, Como::Source::Type valueType  );

	//! \return Tpe of the condition (Expression).
	Expression type() const;
	//! Set type of the condition (Expression).
	void setType( Expression expr );

	//! \return Value for the comparison.
	const QVariant & value() const;
	//! Set value fot the comparison.
	void setValue( const QVariant & v );

	//! \return Level of severity of the source.
	Level level() const;
	//! Set level of severity of the source.
	void setLevel( Level l );

	//! \return Message for this condition.
	const QString & message() const;
	//! Set message for this condition.
	void setMessage( const QString & msg );

private:
	//! Expression type.
	Expression m_exprType;
	//! Value for the comparison.
	QVariant m_value;
	//! Level of severity.
	Level m_level;
	//! Message.
	QString m_message;
}; // class Condition


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

} /* namespace Globe */

#endif // GLOBE__CONDITION_HPP__INCLUDED

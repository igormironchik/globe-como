
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__CONDITION_HPP__INCLUDED
#define GLOBE__CONDITION_HPP__INCLUDED

// Qt include.
#include <QVariant>
#include <QString>

// Como include.
#include <Como/Source>


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
	//! Uninitialized.
	Uninitialized = 0xFFFF,
	//! None level,
	None = 0xFF,
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
	bool check( const QVariant & val, Como::Source::Type valueType  ) const;

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

	//! \return Is condition valid?
	bool isValid() const;

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

} /* namespace Globe */

#endif // GLOBE__CONDITION_HPP__INCLUDED

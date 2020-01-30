
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

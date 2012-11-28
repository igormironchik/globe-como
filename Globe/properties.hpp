
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

#ifndef GLOBE__PROPERTIES_HPP__INCLUDED
#define GLOBE__PROPERTIES_HPP__INCLUDED

// Como include.
#include <Como/Source>

// Qt include.
#include <QtCore/QList>

// Globe include.
#include <Globe/condition.hpp>


namespace Globe {

//
// Properties
//

//! Properties of the source.
class Properties {
public:
	explicit Properties( const Como::Source & source );

	Properties( const Properties & other );

	Properties & operator = ( const Properties & other );

	//! \return Priority of the source.
	int priority() const;
	//! Set priority of the source.
	void setPriority( int p );

	//! \return Amount of conditions.
	int conditionsAmount() const;
	//! \return Condition with the given index.
	Condition & conditionAt( int index );
	//! \return Condition with the given index.
	const Condition & conditionAt( int index ) const;
	//! Insert new condition to the new place with \arg index.
	//! If \arg index is -1 then condition will be placed to the end of list.
	void insertCondition( const Condition & cond, int index = -1 );
	//! Remove condition with the \arg index.
	void removeCondition( int index );
	//! Swap to conditions in the list.
	void swapConditions( int i, int j );

private:
	//! Priority of the source.
	int m_priority;
	//! List of conditions for this source.
	QList< Condition > m_conditions;
}; // class Properties

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_HPP__INCLUDED

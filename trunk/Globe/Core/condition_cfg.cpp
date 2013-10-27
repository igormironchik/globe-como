
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
#include <Globe/Core/condition_cfg.hpp>


namespace Globe {

//
// OtherwiseTag
//

OtherwiseTag::OtherwiseTag( QtConfFile::Tag & owner, const QString & name,
	bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_level( *this, QLatin1String( "level" ), true )
	,	m_message( *this, QLatin1String( "message" ), false )
{
	m_levelConstraint.addValue( criticalLevelString );
	m_levelConstraint.addValue( errorLevelString );
	m_levelConstraint.addValue( warningLevelString );
	m_levelConstraint.addValue( debugLevelString );
	m_levelConstraint.addValue( infoLevelString );
	m_levelConstraint.addValue( noneLevelString );

	m_level.setConstraint( &m_levelConstraint );
}

OtherwiseTag::OtherwiseTag( const Condition & cond, QtConfFile::Tag & owner,
	const QString & name, bool isMandatory )
	:	QtConfFile::TagNoValue( owner, name, isMandatory )
	,	m_level( *this, QLatin1String( "level" ), true )
	,	m_message( *this, QLatin1String( "message" ), false )
{
	m_levelConstraint.addValue( criticalLevelString );
	m_levelConstraint.addValue( errorLevelString );
	m_levelConstraint.addValue( warningLevelString );
	m_levelConstraint.addValue( debugLevelString );
	m_levelConstraint.addValue( infoLevelString );
	m_levelConstraint.addValue( noneLevelString );

	m_level.setConstraint( &m_levelConstraint );

	m_level.setValue( levelToString( cond.level() ) );

	if( !cond.message().isEmpty() )
		m_message.setValue( cond.message() );

	setDefined();
}

Condition
OtherwiseTag::value() const
{
	Condition c;

	c.setLevel( levelFromString( m_level.value() ) );

	if( m_message.isDefined() )
		c.setMessage( m_message.value() );

	return c;
}

} /* namespace Globe */


/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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


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

// Globe include.
#include <Globe/Core/condition_cfg.hpp>


namespace Globe {

//
// OtherwiseTag
//

OtherwiseTag::OtherwiseTag( cfgfile::tag_t< cfgfile::qstring_trait_t > & owner, const QString & name,
	bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_level( *this, QLatin1String( "level" ), true )
	,	m_message( *this, QLatin1String( "message" ), false )
{
	m_levelConstraint.add_value( criticalLevelString );
	m_levelConstraint.add_value( errorLevelString );
	m_levelConstraint.add_value( warningLevelString );
	m_levelConstraint.add_value( debugLevelString );
	m_levelConstraint.add_value( infoLevelString );
	m_levelConstraint.add_value( noneLevelString );

	m_level.set_constraint( &m_levelConstraint );
}

OtherwiseTag::OtherwiseTag( const Condition & cond, cfgfile::tag_t< cfgfile::qstring_trait_t > & owner,
	const QString & name, bool isMandatory )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			owner, name, isMandatory )
	,	m_level( *this, QLatin1String( "level" ), true )
	,	m_message( *this, QLatin1String( "message" ), false )
{
	m_levelConstraint.add_value( criticalLevelString );
	m_levelConstraint.add_value( errorLevelString );
	m_levelConstraint.add_value( warningLevelString );
	m_levelConstraint.add_value( debugLevelString );
	m_levelConstraint.add_value( infoLevelString );
	m_levelConstraint.add_value( noneLevelString );

	m_level.set_constraint( &m_levelConstraint );

	m_level.set_value( levelToString( cond.level() ) );

	if( !cond.message().isEmpty() )
		m_message.set_value( cond.message() );

	set_defined();
}

Condition
OtherwiseTag::value() const
{
	Condition c;

	c.setLevel( levelFromString( m_level.value() ) );

	if( m_message.is_defined() )
		c.setMessage( m_message.value() );

	return c;
}

} /* namespace Globe */

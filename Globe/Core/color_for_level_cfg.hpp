
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

#ifndef GLOBE__COLOR_FOR_LEVEL_CFG_HPP__INCLUDED
#define GLOBE__COLOR_FOR_LEVEL_CFG_HPP__INCLUDED

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>


namespace Globe {

class ColorForLevel;


//
// ColorForLevelTag
//

//! Tag with corresondence between level and color.
class ColorForLevelTag
	:	public QtConfFile::TagNoValue
{
public:
	ColorForLevelTag();

	explicit ColorForLevelTag( ColorForLevel * colorForLevel );

	//! Init correspondence from configuration.
	void initColorForLevel( ColorForLevel * colorForLevel );

private:
	//! Color for "none" level.
	QtConfFile::TagScalar< QString > m_noneColor;
	//! Color for "critical" level.
	QtConfFile::TagScalar< QString > m_criticalColor;
	//! Color for "error" level.
	QtConfFile::TagScalar< QString > m_errorColor;
	//! Color for "warning" level.
	QtConfFile::TagScalar< QString > m_warningColor;
	//! Color for "debug" level.
	QtConfFile::TagScalar< QString > m_debugColor;
	//! Color for "info" level.
	QtConfFile::TagScalar< QString > m_infoColor;
	//! Color for deregistered sources.
	QtConfFile::TagScalar< QString > m_deregisteredColor;
	//! Color for disconected sources.
	QtConfFile::TagScalar< QString > m_disconnectedColor;
}; // class ColorForLevelTag

} /* namespace Globe */

#endif // GLOBE__COLOR_FOR_LEVEL_CFG_HPP__INCLUDED

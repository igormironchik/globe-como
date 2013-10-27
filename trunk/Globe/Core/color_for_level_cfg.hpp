
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

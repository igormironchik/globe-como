
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__COLOR_FOR_LEVEL_CFG_HPP__INCLUDED
#define GLOBE__COLOR_FOR_LEVEL_CFG_HPP__INCLUDED

// cfgfile include.
#include <cfgfile/all.hpp>


namespace Globe {

class ColorForLevel;


//
// ColorForLevelTag
//

//! Tag with corresondence between level and color.
class ColorForLevelTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	ColorForLevelTag();

	explicit ColorForLevelTag( ColorForLevel * colorForLevel );

	//! Init correspondence from configuration.
	void initColorForLevel( ColorForLevel * colorForLevel );

private:
	//! Color for "none" level.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_noneColor;
	//! Color for "critical" level.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_criticalColor;
	//! Color for "error" level.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_errorColor;
	//! Color for "warning" level.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_warningColor;
	//! Color for "debug" level.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_debugColor;
	//! Color for "info" level.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_infoColor;
	//! Color for deregistered sources.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_deregisteredColor;
	//! Color for disconected sources.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_disconnectedColor;
}; // class ColorForLevelTag

} /* namespace Globe */

#endif // GLOBE__COLOR_FOR_LEVEL_CFG_HPP__INCLUDED

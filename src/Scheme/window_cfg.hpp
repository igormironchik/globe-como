
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SCHEME__WINDOW_CFG_HPP__INCLUDED
#define GLOBE__SCHEME__WINDOW_CFG_HPP__INCLUDED

// cfgfile include.
#include <cfgfile/all.hpp>

// Globe include.
#include <Core/window_state_cfg.hpp>


namespace Globe {

namespace Scheme {

//
// WindowCfg
//

class WindowCfg {
public:
	WindowCfg();

	WindowCfg( const QString & schemeCfgFile,
		const WindowStateCfg & windowState );

	~WindowCfg();

	WindowCfg( const WindowCfg & other );

	WindowCfg & operator = ( const WindowCfg & other );

	//! \return Scheme configuration file name.
	const QString & schemeCfgFile() const;
	//! Set scheme configuration file name.
	void setSchemeCfgFile( const QString & fileName );

	//! \return Window state cfg.
	const WindowStateCfg & windowStateCfg() const;
	//! Set window state cfg.
	void setWindowStateCfg( const WindowStateCfg & cfg );

private:
	//! Scheme configuration file name.
	QString m_schemeCfgFile;
	//! Window state cfg.
	WindowStateCfg m_windowState;
}; // class WindowCfg


//
// WindowCfgTag
//

//! Tag with configuration of the scheme window.
class WindowCfgTag
	:	public cfgfile::tag_no_value_t< cfgfile::qstring_trait_t >
{
public:
	explicit WindowCfgTag( const QString & name,
		bool isMandatory = false );

	WindowCfgTag( const WindowCfg & cfg,
		const QString & name, bool isMandatory = false );

	~WindowCfgTag();

	//! \return Configuration.
	WindowCfg cfg() const;

private:
	//! Name of the channel.
	cfgfile::tag_scalar_t< QString, cfgfile::qstring_trait_t > m_schemeCfgFile;
	//! Window state cfg.
	WindowStateCfgTag m_windowState;
}; // class WindowCfgTag

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__WINDOW_CFG_HPP__INCLUDED

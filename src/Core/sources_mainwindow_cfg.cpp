
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/sources_mainwindow_cfg.hpp>


namespace Globe {

//
// SourcesMainWindowTag
//

SourcesMainWindowTag::SourcesMainWindowTag()
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "sourcesMainWindow" ), true )
	,	m_channelName( *this, QLatin1String( "channelName" ), true )
	,	m_windowState( *this, QLatin1String( "windowState" ), true )
{
}

SourcesMainWindowTag::SourcesMainWindowTag( const QString & channelName,
	const WindowStateCfg & windowState )
	:	cfgfile::tag_no_value_t< cfgfile::qstring_trait_t > (
			QLatin1String( "sourcesMainWindow" ), true )
	,	m_channelName( *this, QLatin1String( "channelName" ), true )
	,	m_windowState( windowState, *this, QLatin1String( "windowState" ), true )
{
	m_channelName.set_value( channelName );

	set_defined();
}

QString
SourcesMainWindowTag::channelName() const
{
	return m_channelName.value();
}

WindowStateCfg
SourcesMainWindowTag::windowState() const
{
	return m_windowState.cfg();
}

} /* namespace Globe */

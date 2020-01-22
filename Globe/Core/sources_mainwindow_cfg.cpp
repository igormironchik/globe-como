
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
#include <Globe/Core/sources_mainwindow_cfg.hpp>


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

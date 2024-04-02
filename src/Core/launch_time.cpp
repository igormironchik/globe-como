
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/launch_time.hpp>


namespace Globe {

//
// LaunchTime
//

LaunchTime::LaunchTime()
	:	m_launchTime( QDateTime::currentDateTime() )
{
}

LaunchTime::~LaunchTime()
{
}

LaunchTime &
LaunchTime::instance()
{
	static LaunchTime inst;

	return inst;
}

const QDateTime &
LaunchTime::launchTime() const
{
	return m_launchTime;
}

} /* namespace Globe */

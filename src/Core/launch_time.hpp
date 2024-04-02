
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__LAUNCH_TIME_HPP__INCLUDED
#define GLOBE__LAUNCH_TIME_HPP__INCLUDED

// Qt include.
#include <QDateTime>

// Globe include.
#include <Core/export.hpp>


namespace Globe {

//
// LaunchTime
//

//! Class that gives launch time of the application.
class CORE_EXPORT LaunchTime {
private:
	LaunchTime();

	~LaunchTime();

public:
	//! \return Instance of the class.
	static LaunchTime & instance();

	//! \return Launch time of the application.
	const QDateTime & launchTime() const;

private:
	Q_DISABLE_COPY( LaunchTime )

	//! Launch time
	QDateTime m_launchTime;
}; // class LaunchTime

} /* namespace Globe */

#endif // GLOBE__LAUNCH_TIME_HPP__INCLUDED

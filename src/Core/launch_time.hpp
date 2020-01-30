
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

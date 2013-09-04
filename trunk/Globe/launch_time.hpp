
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

#ifndef GLOBE__LAUNCH_TIME_HPP__INCLUDED
#define GLOBE__LAUNCH_TIME_HPP__INCLUDED

// Qt include.
#include <QDateTime>


namespace Globe {

//
// LaunchTime
//

//! Class that gives launch time of the application.
class LaunchTime {
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

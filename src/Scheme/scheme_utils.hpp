
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SCHEME__UTILS_HPP__INCLUDED
#define GLOBE__SCHEME__UTILS_HPP__INCLUDED

// Qt include.
#include <QString>

// Como include.
#include <Como/Source>


namespace Globe {

namespace Scheme {

//
// createToolTip
//

//! Create tooltip.
QString createToolTip( const QString & channelName,
	const Como::Source & s );

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__UTILS_HPP__INCLUDED

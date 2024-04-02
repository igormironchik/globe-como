
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Scheme/scheme_utils.hpp>


namespace Globe {

namespace Scheme {

//
// createToolTip
//

QString createToolTip( const QString & channelName,
	const Como::Source & s )
{
	QString res;

	res.append( QLatin1String( "<b>Channel:</b> " ) );
	res.append( channelName );
	res.append( QLatin1String( "<br><b>Type:</b> " ) );
	res.append( s.typeName() );
	res.append( QLatin1String( "<br><b>Name:</b> " ) );
	res.append( s.name() );
	res.append( QLatin1String( "<br><b>Value</b> " ) );
	res.append( s.value().toString() );

	if( !s.description().isEmpty() )
	{
		res.append( QLatin1String( "<br><b>Description:</b> " ) );
		res.append( s.description() );
	}

	return res;
}

} /* namespace Scheme */

} /* namespace Globe */


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

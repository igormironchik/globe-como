
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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

#ifndef GLOBE__SOUNDS_DISABLED_DATA_HPP__INCLUDED
#define GLOBE__SOUNDS_DISABLED_DATA_HPP__INCLUDED

// Qt include.
#include <QDateTime>
#include <QMap>
#include <QList>

// Como include.
#include <Como/Source>


namespace Globe {

//
// DisabledSoundsData
//

//! Data in the map of disabled sounds.
class DisabledSoundsData {
public:
	DisabledSoundsData();

	DisabledSoundsData( const Como::Source & source,
		const QDateTime & dt );

	explicit DisabledSoundsData( const Como::Source & source );

	DisabledSoundsData( const DisabledSoundsData & other );

	DisabledSoundsData & operator = ( const DisabledSoundsData & other );

	//! \return Como source.
	Como::Source & source();
	//! \return Como source.
	const Como::Source & source() const;

	//! \return Date & time.
	QDateTime & dateTime();
	//! \return Date & time.
	const QDateTime & dateTime() const;

	friend bool operator == ( const DisabledSoundsData & d1,
		const DisabledSoundsData & d2 );

private:
	//! Source.
	Como::Source m_source;
	//! Date & time.
	QDateTime m_dt;
}; // class DisabledSoundsData


//
// DisabledSoundsList
//

//! List of disabled sounds.
typedef QList< DisabledSoundsData > DisabledSoundsList;


//
// DisabledSoundsMap
//

//! Map of disabled sounds.
typedef QMap< QString, DisabledSoundsList > DisabledSoundsMap;

} /* namespace Globe */

#endif // GLOBE__SOUNDS_DISABLED_DATA_HPP__INCLUDED

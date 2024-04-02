
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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

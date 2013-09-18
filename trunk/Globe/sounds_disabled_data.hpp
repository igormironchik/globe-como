
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

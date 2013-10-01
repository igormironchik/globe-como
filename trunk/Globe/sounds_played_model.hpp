
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

#ifndef GLOBE__SOUNDS_PLAYED_MODEL_HPP__INCLUDED
#define GLOBE__SOUNDS_PLAYED_MODEL_HPP__INCLUDED

// Qt include.
#include <QAbstractTableModel>
#include <QScopedPointer>

// Como include.
#include <Como/Source>

// Globe include.
#include <Globe/condition.hpp>


namespace Globe {

//
// PlayedSoundsModelRecord
//

//! Record in the model of the played sounds.
class PlayedSoundsModelRecord {
public:
	PlayedSoundsModelRecord();

	PlayedSoundsModelRecord( Level level, const QString & channelName,
		const Como::Source & source );

	PlayedSoundsModelRecord( const PlayedSoundsModelRecord & other );

	PlayedSoundsModelRecord & operator = (
		const PlayedSoundsModelRecord & other );

	//! \return Level.
	Level level() const;
	//! Set level.
	void setLevel( Level l );

	//! \return Channel's name.
	const QString & channelName() const;
	//! Set channel's name.
	void setChannelName( const QString & name );

	//! \return Source.
	const Como::Source & source() const;
	//! \return Source.
	Como::Source & source();
	//! Set source.
	void setSource( const Como::Source & s );

private:
	//! Level.
	Level m_level;
	//! Channel's name.
	QString m_channelName;
	//! Source.
	Como::Source m_source;
}; // class PlayedSoundsModelRecord


//
// PlayedSoundsModel
//

class PlayedSoundsModelPrivate;

//! Model for the played sounds.
class PlayedSoundsModel
	:	public QAbstractTableModel
{
	Q_OBJECT

public:
	PlayedSoundsModel( QObject * parent = 0 );

	~PlayedSoundsModel();

	//! Add record.
	void addRecord( const PlayedSoundsModelRecord & r );

	//! \return Record for the given index.
	const PlayedSoundsModelRecord & record( const QModelIndex & index ) const;

	//! \return Count of the rows.
	int rowCount( const QModelIndex & parent = QModelIndex() ) const;
	//! \return Count of the columns.
	int columnCount( const QModelIndex & parent = QModelIndex() ) const;
	//! \return Data by the given index and role.
	QVariant data( const QModelIndex & index,
		int role = Qt::DisplayRole ) const;
	//! Set data.
	bool setData( const QModelIndex & index, const QVariant & value,
		int role = Qt::EditRole );
	//! \return Flags.
	Qt::ItemFlags flags( const QModelIndex & index ) const;
	//! \return Header data.
	QVariant headerData( int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole ) const;

private:
	Q_DISABLE_COPY( PlayedSoundsModel )

	QScopedPointer< PlayedSoundsModelPrivate > d;
}; // class PlayedSoundsModel

} /* namespace Globe */

#endif // GLOBE__SOUNDS_PLAYED_MODEL_HPP__INCLUDED

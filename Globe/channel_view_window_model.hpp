
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

#ifndef GLOBE__CHANNEL_VIEW_WINDOW_MODEL_HPP__INCLUDED
#define GLOBE__CHANNEL_VIEW_WINDOW_MODEL_HPP__INCLUDED

// Qt include.
#include <QAbstractTableModel>
#include <QScopedPointer>

// Como include.
#include <Como/Source>

// Globe include.
#include <Globe/condition.hpp>


namespace Globe {

static const int priorityColumn = 0;
static const int dateTimeColumn = 1;
static const int sourceTypeNameColumn = 2;
static const int sourceNameColumn = 3;
static const int valueColumn = 4;


//
// ChannelViewWindowModel
//

class ChannelViewWindowModelPrivate;

//! Model with Como::Source sources.
class ChannelViewWindowModel
	:	public QAbstractTableModel
{
	Q_OBJECT

public:
	ChannelViewWindowModel( QObject * parent = 0 );

	~ChannelViewWindowModel();

	//! Init model.
	void initModel( const QString & channelName );

	//! Clear model.
	void clear();

	//! Add new item.
	void addItem( const Como::Source & source, bool isRegistered );

	//! \return Como source for the given index.
	const Como::Source & source( const QModelIndex & index ) const;
	//! \return Is source registered?
	bool isRegistered( const QModelIndex & index ) const;
	//! \return Level.
	Level level( const QModelIndex & index ) const;
	//! \return Priority.
	int priority( const QModelIndex & index ) const;

	//! \return Is channel connected?
	bool isConnected() const;

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

private slots:
	//! Source updated.
	void sourceUpdated( const Como::Source & source );
	//! Source deregistered.
	void sourceDeregistered( const Como::Source & source );
	//! Channel connected.
	void connected();
	//! Channel disconnected.
	void disconnected();
	//! New source available.
	void newSource( const Como::Source & source, const QString & channelName );

private:
	Q_DISABLE_COPY( ChannelViewWindowModel )

	QScopedPointer< ChannelViewWindowModelPrivate > d;
}; // class ChannelViewWindowModel

} /* namespace Globe */

#endif // GLOBE__CHANNEL_VIEW_WINDOW_MODEL_HPP__INCLUDED


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__CHANNEL_VIEW_WINDOW_MODEL_HPP__INCLUDED
#define GLOBE__CHANNEL_VIEW_WINDOW_MODEL_HPP__INCLUDED

// Qt include.
#include <QAbstractTableModel>
#include <QScopedPointer>

// Como include.
#include <Como/Source>

// Globe include.
#include <Core/condition.hpp>


namespace Globe {

static const int priorityColumn = 0;
static const int dateTimeColumn = 1;
static const int sourceTypeNameColumn = 2;
static const int sourceNameColumn = 3;
static const int valueColumn = 4;


class Channel;


//
// ChannelViewWindowModel
//

class ChannelViewWindowModelPrivate;

//! Model with Como::Source sources.
class ChannelViewWindowModel
	:	public QAbstractTableModel
{
	Q_OBJECT

signals:
	//! Priority of the source has been changed.
	void priorityChanged();

public:
	ChannelViewWindowModel( QObject * parent = 0 );

	~ChannelViewWindowModel();

	//! \return Channel's name.
	const QString & channelName() const;

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

	QStringList mimeTypes() const;
	QMimeData * mimeData( const QModelIndexList & indexes ) const;

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
	//! Properties changed.
	void propertiesChanged();
	//! Channel removed.
	void channelRemoved( Globe::Channel * ch );

private:
	Q_DISABLE_COPY( ChannelViewWindowModel )

	QScopedPointer< ChannelViewWindowModelPrivate > d;
}; // class ChannelViewWindowModel

} /* namespace Globe */

#endif // GLOBE__CHANNEL_VIEW_WINDOW_MODEL_HPP__INCLUDED

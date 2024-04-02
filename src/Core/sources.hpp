
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SOURCES_HPP__INCLUDED
#define GLOBE__SOURCES_HPP__INCLUDED

// Qt include.
#include <QObject>

// Como include.
#include <Como/Source>


namespace Globe {

class Channel;

//
// SourcesManager.
//

class SourcesManagerPrivate;

/*!
	Sources manager. Collects information about all sources.
*/
class SourcesManager
	:	public QObject
{
	Q_OBJECT

signals:
	/*!
		New source appears.

		First parameter is Como source and the second parameter is
		channel's name.
	*/
	void newSource( const Como::Source &, const QString & );

private:
	SourcesManager( QObject * parent = 0 );

	~SourcesManager();

	static void cleanup();

public:
	//! \return Instance.
	static SourcesManager & instance();

	//! \return List of names of available channels.
	QList< QString > channelsNames() const;

	//! \return List of sources in the given channel.
	QList< Como::Source > sources( const QString & channelName ) const;

	//! \return List of registered sources in the given channel.
	QList< Como::Source > registeredSources( const QString & channelName ) const;

	//! \return List of deregistered sources in the given channel.
	QList< Como::Source > deregisteredSources( const QString & channelName ) const;

	//! Sync source. \return Was source synced?
	bool syncSource( const QString & channelName,
		Como::Source & s, bool & isRegistered );

private slots:
	//! Source updated or registered.
	void sourceUpdated( const Como::Source & source );
	//! Source deregistered.
	void sourceDeregistered( const Como::Source & source );
	//! Channel created.
	void channelCreated( Globe::Channel * channel );
	//! Channel removed.
	void channelRemoved( Globe::Channel * channel );
	//! Channel disconnected.
	void channelDisconnected();

private:
	Q_DISABLE_COPY( SourcesManager )

	QScopedPointer< SourcesManagerPrivate > d;
}; // class SourcesManager

} /* namespace Globe */

#endif // GLOBE__SOURCES_HPP__INCLUDED

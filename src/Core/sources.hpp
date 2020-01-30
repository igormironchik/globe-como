
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
	void channelCreated( Channel * channel );
	//! Channel removed.
	void channelRemoved( Channel * channel );
	//! Channel disconnected.
	void channelDisconnected();

private:
	Q_DISABLE_COPY( SourcesManager )

	QScopedPointer< SourcesManagerPrivate > d;
}; // class SourcesManager

} /* namespace Globe */

#endif // GLOBE__SOURCES_HPP__INCLUDED

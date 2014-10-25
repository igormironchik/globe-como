
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

public:
	//! \return Instance.
	static SourcesManager & instance();

	//! \return List of names of available channels.
	QList< QString > channelsNames() const;

	//! \return List of sources in the given \arg channel channel.
	QList< Como::Source > sources( const QString & channelName ) const;

	//! \return List of registered sources in the given \arg channel channel.
	QList< Como::Source > registeredSources( const QString & channelName ) const;

	//! \return List of deregistered sources in the given \arg channel channel.
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

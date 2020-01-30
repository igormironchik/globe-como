
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

#ifndef GLOBE__SOUNDS_HPP__INCLUDED
#define GLOBE__SOUNDS_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>
#include <QMediaPlayer>

// Como include.
#include <Como/Source>

// Globe include.
#include <Core/condition.hpp>
#include <Core/tool_window.hpp>
#include <Core/export.hpp>


namespace Globe {

class SoundsCfg;


//
// Sounds
//

class SoundsPrivate;

//! Sounds manager.
class CORE_EXPORT Sounds
	:	public QMainWindow
	,	public ToolWindow
{
	Q_OBJECT

private:
	Sounds( QWidget * parent = 0, Qt::WindowFlags f = 0 );

	~Sounds();

	static void cleanup();

public:
	//! \return Instance.
	static Sounds & instance();

	//! \return Tool window object.
	ToolWindowObject * toolWindowObject();

	//! Init menu.
	void initMenu( const Menu & menu );

	//! Read configuration.
	void readCfg( const QString & fileName );

	//! Save configuration.
	void saveCfg( const QString & fileName );

	//! \return Configuration.
	const SoundsCfg & cfg() const;
	//! Set configuration.
	void setCfg( const SoundsCfg & c );

public slots:
	//! Play sound.
	void playSound( Level level, const Como::Source & source,
		const QString & channelName );

private slots:
	//! Player state changed.
	void playerStateChanged( QMediaPlayer::State state );

protected:
	void closeEvent( QCloseEvent * event );

private:
	//! Init.
	void init();
	//! Check is sound enabled for the given level.
	bool isSoundEnabled( Level level );
	//! \return Sound file for the given level.
	const QString & soundFileName( Level level );

private:
	Q_DISABLE_COPY( Sounds )

	QScopedPointer< SoundsPrivate > d;
}; // class Sounds

} /* namespace Globe */

#endif // GLOBE__SOUNDS_HPP__INCLUDED


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

#ifndef GLOBE__SOUNDS_HPP__INCLUDED
#define GLOBE__SOUNDS_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Como include.
#include <Como/Source>

// Globe include.
#include <Globe/condition.hpp>
#include <Globe/tool_window.hpp>


namespace Globe {

class MainWindow;


//
// Sounds
//

class SoundsPrivate;

//! Sounds manager.
class Sounds
	:	public QMainWindow
	,	public ToolWindow
{
	Q_OBJECT

private:
	Sounds( QWidget * parent = 0, Qt::WindowFlags f = 0 );

	~Sounds();

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

public slots:
	//! Play sound.
	void playSound( Level level, const Como::Source & source,
		const QString & channelName );

protected:
	void closeEvent( QCloseEvent * event );

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( Sounds )

	QScopedPointer< SoundsPrivate > d;
}; // class Sounds

} /* namespace Globe */

#endif // GLOBE__SOUNDS_HPP__INCLUDED

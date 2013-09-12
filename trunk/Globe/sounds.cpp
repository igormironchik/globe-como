
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

// Globe include.
#include <Globe/sounds.hpp>
#include <Globe/globe_menu.hpp>
#include <Globe/tool_window_object.hpp>

// Qt include.
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QCloseEvent>


namespace Globe {

//
// SoundsPrivate
//

class SoundsPrivate {
public:
	SoundsPrivate()
		:	m_toolWindowObject( 0 )
	{
	}

	//! Tool window object.
	ToolWindowObject * m_toolWindowObject;
}; // class SoundsPrivate


//
// Sounds
//

Sounds::Sounds( QWidget * parent, Qt::WindowFlags f )
	:	QMainWindow( parent, f )
	,	d( new SoundsPrivate )
{
	init();
}

Sounds::~Sounds()
{
}

Sounds &
Sounds::instance()
{
	static Sounds inst;

	return inst;
}

ToolWindowObject *
Sounds::toolWindowObject()
{
	return d->m_toolWindowObject;
}

void
Sounds::initMenu( const Menu & menu )
{
	menuBar()->addMenu( menu.fileMenu() );

	QMenu * toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );

	foreach( ToolWindowObject * obj, menu.toolWindows() )
		if( obj != d->m_toolWindowObject )
			toolsMenu->addAction( obj->menuEntity() );

	menuBar()->addMenu( menu.settingsMenu() );
}

void
Sounds::playSound( Level level, const Como::Source & source )
{

}

void
Sounds::closeEvent( QCloseEvent * event )
{
	hide();

	event->accept();
}

void
Sounds::init()
{
	QAction * showAction = new QAction( tr( "S&ounds" ), this );
	d->m_toolWindowObject = new ToolWindowObject( showAction, this, this );
}

} /* namespace Globe */


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

#ifndef GLOBE__SCHEME__WINDOW_HPP__INCLUDED
#define GLOBE__SCHEME__WINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Globe/Core/with_menu.hpp>

#include <Globe/Scheme/window_cfg.hpp>


namespace Globe {

namespace Scheme {

//
// Window
//

class WindowPrivate;

//! Window with scheme.
class Window
	:	public QMainWindow
	,	public WithMenu
{
	Q_OBJECT

public:
	Window( QWidget * parent = 0, Qt::WindowFlags f = 0 );

	~Window();

	//! Init menu.
	void initMenu( const Menu & menu );

	//! \return Window's configuration.
	WindowCfg cfg() const;
	//! Set window's configuration.
	void setCfg( const WindowCfg & cfg );

public slots:
	//! Load scheme configuration.
	void loadScheme( const QString & fileName );
	//! Create new scheme.
	void createNewScheme( const QString & fileName );

protected:
	void closeEvent( QCloseEvent * event );

private:
	//! Init.
	void init();
	//! Set window title.
	void setTitle( const QString & title );

private:
	Q_DISABLE_COPY( Window )

	QScopedPointer< WindowPrivate > d;
}; // class Window

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__WINDOW_HPP__INCLUDED

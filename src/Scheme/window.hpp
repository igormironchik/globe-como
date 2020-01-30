
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

#ifndef GLOBE__SCHEME__WINDOW_HPP__INCLUDED
#define GLOBE__SCHEME__WINDOW_HPP__INCLUDED

// Qt include.
#include <QMainWindow>
#include <QScopedPointer>

// Globe include.
#include <Core/with_menu.hpp>

#include <Scheme/window_cfg.hpp>


namespace Globe {

namespace Scheme {

class SchemeCfg;


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

signals:
	//! Scheme changed.
	void schemeChanged();

public:
	Window( QWidget * parent = 0, Qt::WindowFlags f = 0 );

	~Window();

	//! Init menu.
	void initMenu( const Menu & menu );

	//! \return Window's configuration.
	WindowCfg cfg() const;
	//! Set window's configuration.
	void setCfg( const WindowCfg & cfg );

	//! \return Scheme configuration.
	SchemeCfg schemeCfg() const;

	//! \return Name of the scheme.
	const QString & schemeName() const;

	//! \return Name of the configuration file.
	const QString & cfgFile() const;

public slots:
	//! Load scheme configuration.
	void loadScheme( const QString & fileName );
	//! Create new scheme.
	void createNewScheme( const QString & fileName );
	//! Save scheme.
	void saveScheme();
	//! Load scheme.
	void loadScheme( const SchemeCfg & cfg, bool editing = false );

private slots:
	//! Edit mode changed.
	void editMode();
	//! Set select edit mode.
	void selectEditMode();
	//! Set new source edit mode.
	void sourceEditMode();
	//! Set new text block edit mode.
	void textBlockEditMode();
	//! Add new aggregate.
	void aggregateEditMode();
	//! Update windows menu.
	void updateWindowsMenu( QWidget * );

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

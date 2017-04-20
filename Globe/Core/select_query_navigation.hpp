
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

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

#ifndef GLOBE__SELECT_QUERY_NAVIGATION_HPP__INCLUDED
#define GLOBE__SELECT_QUERY_NAVIGATION_HPP__INCLUDED

// Qt include.
#include <QWidget>
#include <QScopedPointer>

// Globe include.
#include <Globe/Core/export.hpp>


namespace Globe {

//
// SelectQueryNavigation
//

class SelectQueryNavigationPrivate;

//! Navigation buttons throug the SELECT query.
class CORE_EXPORT SelectQueryNavigation
	:	public QWidget
{
	Q_OBJECT

signals:
	//! Execute button clicked.
	void executeButtonClicked();
	//! "Go to next page" button clicked.
	void goToNextPageButtonClicked();
	//! "Go to previous page" button clicked.
	void goToPreviousPageButtonClicked();
	//! "Go to end page" button clicked.
	void goToEndPageButtonClicked();
	//! "Go to start page" button clicked.
	void goToStartPageButtonClicked();

public:
	SelectQueryNavigation( QWidget * parent = 0, Qt::WindowFlags f = 0 );

	~SelectQueryNavigation();

public slots:
	//! Disable/enable "previous" buttons.
	void enablePreviousButtons( bool on = true );
	//! Disable/enable "next" buttons.
	void enableNextButtons( bool on = true );

private slots:
	//! Execute button clicked.
	void execute();
	//! "Go to next page" button clicked.
	void goToNextPage();
	//! "Go to previous page" button clicked.
	void goToPreviousPage();
	//! "Go to end page" button clicked.
	void goToEndPage();
	//! "Go to start page" button clicked.
	void goToStartPage();

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( SelectQueryNavigation )

	QScopedPointer< SelectQueryNavigationPrivate > d;
}; // class SelectQueryNavigation

} /* namespace Globe */

#endif // GLOBE__SELECT_QUERY_NAVIGATION_HPP__INCLUDED


/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__SELECT_QUERY_NAVIGATION_HPP__INCLUDED
#define GLOBE__SELECT_QUERY_NAVIGATION_HPP__INCLUDED

// Qt include.
#include <QWidget>
#include <QScopedPointer>

// Globe include.
#include <Core/export.hpp>


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
	SelectQueryNavigation( QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );

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

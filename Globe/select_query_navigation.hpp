
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

#ifndef GLOBE__SELECT_QUERY_NAVIGATION_HPP__INCLUDED
#define GLOBE__SELECT_QUERY_NAVIGATION_HPP__INCLUDED

// Qt include.
#include <QWidget>
#include <QScopedPointer>


namespace Globe {

//
// SelectQueryNavigation
//

class SelectQueryNavigationPrivate;

//! Navigation buttons throug the SELECT query.
class SelectQueryNavigation
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

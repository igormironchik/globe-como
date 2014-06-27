
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
#include <Globe/Core/select_query_navigation.hpp>

#include "ui_select_query_navigation.h"

// Qt include.
#include <QToolButton>
#include <QCommandLinkButton>


namespace Globe {

//
// SelectQueryNavigationPrivate
//

class SelectQueryNavigationPrivate {
public:
	SelectQueryNavigationPrivate()
	{
	}

	//! Ui.
	Ui::SelectQueryNavigation m_ui;
}; // class SelectQueryNavigationPrivate


//
// SelectQueryNavigation
//

SelectQueryNavigation::SelectQueryNavigation( QWidget * parent,
	Qt::WindowFlags f )
	:	QWidget( parent, f )
	,	d( new SelectQueryNavigationPrivate )
{
	init();
}

SelectQueryNavigation::~SelectQueryNavigation()
{
}

void
SelectQueryNavigation::enablePreviousButtons( bool on )
{
	d->m_ui.m_prev->setEnabled( on );
	d->m_ui.m_toBegin->setEnabled( on );
}

void
SelectQueryNavigation::enableNextButtons( bool on )
{
	d->m_ui.m_next->setEnabled( on );
	d->m_ui.m_toEnd->setEnabled( on );
}

void
SelectQueryNavigation::execute()
{
	emit executeButtonClicked();
}

void
SelectQueryNavigation::goToNextPage()
{
	emit goToNextPageButtonClicked();
}

void
SelectQueryNavigation::goToPreviousPage()
{
	emit goToPreviousPageButtonClicked();
}

void
SelectQueryNavigation::goToEndPage()
{
	emit goToEndPageButtonClicked();
}

void
SelectQueryNavigation::goToStartPage()
{
	emit goToStartPageButtonClicked();
}

void
SelectQueryNavigation::init()
{
	d->m_ui.setupUi( this );

	connect( d->m_ui.m_exec, &QCommandLinkButton::clicked,
		this, &SelectQueryNavigation::execute );

	connect( d->m_ui.m_toBegin, &QToolButton::clicked,
		this, &SelectQueryNavigation::goToStartPage );

	connect( d->m_ui.m_prev, &QToolButton::clicked,
		this, &SelectQueryNavigation::goToPreviousPage );

	connect( d->m_ui.m_next, &QToolButton::clicked,
		this, &SelectQueryNavigation::goToNextPage );

	connect( d->m_ui.m_toEnd, &QToolButton::clicked,
		this, &SelectQueryNavigation::goToEndPage );
}

} /* namespace Globe */

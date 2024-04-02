
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/select_query_navigation.hpp>

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

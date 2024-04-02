
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__CORE__EXPORT_HPP__INCLUDED
#define GLOBE__CORE__EXPORT_HPP__INCLUDED

// Qt include.
#include <QtGlobal>

#ifdef GLOBE_CORE
	#define CORE_EXPORT Q_DECL_EXPORT
#else
	#define CORE_EXPORT Q_DECL_IMPORT
#endif

#endif // GLOBE__CORE__EXPORT_HPP__INCLUDED

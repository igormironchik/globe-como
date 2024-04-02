
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/word_wrap_delegate.hpp>

// Qt include.
#include <QHeaderView>
#include <QPainter>


namespace Globe {

//
// WordWrapItemDelegate
//

WordWrapItemDelegate::WordWrapItemDelegate( QTreeView * parent )
	:	QStyledItemDelegate( parent )
	,	m_parent( parent )
{
}

QSize
WordWrapItemDelegate::sizeHint( const QStyleOptionViewItem & option,
	const QModelIndex & index ) const
{
	return option.fontMetrics.boundingRect(
		QRect( 0, 0, m_parent->header()->sectionSize( index.column() ), 0 ),
		Qt::AlignLeft | Qt::TextWordWrap,
		index.data( Qt::DisplayRole ).toString() ).size();
}

void
WordWrapItemDelegate::paint( QPainter * painter,
	const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
	QStyledItemDelegate::paint( painter, option, index );

	painter->drawText( option.rect,
		Qt::AlignLeft | Qt::TextWordWrap | Qt::AlignVCenter,
		index.data( Qt::DisplayRole ).toString() );
}

void
WordWrapItemDelegate::initStyleOption( QStyleOptionViewItem * option,
	const QModelIndex & index ) const
{
	QStyledItemDelegate::initStyleOption( option, index );
	option->text = QString();
}

} /* namespace Globe */

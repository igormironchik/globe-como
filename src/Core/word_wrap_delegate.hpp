
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE_WORD_WRAP_DELEGATE_HPP_INCLUDED
#define GLOBE_WORD_WRAP_DELEGATE_HPP_INCLUDED

// Qt include.
#include <QStyledItemDelegate>
#include <QTreeView>


namespace Globe {

//! Item delegate for word wrapping.
class WordWrapItemDelegate final
	:	public QStyledItemDelegate
{
public:
	WordWrapItemDelegate( QTreeView * parent = nullptr );

	QSize sizeHint( const QStyleOptionViewItem & option,
		const QModelIndex & index ) const override;
	void paint( QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index) const override;

protected:
	void initStyleOption( QStyleOptionViewItem * option,
		const QModelIndex & index ) const override;

private:
  QTreeView * m_parent;
}; // class WordWrapItemDelegate

} /* namespace Globe */

#endif // GLOBE_WORD_WRAP_DELEGATE_HPP_INCLUDED

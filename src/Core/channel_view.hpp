
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__CHANNEL_VIEW_HPP__INCLUDED
#define GLOBE__CHANNEL_VIEW_HPP__INCLUDED

// Qt include.
#include <QTreeView>
#include <QScopedPointer>

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
QT_END_NAMESPACE


namespace Globe {

class ChannelViewWindowModel;


//
// ChannelView
//

class ChannelViewPrivate;

//! View with channel's sources.
class ChannelView
	:	public QTreeView
{
	Q_OBJECT

public:
	ChannelView( QWidget * parent = 0 );

	~ChannelView();

	//! \return Model.
	ChannelViewWindowModel * model();

	//! \return Sort model.
	QSortFilterProxyModel * sortModel();

	//! \return Action for copy.
	QAction * copyAction() const;

	//! \return Action for selecting all rows.
	QAction * selectAllAction() const;

	//! \return Action for turning on/off coloring of view.
	QAction * fillColorAction() const;

protected slots:
	//! Selection changed.
	void selectionChanged( const QItemSelection & selected,
		const QItemSelection & deselected );

private slots:
	//! Select all.
	void selectAllImplementation();
	//! Copy.
	void copyImplementation();
	//! Fill with color changed.
	void fillWithColorChanged();
	//! Color for level correspondence changed.
	void colorForLevelChanged();
	//! Add properties.
	void addProperties();
	//! Edit properties.
	void editProperties();
	//! Delete properties.
	void deleteProperties();
	//! Promote properties.
	void promoteProperties();
	//! Section resized.
	void sectionResized( int section, int, int );
	//! Priority of the source has been changed.
	void priorityChanged();

protected:
	void drawRow( QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index ) const;
	void contextMenuEvent( QContextMenuEvent * event );

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( ChannelView )

	QScopedPointer< ChannelViewPrivate > d;
}; // class ChannelView

} /* namespace Globe */

#endif // GLOBE__CHANNEL_VIEW_HPP__INCLUDED

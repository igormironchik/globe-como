
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2016 Igor Mironchik

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

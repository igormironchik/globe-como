
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

protected:
	void drawRow( QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index ) const;

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( ChannelView )

	QScopedPointer< ChannelViewPrivate > d;
}; // class ChannelView

} /* namespace Globe */

#endif // GLOBE__CHANNEL_VIEW_HPP__INCLUDED

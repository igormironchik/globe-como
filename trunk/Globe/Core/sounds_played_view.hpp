
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

#ifndef GLOBE__SOUNDS_PLAYED_VIEW_HPP__INCLUDED
#define GLOBE__SOUNDS_PLAYED_VIEW_HPP__INCLUDED

// Qt include.
#include <QTreeView>
#include <QScopedPointer>


namespace Globe {

class PlayedSoundsModel;


//
// PlayedSoundsView
//

class PlayedSoundsViewPrivate;

//! View with played sounds.
class PlayedSoundsView
	:	public QTreeView
{
	Q_OBJECT

public:
	PlayedSoundsView( QWidget * parent = 0 );

	~PlayedSoundsView();

	//! \return Model.
	PlayedSoundsModel * model();

private slots:
	//! Disable sound for the selected item.
	void disableSound();

protected:
	//! Context menu event.
	void contextMenuEvent( QContextMenuEvent * event );
	//! Draw row.
	void drawRow( QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index ) const;

private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( PlayedSoundsView )

	QScopedPointer< PlayedSoundsViewPrivate > d;
}; // class PlayedSoundsView

} /* namespace Globe */

#endif // GLOBE__SOUNDS_PLAYED_VIEW_HPP__INCLUDED
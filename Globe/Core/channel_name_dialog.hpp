
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

#ifndef GLOBE__CHANNEL_NAME_DIALOG_HPP__INCLUDED
#define GLOBE__CHANNEL_NAME_DIALOG_HPP__INCLUDED

// Qt include.
#include <QDialog>
#include <QScopedPointer>


namespace Globe {

//
// ChannelNameDialog
//

class ChannelNameDialogPrivate;

//! Dialog for selecting channel's name.
class ChannelNameDialog
	:	public QDialog
{
	Q_OBJECT

public:
	ChannelNameDialog( QString & result,
		const QStringList & names,
		QWidget * parent = 0, Qt::WindowFlags f = 0 );

	~ChannelNameDialog();

private slots:
	//! Accepted.
	void accepted();
	//! Current index changed.
	void currentIndexChanged( int index );

private:
	//! Init.
	void init( const QStringList & names );

private:
	Q_DISABLE_COPY( ChannelNameDialog )

	QScopedPointer< ChannelNameDialogPrivate > d;
}; // class ChannelNameDialog

} /* namespace Globe */

#endif // GLOBE__CHANNEL_NAME_DIALOG_HPP__INCLUDED
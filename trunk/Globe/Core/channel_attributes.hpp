
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

#ifndef GLOBE__CHANNEL_ATTRIBUTES_HPP__INCLUDED
#define GLOBE__CHANNEL_ATTRIBUTES_HPP__INCLUDED

// Qt include.
#include <QDialog>
#include <QScopedPointer>

QT_BEGIN_NAMESPACE
class QHostAddress;
QT_END_NAMESPACE


namespace Globe {

class ChannelAttributesPrivate;


//
// ChannelAttributes
//

//! Attributes of the channel.
class ChannelAttributes {
public:
	ChannelAttributes();
	~ChannelAttributes();

	//! \return Name of the channel.
	const QString & name() const;
	//! Set name of the channel.
	void setName( const QString & name );

	//! \return Address of the channel.
	const QHostAddress & address() const;
	//! Set address of the channel.
	void setAddress( const QHostAddress & addr );

	//! \return Port of the channel.
	quint16 port() const;
	//! Set port of the channel.
	void setPort( quint16 p );

private:
	Q_DISABLE_COPY( ChannelAttributes )

	QScopedPointer< ChannelAttributesPrivate > d;
}; // class ChannelAttributes


class ChannelAttributesDialogPrivate;


//
// ChannelAttributesDialog
//

//! Dialog with channel's attributes.
class ChannelAttributesDialog
	:	public QDialog
{
	Q_OBJECT

public:
	explicit ChannelAttributesDialog( ChannelAttributes & attributes,
		QWidget * parent = 0, Qt::WindowFlags f = 0 );

	~ChannelAttributesDialog();

private slots:
	//! Name edited.
	void nameEdited( const QString & text );
	//! IP address edited.
	void ipEdited( const QString & text );
	//! Port edited.
	void portEdited( int val );
	//! Accepted.
	void accepted();
	//! Check fields.
	void checkFields();


private:
	//! Init.
	void init();

private:
	Q_DISABLE_COPY( ChannelAttributesDialog )

	QScopedPointer< ChannelAttributesDialogPrivate > d;
}; // class ChannelAttributesDialog

} /* namespace Globe */

#endif // GLOBE__CHANNEL_ATTRIBUTES_HPP__INCLUDED

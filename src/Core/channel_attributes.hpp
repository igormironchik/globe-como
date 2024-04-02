
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef GLOBE__CHANNEL_ATTRIBUTES_HPP__INCLUDED
#define GLOBE__CHANNEL_ATTRIBUTES_HPP__INCLUDED

// Qt include.
#include <QDialog>
#include <QScopedPointer>


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
	const QString & address() const;
	//! Set address of the channel.
	void setAddress( const QString & addr );

	//! \return Port of the channel.
	quint16 port() const;
	//! Set port of the channel.
	void setPort( quint16 p );

	//! \return Type of the channel.
	const QString & type() const;
	//! Set type of the channel.
	void setType( const QString & t );

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
	ChannelAttributesDialog( ChannelAttributes & attributes,
		const QStringList & types,
		QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags() );

	~ChannelAttributesDialog();

private slots:
	//! Name edited.
	void nameEdited( const QString & text );
	//! IP address edited.
	void ipEdited( const QString & text );
	//! Port edited.
	void portEdited( int val );
	//! Accepted.
	void ok();
	//! Check fields.
	void checkFields();
	//! Check IPv4?
	void checkIPv4Checked( int state );


private:
	//! Init.
	void init( const QStringList & types );

private:
	Q_DISABLE_COPY( ChannelAttributesDialog )

	QScopedPointer< ChannelAttributesDialogPrivate > d;
}; // class ChannelAttributesDialog

} /* namespace Globe */

#endif // GLOBE__CHANNEL_ATTRIBUTES_HPP__INCLUDED


/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef COMO__MESSAGES_HPP__INCLUDED
#define COMO__MESSAGES_HPP__INCLUDED

// Como include.
#include <Como/Source>

// Qt include.
#include <QSharedPointer>
#include <QByteArray>


namespace Como {

//
// Message
//

//! Base class of the message in Como protocol.
class Message {
public:
	virtual ~Message() = 0;

	//! \return Code (type) of the message.
	virtual quint16 type() const = 0;

	//! Serialize message.
	virtual QSharedPointer< QByteArray > serialize() const = 0;

	//! Deserialize message.
	virtual bool deserialize( const QByteArray & data ) = 0;
}; // class Message


//
// GetListOfSourcesMessage
//

/*!
	If ServerSocket recives this type of message then
	he send out list of all available sources. Each source
	will send out in separate messages.
*/
class GetListOfSourcesMessage
	:	public Message
{
public:
	//! Type of the  message.
	static const quint16 messageType = 0x0001;

	virtual ~GetListOfSourcesMessage();

	//! \return Code (type) of the message.
	virtual quint16 type() const;

	//! Serialize message.
	virtual QSharedPointer< QByteArray > serialize() const;

	//! Deserialize message.
	virtual bool deserialize( const QByteArray & data );
}; // class GetListOfSourcesMessage


//
// SourceMessage
//

/*!
	This is response to the GetListOfSourcesMessage
	message. And this type of messages used to inform
	ClientSocket about changes in the value of the source.
*/
class SourceMessage
	:	public Message
{
public:
	//! Type of the  message.
	static const quint16 messageType = 0x0002;

	SourceMessage();
	explicit SourceMessage( const Source & s );

	virtual ~SourceMessage();

	//! \return Source.
	const Source & source() const;

	//! \return Code (type) of the message.
	virtual quint16 type() const;

	//! Serialize message.
	virtual QSharedPointer< QByteArray > serialize() const;

	//! Deserialize message.
	virtual bool deserialize( const QByteArray & data );

private:
	//! Source.
	Source m_source;
}; // class SourceMessage


//
// DeinitSourceMessage
//

/*!
	This is message about deinitialization of the source.
*/
class DeinitSourceMessage
	:	public Message
{
public:
	//! Type of the  message.
	static const quint16 messageType = 0x0003;

	DeinitSourceMessage();
	explicit DeinitSourceMessage( const Source & s );

	virtual ~DeinitSourceMessage();

	//! \return Source.
	const Source & source() const;

	//! \return Code (type) of the message.
	virtual quint16 type() const;

	//! Serialize message.
	virtual QSharedPointer< QByteArray > serialize() const;

	//! Deserialize message.
	virtual bool deserialize( const QByteArray & data );

private:
	//! Source.
	Source m_source;
}; // class DeinitSourceMessage

} /* namespace Como */

#endif // COMO__MESSAGES_HPP__INCLUDED

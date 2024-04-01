
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 Igor Mironchik

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

#ifndef COMO__PROTOCOL_HPP__INCLUDED
#define COMO__PROTOCOL_HPP__INCLUDED

// Qt include.
#include <QSharedPointer>
#include <QString>

// C++ include.
#include <stdexcept>


QT_BEGIN_NAMESPACE
class QByteArray;
QT_END_NAMESPACE


namespace Como {

class Message;

//
// ProtocolException
//

//! Exception in protocol.
class ProtocolException
	:	public std::runtime_error
{
public:
	explicit ProtocolException( const QString & what );
	virtual ~ProtocolException() noexcept;

	//! \return Reason of the exception.
	const QString & whatAsQString() const noexcept;

private:
	//! Reason of the exception.
	QString m_what;
}; // class ProtocolException


//
// GarbageReceivedException
//

//! This exception throws when garbage received.
class GarbageReceivedException
	:	public ProtocolException
{
public:
	GarbageReceivedException();
	virtual ~GarbageReceivedException() noexcept;
}; // class GarbageReceivedException


//
// NotEnoughDataReceivedException
//

//! This exception throws when not enough data to parse message in the buffer.
class NotEnoughDataReceivedException
	:	public ProtocolException
{
public:
	NotEnoughDataReceivedException();
	virtual ~NotEnoughDataReceivedException() noexcept;
}; // class NotEnoughDataReceivedException


//
// Protocol
//

//! Protocol for exchanging messages between server and client.
class Protocol {
public:
	/*!
		Write message.

		\return Data to transfer over TCP/IP network.
	*/
	static QSharedPointer< QByteArray > writeMessage(
		//! Message to be written to.
		const Message & msg );

	/*!
		Read message.

		Can throw exceptions: ProtocolException
		and GarbageReceivedException.
	*/
	static QSharedPointer< Message > readMessage(
		//! Data to read message from.
		const QByteArray & data,
		//! Actual count of bytes that were read from.
		int & bytesRead );
}; // class Protocol

} /* namespace Como */

#endif // COMO__PROTOCOL_HPP__INCLUDED

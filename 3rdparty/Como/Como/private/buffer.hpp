
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef COMO__BUFFER_HPP__INCLUDED
#define COMO__BUFFER_HPP__INCLUDED

// Qt include.
#include <QByteArray>


namespace Como {

//
// Buffer
//

//! Buffer of the ClientSocket.
class Buffer {
public:
	Buffer();

	//! \return Data of the buffer.
	const QByteArray & data() const;

	//! Write data to the end of the buffer.
	void write( const QByteArray & data );

	//! Remove first bytes from the beginning of the buffer.
	void remove( int bytes );

	//! Clear the buffer.
	void clear();

	//! Is buffer empty?
	bool isEmpty() const;

	//! \return Size of the buffer.
	int size() const;

private:
	//! Data.
	QByteArray m_data;
}; // class Buffer

} /* namespace Como */

#endif // COMO__BUFFER_HPP__INCLUDED

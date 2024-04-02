
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Como include.
#include <Como/private/Buffer>


namespace Como {

//
// Buffer
//

Buffer::Buffer()
{
}

const QByteArray &
Buffer::data() const
{
	return m_data;
}

void
Buffer::write( const QByteArray & data )
{
	m_data.append( data );
}

void
Buffer::remove( int bytes )
{
	m_data.remove( 0, bytes );
}

void
Buffer::clear()
{
	m_data.clear();
}

bool
Buffer::isEmpty() const
{
	return m_data.isEmpty();
}

int
Buffer::size() const
{
	return m_data.size();
}

} /* namespace Como */

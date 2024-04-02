
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Como include.
#include <Como/private/Messages>

// Qt include.
#include <QDataStream>
#include <QIODevice>


namespace Como {

//
// Message
//

Message::~Message()
{
}


//
// GetListOfSourcesMessage
//

GetListOfSourcesMessage::~GetListOfSourcesMessage()
{
}

quint16
GetListOfSourcesMessage::type() const
{
	return messageType;
}

QSharedPointer< QByteArray >
GetListOfSourcesMessage::serialize() const
{
	return QSharedPointer< QByteArray > ( new QByteArray );
}

bool
GetListOfSourcesMessage::deserialize( const QByteArray & data )
{
	Q_UNUSED( data )

	return true;
}

namespace /* anonymous */ {

//
// serializeSource
//

void
serializeSource( QDataStream & to, const Source & source )
{
	to << (quint16) source.type();
	to << source.name();
	to << source.typeName();
	to << source.dateTime();
	to << source.description();
	to << source.value();
} // serializeSource


//
// deserializeSource
//

bool
deserializeSource( QDataStream & from, Source & source )
{
	quint16 t;
	from >> t;
	if( from.status() != QDataStream::Ok )
		return false;

	source.setType( (Source::Type) t );

	QString name;
	from >> name;
	if( from.status() != QDataStream::Ok )
		return false;

	source.setName( name );

	QString typeName;
	from >> typeName;
	if( from.status() != QDataStream::Ok )
		return false;

	source.setTypeName( typeName );

	QDateTime dt;
	from >> dt;
	if( from.status() != QDataStream::Ok )
		return false;

	source.setDateTime( dt );

	QString desc;
	from >> desc;
	if( from.status() != QDataStream::Ok )
		return false;

	source.setDescription( desc );

	QVariant value;
	from >> value;
	if( from.status() != QDataStream::Ok )
		return false;

	source.setValue( value );

	return true;
} // deserializeSource

} /* namespace anonymous */


//
// SourceMessage
//

SourceMessage::SourceMessage()
{
}

SourceMessage::SourceMessage( const Source & s )
	:	m_source( s )
{
}

SourceMessage::~SourceMessage()
{
}

const Source &
SourceMessage::source() const
{
	return m_source;
}

quint16
SourceMessage::type() const
{
	return messageType;
}

QSharedPointer< QByteArray >
SourceMessage::serialize() const
{
	QSharedPointer< QByteArray > data =
		QSharedPointer< QByteArray > ( new QByteArray );

	QDataStream dataStream( data.data(), QIODevice::WriteOnly );
	dataStream.setVersion( QDataStream::Qt_4_0 );

	serializeSource( dataStream, m_source );

	return data;
}

bool
SourceMessage::deserialize( const QByteArray & data )
{
	QDataStream dataStream( data );
	dataStream.setVersion( QDataStream::Qt_4_0 );

	if( !deserializeSource( dataStream, m_source ) )
		return false;

	return true;
}


//
// DeinitSourceMessage
//

DeinitSourceMessage::DeinitSourceMessage()
{
}

DeinitSourceMessage::DeinitSourceMessage( const Source & s )
	:	m_source( s )
{
}

DeinitSourceMessage::~DeinitSourceMessage()
{
}

const Source &
DeinitSourceMessage::source() const
{
	return m_source;
}

quint16
DeinitSourceMessage::type() const
{
	return messageType;
}

QSharedPointer< QByteArray >
DeinitSourceMessage::serialize() const
{
	QSharedPointer< QByteArray > data =
		QSharedPointer< QByteArray > ( new QByteArray );

	QDataStream dataStream( data.data(), QIODevice::WriteOnly );
	dataStream.setVersion( QDataStream::Qt_4_0 );

	serializeSource( dataStream, m_source );

	return data;
}

bool
DeinitSourceMessage::deserialize( const QByteArray & data )
{
	QDataStream dataStream( data );
	dataStream.setVersion( QDataStream::Qt_4_0 );

	if( !deserializeSource( dataStream, m_source ) )
		return false;

	return true;
}

} /* namespace Como */

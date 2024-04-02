
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Como include.
#include <Como/Source>
#include <Como/ServerSocket>


namespace Como {


//
// Source
//

Source::Source()
	:	m_type( Int )
	,	m_serverSocket( Q_NULLPTR )
	,	m_dateTime( QDateTime::currentDateTime() )
	,	m_value( QVariant( (int) 0 ) )
{
}

Source::Source( Type type, const QString & name,
	const QString & typeName,
	const QVariant & value,
	const QString & desc,
	ServerSocket * serverSocket )
	:	m_type( type )
	,	m_name( name )
	,	m_typeName( typeName )
	,	m_serverSocket( serverSocket )
	,	m_dateTime( QDateTime::currentDateTime() )
	,	m_desc( desc )
	,	m_value( value )
{
	initSource();
}

Source::~Source()
{
	deinitSource();
}

Source::Source( const Source & other )
	:	m_type( other.type() )
	,	m_name( other.name() )
	,	m_typeName( other.typeName() )
	,	m_serverSocket( Q_NULLPTR )
	,	m_dateTime( other.dateTime() )
	,	m_desc( other.description() )
	,	m_value( other.value() )
{
}

Source &
Source::operator = ( const Source & other )
{
	if( this != &other )
	{
		m_type = other.type();
		m_name = other.name();
		m_typeName = other.typeName();
		m_serverSocket = Q_NULLPTR;
		m_dateTime = other.dateTime();
		m_desc = other.description();
		m_value = other.value();
	}

	return *this;
}

void
Source::initSource()
{
	if( m_serverSocket )
		m_serverSocket->initSource( *this );
}

void
Source::deinitSource()
{
	if( m_serverSocket )
		m_serverSocket->deinitSource( *this );
}

const QVariant &
Source::value() const
{
	return m_value;
}


void
Source::setValue( const QVariant & v )
{
	m_value = v;

	m_dateTime = QDateTime::currentDateTime();

	if( m_serverSocket )
		m_serverSocket->updateSource( *this );
}

const QDateTime &
Source::dateTime() const
{
	return m_dateTime;
}

void
Source::setDateTime( const QDateTime & dt )
{
	m_dateTime = dt;

	if( m_serverSocket )
		m_serverSocket->updateSource( *this );
}

Source::Type
Source::type() const
{
	return m_type;
}

void
Source::setType( Type t )
{
	m_type = t;
}

const QString &
Source::name() const
{
	return m_name;
}

void
Source::setName( const QString & name )
{
	m_name = name;
}

const QString &
Source::typeName() const
{
	return m_typeName;
}

void
Source::setTypeName( const QString & typeName )
{
	m_typeName = typeName;
}

const QString &
Source::description() const
{
	return m_desc;
}

void
Source::setDescription( const QString & desc )
{
	m_desc = desc;
}

ServerSocket *
Source::serverSocket() const
{
	return m_serverSocket;
}

void
Source::setServerSocket( ServerSocket * socket )
{
	deinitSource();

	m_serverSocket = socket;

	initSource();
}

bool operator == ( const Source & s1, const Source & s2 )
{
	return ( s1.name() == s2.name() &&
		s1.typeName() == s2.typeName() );
}

bool operator != ( const Source & s1, const Source & s2 )
{
	return ( s1.name() != s2.name() ||
		s1.typeName() != s2.typeName() );
}

} /* namespace Como */

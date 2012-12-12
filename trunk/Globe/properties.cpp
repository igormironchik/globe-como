
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

// Globe include.
#include <Globe/properties.hpp>
#include <Globe/utils.hpp>
#include <Globe/properties_model.hpp>
#include <Globe/properties_cfg.hpp>
#include <Globe/window_state_cfg.hpp>

#include "ui_properties_mainwindow.h"

// Qt include.
#include <QtCore/QFile>
#include <QtCore/QDateTime>
#include <QtGui/QSortFilterProxyModel>
#include <QtGui/QMessageBox>
#include <QtGui/QCloseEvent>
#include <QtGui/QApplication>

// QtConfFile include.
#include <QtConfFile/Utils>


namespace Globe {

//
// Properties
//

Properties::Properties()
	:	m_priority( 0 )
{
}

Properties::Properties( const Properties & other )
	:	m_priority( other.priority() )
	,	m_conditions( other.m_conditions )
{
}

Properties &
Properties::operator = ( const Properties & other )
{
	if( this != &other )
	{
		m_priority = other.priority();
		m_conditions = other.m_conditions;
	}

	return *this;
}

int
Properties::priority() const
{
	return m_priority;
}

void
Properties::setPriority( int p )
{
	m_priority = p;
}

int
Properties::conditionsAmount() const
{
	return m_conditions.count();
}

Condition &
Properties::conditionAt( int index )
{
	return m_conditions[ index ];
}

const Condition &
Properties::conditionAt( int index ) const
{
	return m_conditions.at( index );
}

void
Properties::insertCondition( const Condition & cond, int index )
{
	m_conditions.insert( index, cond );
}

void
Properties::removeCondition( int index )
{
	m_conditions.removeAt( index );
}

void
Properties::swapConditions( int i, int j )
{
	m_conditions.swap( i, j );
}

int
Properties::checkConditions( const QVariant & value,
	Como::Source::Type valueType ) const
{
	int index = -1;
	int i = 0;

	foreach( const Condition & c, m_conditions )
	{
		if( c.check( value, valueType ) )
		{
			index = i;
			break;
		}

		++i;
	}

	return index;
}

void
Properties::saveConfiguration( const QString & fileName ) const
{
	PropertiesTag tag( *this );

	QtConfFile::writeQtConfFile( tag, fileName,
		QTextCodec::codecForName( "UTF-8" ) );
}

void
Properties::readConfiguration( const QString & fileName )
{
	PropertiesTag tag;

	QtConfFile::readQtConfFile( tag, fileName,
		QTextCodec::codecForName( "UTF-8" ) );

	operator = ( tag.properties() );
}


//
// PropertiesKey
//

PropertiesKey::PropertiesKey( const QString & name,
	const QString & typeName, const QString & channelName )
	:	m_name( name )
	,	m_typeName( typeName )
	,	m_channelName( channelName )
{
}

PropertiesKey::PropertiesKey( const PropertiesKey & other )
	:	m_name( other.name() )
	,	m_typeName( other.typeName() )
	,	m_channelName( other.channelName() )
{
}

PropertiesKey &
PropertiesKey::operator = ( const PropertiesKey & other )
{
	if( this != &other )
	{
		m_name = other.name();
		m_typeName = other.typeName();
		m_channelName = other.channelName();
	}

	return *this;
}

const QString &
PropertiesKey::name() const
{
	return m_name;
}

const QString &
PropertiesKey::typeName() const
{
	return m_typeName;
}

const QString &
PropertiesKey::channelName() const
{
	return m_channelName;
}

bool operator < ( const PropertiesKey & k1, const PropertiesKey & k2 )
{
	const bool k1ChannelNameDefined = !k1.channelName().isEmpty();
	const bool k1SourceNameDefined = !k1.name().isEmpty();

	const bool k2ChannelNameDefined = !k2.channelName().isEmpty();
	const bool k2SourceNameDefined = !k2.name().isEmpty();

	if( k2ChannelNameDefined && k2SourceNameDefined &&
		( !k1ChannelNameDefined || !k1SourceNameDefined ) )
			return true;
	else if( k2ChannelNameDefined && k1ChannelNameDefined &&
		k2SourceNameDefined && !k1SourceNameDefined )
			return true;
	else if( k2SourceNameDefined && k1SourceNameDefined &&
		k2ChannelNameDefined && !k1ChannelNameDefined )
			return true;
	else if( k1ChannelNameDefined && k1SourceNameDefined &&
		k2ChannelNameDefined && k2SourceNameDefined )
	{
		return ( ( k1.name() + k1.typeName() + k1.channelName() ) <
			( k2.name() + k2.typeName() + k2.channelName() ) );
	}
	else if( k1ChannelNameDefined && k2ChannelNameDefined &&
		!k1SourceNameDefined && !k2SourceNameDefined )
	{
		return ( ( k1.typeName() + k1.channelName() ) <
			( k2.typeName() + k2.channelName() ) );
	}
	else if( k1SourceNameDefined && k2SourceNameDefined &&
		!k1ChannelNameDefined && !k2ChannelNameDefined )
	{
		return ( ( k1.name() + k1.typeName() ) <
			( k2.name() + k2.typeName() ) );
	}
	else if( !k1SourceNameDefined && !k2SourceNameDefined &&
		!k1ChannelNameDefined && !k2ChannelNameDefined )
	{
		return ( k1.typeName() < k2.typeName() );
	}
	else
		return false;
}

bool operator == ( const PropertiesKey & k1, const PropertiesKey & k2 )
{
	return ( k1.name() == k2.name() &&
		k1.typeName() == k2.typeName() &&
		k1.channelName() == k2.channelName() );
}


//
// PropertiesValue
//

PropertiesValue::PropertiesValue( const QString & confFileName,
	const Como::Source::Type & type,
	const Properties & props )
	:	m_confFileName( confFileName )
	,	m_valueType( type )
	,	m_properties( props )
{
}

PropertiesValue::PropertiesValue( const PropertiesValue & other )
	:	m_confFileName( other.confFileName() )
	,	m_valueType( other.valueType() )
	,	m_properties( other.properties() )
{
}

PropertiesValue &
PropertiesValue::operator = ( const PropertiesValue & other )
{
	if( this != &other )
	{
		m_confFileName = other.confFileName();
		m_valueType = other.valueType();
		m_properties = other.properties();
	}

	return *this;
}

const QString &
PropertiesValue::confFileName() const
{
	return m_confFileName;
}

Como::Source::Type
PropertiesValue::valueType() const
{
	return m_valueType;
}

Properties &
PropertiesValue::properties()
{
	return m_properties;
}

const Properties &
PropertiesValue::properties() const
{
	return m_properties;
}


//
// PropertiesManagerPrivate
//

static const QString defaultConfigurationDirectory =
	QLatin1String( "./etc/dataclasses/" );

class PropertiesManagerPrivate {
public:
	PropertiesManagerPrivate()
		:	m_model( 0 )
		,	m_directoryName( defaultConfigurationDirectory )
	{
	}

	//! Generate unique file name for the given key.
	QString generateFileName( const PropertiesKey & key )
	{
		QString fileName;

		QDateTime now = QDateTime::currentDateTime();

		for( QString::ConstIterator it = key.typeName().begin(),
			last = key.typeName().end(); it != last; ++it )
		{
			fileName += QString::number( it->unicode() );
		}

		fileName += QString::number( now.date().year() );
		fileName += QString::number( now.date().month() );
		fileName += QString::number( now.date().day() );
		fileName += QString::number( now.time().hour() );
		fileName += QString::number( now.time().minute() );
		fileName += QString::number( now.time().second() );

		fileName += QLatin1String( ".cfg" );

		return fileName;
	}

	//! Set directory for the properties configuration files.
	void setDirectory( const QString & dir )
	{
		m_directoryName = relativeFilePath( dir );

		if( !m_directoryName.endsWith( QChar( '/' ) ) &&
			!m_directoryName.endsWith( QChar( '\\' ) ) )
				m_directoryName.append( QChar( '/' ) );
	}

	//! Properties map.
	PropertiesMap m_map;
	//! Directory name with properties configuration.
	QString m_directoryName;
	//! UI.
	Ui::PropertiesMainWindow m_ui;
	//! Model for the properties in the view.
	PropertiesModel * m_model;
}; // class PropertiesManagerPrivate


//
// PropertiesManager
//

PropertiesManager::PropertiesManager( QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new PropertiesManagerPrivate )
{
	init();
}

PropertiesManager::~PropertiesManager()
{
}

void
PropertiesManager::init()
{
	d->m_ui.setupUi( this );

	d->m_model = new PropertiesModel( this );
	QSortFilterProxyModel * sortModel = new QSortFilterProxyModel( this );

	sortModel->setSourceModel( d->m_model );

	d->m_ui.m_view->setModel( sortModel );
	d->m_ui.m_view->setSortingEnabled( true );
	d->m_ui.m_view->setRootIsDecorated( false );

	d->m_ui.m_directory->setText( d->m_directoryName );

	connect( d->m_ui.m_quitAction, SIGNAL( triggered() ),
		qApp, SLOT( quit() ) );
}

const Properties *
PropertiesManager::findProperties( const Como::Source & source,
	const QString & channelName ) const
{
	{
		PropertiesKey key( source.name(), source.typeName(), channelName );

		PropertiesMap::ConstIterator it = d->m_map.find( key );

		if( it != d->m_map.end() )
			return &it.value().properties();
	}

	{
		PropertiesKey key( QString(), source.typeName(), channelName );

		PropertiesMap::ConstIterator it = d->m_map.find( key );

		if( it != d->m_map.end() )
			return &it.value().properties();
	}

	{
		PropertiesKey key( source.name(), source.typeName(), QString() );

		PropertiesMap::ConstIterator it = d->m_map.find( key );

		if( it != d->m_map.end() )
			return &it.value().properties();
	}

	{
		PropertiesKey key( QString(), source.typeName(), QString() );

		PropertiesMap::ConstIterator it = d->m_map.find( key );

		if( it != d->m_map.end() )
			return &it.value().properties();
	}

	return 0;
}

const Properties *
PropertiesManager::findProperties( const PropertiesKey & key ) const
{
	PropertiesMap::ConstIterator it = d->m_map.find( key );

	if( it != d->m_map.end() )
		return &it.value().properties();
	else
		return 0;
}

void
PropertiesManager::addProperties( const PropertiesKey & key,
	const Properties & props, const Como::Source::Type & type )
{
	PropertiesMap::Iterator it = d->m_map.find( key );

	if( it != d->m_map.end() )
	{
		it.value().properties() = props;
		it.value().properties().saveConfiguration( it.value().confFileName() );
	}
	else
	{
		PropertiesValue value( d->generateFileName( key ),
			type, props );

		props.saveConfiguration( value.confFileName() );

		d->m_map.insert( key, value );
	}
}

void
PropertiesManager::removeProperties( const PropertiesKey & key )
{
	PropertiesMap::ConstIterator it = d->m_map.find( key );

	if( it != d->m_map.end() )
	{
		QFile confFile( it.value().confFileName() );
		confFile.remove();

		d->m_map.remove( key );
	}
}

void
PropertiesManager::saveConfiguration( const QString & fileName )
{
	PropertiesManagerTag tag( relativeFilePath( d->m_directoryName ),
		d->m_map, windowStateCfg( this ) );

	try {
		QtConfFile::writeQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		QMessageBox::critical( this,
			tr( "Unable to save properties configuration..." ),
			x.whatAsQString() );
	}
}

void
PropertiesManager::readConfiguration( const QString & fileName )
{
	{
		PropertiesManagerTag tag;

		try {
			QtConfFile::readQtConfFile( tag, fileName,
				QTextCodec::codecForName( "UTF-8" ) );
		}
		catch( const QtConfFile::Exception & x )
		{
			QMessageBox::critical( this,
				tr( "Unable to read properties configuration..." ),
				x.whatAsQString() );

			return;
		}

		d->m_directoryName = tag.propertiesDirectory();
		d->m_map = tag.propertiesMap();

		restoreWindowState( tag.windowState(), this );
	}

	d->m_map.clear();

	if( !d->m_directoryName.endsWith( QChar( '/' ) ) &&
		!d->m_directoryName.endsWith( QChar( '\\' ) ) )
			d->m_directoryName.append( QChar( '/' ) );

	QList< PropertiesKey > toRemove;

	for( PropertiesMap::Iterator it = d->m_map.begin(),
		last = d->m_map.end(); it != last; ++it )
	{
		try {
			PropertiesTag tag;

			QtConfFile::readQtConfFile( tag,
				d->m_directoryName + it.value().confFileName(),
				QTextCodec::codecForName( "UTF-8" ) );

			it.value().properties() = tag.properties();
		}
		catch( const QtConfFile::Exception & x )
		{
			const QMessageBox::StandardButton button =
				QMessageBox::question( this,
					tr( "Unable to read properties configuration..." ),
					tr( "%1\\n\\n"
						"Do you want to delete this file?" )
							.arg( x.whatAsQString() ),
					QMessageBox::Ok | QMessageBox::Cancel,
					QMessageBox::Ok );

			toRemove.append( it.key() );

			if( button == QMessageBox::Ok )
			{
				QFile file( d->m_directoryName + it.value().confFileName() );
				file.remove();
			}
		}
	}

	foreach( const PropertiesKey & key, toRemove )
		d->m_map.remove( key );

	initModelAndView();
}

void
PropertiesManager::initModelAndView()
{
	d->m_ui.m_directory->setText( d->m_directoryName );
	d->m_model->initModel( d->m_map );
}

void
PropertiesManager::closeEvent( QCloseEvent * event )
{
	hide();

	event->accept();
}

} /* namespace Globe */

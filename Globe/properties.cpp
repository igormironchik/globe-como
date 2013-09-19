
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

// Globe include.
#include <Globe/properties.hpp>
#include <Globe/utils.hpp>
#include <Globe/properties_model.hpp>
#include <Globe/properties_cfg.hpp>
#include <Globe/window_state_cfg.hpp>
#include <Globe/tool_window_object.hpp>
#include <Globe/channels.hpp>
#include <Globe/sources.hpp>
#include <Globe/sources_dialog.hpp>
#include <Globe/properties_cfg_filename_dialog.hpp>
#include <Globe/properties_key_type_dialog.hpp>
#include <Globe/properties_dialog.hpp>
#include <Globe/properties_widget.hpp>
#include <Globe/log.hpp>
#include <Globe/globe_menu.hpp>

#include "ui_properties_mainwindow.h"

// Qt include.
#include <QFile>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include <QCloseEvent>
#include <QMenuBar>

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
	,	m_otherwise( other.m_otherwise )
{
}

Properties &
Properties::operator = ( const Properties & other )
{
	if( this != &other )
	{
		m_priority = other.priority();
		m_conditions = other.m_conditions;
		m_otherwise = other.m_otherwise;
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

Condition &
Properties::otherwise()
{
	return m_otherwise;
}

const Condition &
Properties::otherwise() const
{
	return m_otherwise;
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

const Condition &
Properties::checkConditions( const QVariant & value,
	Como::Source::Type valueType ) const
{
	foreach( const Condition & c, m_conditions )
	{
		if( c.check( value, valueType ) )
			return c;
	}

	return m_otherwise;
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

PropertiesKey::PropertiesKey()
	:	m_keyType( NotDefinedKeyType )
{
}

PropertiesKey::PropertiesKey( const QString & name,
	const QString & typeName, const QString & channelName )
	:	m_name( name )
	,	m_typeName( typeName )
	,	m_channelName( channelName )
	,	m_keyType( NotDefinedKeyType )
{
	if( m_channelName.isEmpty() && m_name.isEmpty() )
		m_keyType = ExactlyThisTypeOfSourceInAnyChannel;
	else if( m_name.isEmpty() )
		m_keyType = ExactlyThisTypeOfSource;
	else if( m_channelName.isEmpty() )
		m_keyType = ExactlyThisSourceInAnyChannel;
	else
		m_keyType = ExactlyThisSource;
}

PropertiesKey::PropertiesKey( const PropertiesKey & other )
	:	m_name( other.name() )
	,	m_typeName( other.typeName() )
	,	m_channelName( other.channelName() )
	,	m_keyType( other.keyType() )
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
		m_keyType = other.keyType();
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

PropertiesKeyType
PropertiesKey::keyType() const
{
	return m_keyType;
}

bool operator < ( const PropertiesKey & k1, const PropertiesKey & k2 )
{
	switch( k1.keyType() )
	{
		case ExactlyThisSource :
			return ( ( k1.name() + k1.typeName() + k1.channelName() ) <
				( k2.name() + k2.typeName() + k2.channelName() ) );
		case ExactlyThisSourceInAnyChannel :
			return ( ( k1.name() + k1.typeName() ) <
			( k2.name() + k2.typeName() ) );
		case ExactlyThisTypeOfSource :
			return ( ( k1.typeName() + k1.channelName() ) <
			( k2.typeName() + k2.channelName() ) );
		case ExactlyThisTypeOfSourceInAnyChannel :
			return ( k1.typeName() < k2.typeName() );

		default : return false;
	}
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

PropertiesValue::PropertiesValue()
	:	m_valueType( Como::Source::String )
{
}

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
		,	m_sortModel( 0 )
		,	m_directoryName( defaultConfigurationDirectory )
		,	m_toolWindowObject( 0 )
	{
	}

	//! Set directory for the properties configuration files.
	void setDirectory( const QString & dir )
	{
		m_directoryName = relativeFilePath( dir );

		if( !m_directoryName.endsWith( QChar( '/' ) ) &&
			!m_directoryName.endsWith( QChar( '\\' ) ) )
				m_directoryName.append( QChar( '/' ) );
	}

	//! Find and initialize iterator for the given key.
	void findByKey( const PropertiesKey & key,
		PropertiesMap::Iterator * it, bool * keyExists )
	{
		if( key.keyType() == ExactlyThisSource )
		{
			*it = m_exactlyThisSourceMap.find( key );

			if( *it != m_exactlyThisSourceMap.end() )
				*keyExists = true;

			return;
		}
		else if( key.keyType() == ExactlyThisSourceInAnyChannel )
		{
			*it = m_exactlyThisSourceInAnyChannelMap.find( key );

			if( *it != m_exactlyThisSourceInAnyChannelMap.end() )
				*keyExists = true;

			return;
		}
		else if( key.keyType() == ExactlyThisTypeOfSource )
		{
			*it = m_exactlyThisTypeOfSourceMap.find( key );

			if( *it != m_exactlyThisTypeOfSourceMap.end() )
				*keyExists = true;

			return;
		}
		else
		{
			*it = m_exactlyThisTypeOfSourceInAnyChannelMap.find( key );

			if( *it != m_exactlyThisTypeOfSourceInAnyChannelMap.end() )
				*keyExists = true;

			return;
		}

		*keyExists = false;
	}

	//! Properties map for "ExactlyThisSource" key's type.
	PropertiesMap m_exactlyThisSourceMap;
	//! Properties map for "ExactlyThisSourceInAnyChannel" key's type.
	PropertiesMap m_exactlyThisSourceInAnyChannelMap;
	//! Properties map for "ExactlyThisTypeOfSource" key's type.
	PropertiesMap m_exactlyThisTypeOfSourceMap;
	//! Properties map for "ExactlyThisTypeOfSourceInAnyChannel" key's type.
	PropertiesMap m_exactlyThisTypeOfSourceInAnyChannelMap;
	//! Directory name with properties configuration.
	QString m_directoryName;
	//! UI.
	Ui::PropertiesMainWindow m_ui;
	//! Model for the properties in the view.
	PropertiesModel * m_model;
	//! Sort model.
	QSortFilterProxyModel * m_sortModel;
	//! Tool window object.
	ToolWindowObject * m_toolWindowObject;
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

PropertiesManager &
PropertiesManager::instance()
{
	static PropertiesManager inst;

	return inst;
}

void
PropertiesManager::init()
{
	d->m_ui.setupUi( this );

	setWindowTitle( tr( "Properties Manager" ) );

	d->m_model = new PropertiesModel( this );

	d->m_sortModel = new QSortFilterProxyModel( this );

	d->m_sortModel->setSourceModel( d->m_model );

	d->m_ui.m_view->setModel( d->m_sortModel );
	d->m_ui.m_view->setSortingEnabled( true );
	d->m_ui.m_view->setRootIsDecorated( false );
	d->m_ui.m_view->setAlternatingRowColors( true );

	d->m_ui.m_directory->setText( d->m_directoryName );

	QAction * showAction = new QAction( tr( "&Properties" ), this );
	d->m_toolWindowObject = new ToolWindowObject( showAction, this, this );

	connect( d->m_ui.m_addAction, SIGNAL( triggered() ),
		this, SLOT( addProperties() ) );
	connect( d->m_ui.m_removeAction, SIGNAL( triggered() ),
		this, SLOT( removeProperties() ) );
	connect( d->m_ui.m_view, SIGNAL( clicked( const QModelIndex & ) ),
		this, SLOT( itemSelected( const QModelIndex & ) ) );
	connect( d->m_ui.m_editAction, SIGNAL( triggered() ),
		this, SLOT( editProperties() ) );
}

void
PropertiesManager::initMenu( const Menu & menu )
{
	menuBar()->addMenu( menu.fileMenu() );

	QMenu * toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );

	foreach( ToolWindowObject * obj, menu.toolWindows() )
		if( obj != d->m_toolWindowObject )
			toolsMenu->addAction( obj->menuEntity() );

	menuBar()->addMenu( menu.settingsMenu() );
}

const Properties *
PropertiesManager::findProperties( const Como::Source & source,
	const QString & channelName, PropertiesKey * resultedKey ) const
{
	{
		PropertiesKey key( source.name(), source.typeName(), channelName );

		PropertiesMap::ConstIterator it = d->m_exactlyThisSourceMap.find( key );

		if( it != d->m_exactlyThisSourceMap.end() )
		{
			if( resultedKey )
				*resultedKey = key;

			return &it.value().properties();
		}
	}

	{
		PropertiesKey key( source.name(), source.typeName(), QString() );

		PropertiesMap::ConstIterator it =
			d->m_exactlyThisSourceInAnyChannelMap.find( key );

		if( it != d->m_exactlyThisSourceInAnyChannelMap.end() )
		{
			if( resultedKey )
				*resultedKey = key;

			return &it.value().properties();
		}
	}

	{
		PropertiesKey key( QString(), source.typeName(), channelName );

		PropertiesMap::ConstIterator it =
			d->m_exactlyThisTypeOfSourceMap.find( key );

		if( it != d->m_exactlyThisTypeOfSourceMap.end() )
		{
			if( resultedKey )
				*resultedKey = key;

			return &it.value().properties();
		}
	}

	{
		PropertiesKey key( QString(), source.typeName(), QString() );

		PropertiesMap::ConstIterator it =
			d->m_exactlyThisTypeOfSourceInAnyChannelMap.find( key );

		if( it != d->m_exactlyThisTypeOfSourceInAnyChannelMap.end() )
		{
			if( resultedKey )
				*resultedKey = key;

			return &it.value().properties();
		}
	}

	return 0;
}

static inline PropertiesKey createKey( PropertiesKeyType type,
	const Como::Source & source, const QString & channelName )
{
	switch( type )
	{
		case ExactlyThisSource :
			return PropertiesKey( source.name(), source.typeName(), channelName );
		case ExactlyThisSourceInAnyChannel :
			return PropertiesKey( source.name(), source.typeName(), QString() );
		case ExactlyThisTypeOfSource :
			return PropertiesKey( QString(), source.typeName(), channelName );
		case ExactlyThisTypeOfSourceInAnyChannel :
			return PropertiesKey( QString(), source.typeName(), QString() );
		default :
			return PropertiesKey( QString(), QString(), QString() );
	}
}

static inline QString sourceToString( const Como::Source & source )
{
	QString result;

	result.append( QLatin1String( "name: \"" ) );
	result.append( source.name() );
	result.append( QLatin1String( "\", type name: \"" ) );
	result.append( source.typeName() );
	result.append( QLatin1String( "\"" ) );

	return result;
}

static inline QString keyToString( const PropertiesKey & key )
{
	QString result;

	result.append( QLatin1String( "{channel: \"" ) );
	result.append( ( key.channelName().isEmpty() ?
		QLatin1String( "any" ) : key.channelName() ) );
	result.append( QLatin1String( "\",\nsource name: \"" ) );
	result.append( ( key.name().isEmpty() ?
		QLatin1String( "any" ) : key.name() ) );
	result.append( QLatin1String( "\",\ntype name: \"" ) );
	result.append( ( key.typeName().isEmpty() ?
		QLatin1String( "any" ) : key.typeName() ) );
	result.append( QLatin1String( "\"}" ) );

	return result;
}

void
PropertiesManager::addProperties( const Como::Source & source,
	const QString & channelName, QWidget * parent )
{
	PropertiesKeyType type = NotDefinedKeyType;

	PropertiesKeyTypeDialog	dialog( type, ( parent ? parent : this ) );

	if( dialog.exec() == QDialog::Accepted )
	{
		PropertiesKey key = createKey( type, source, channelName );

		const QString sourceAsString = sourceToString( source );
		const QString keyAsString = keyToString( key );

		PropertiesMap::Iterator it;
		bool propertiesExists = false;

		d->findByKey( key, &it, &propertiesExists );

		PropertiesDialog propertiesDialog( source.type(),
			( parent ? parent : this ) );

		if( propertiesExists )
			propertiesDialog.propertiesWidget()->
				setProperties( it.value().properties() );

		if( propertiesDialog.exec() == QDialog::Accepted )
		{
			if( propertiesExists )
			{
				it.value().properties() =
					propertiesDialog.propertiesWidget()->properties();

				const QString propertieConfFileName =
					d->m_directoryName + it.value().confFileName();

				Log::instance().writeMsgToEventLog( LogLevelInfo,
					QString( "Properties for source %1\n"
						"and key %2\n"
						"from channel \"%3\" has been changed.\n"
						"New properties will be saved into file \"%4\"." )
							.arg( sourceAsString )
							.arg( keyAsString )
							.arg( channelName )
							.arg( propertieConfFileName ) );

				try {
					it.value().properties().saveConfiguration(
						propertieConfFileName );

					Log::instance().writeMsgToEventLog( LogLevelInfo,
						QString( "Properties for source %1\n"
							"and key %2\n"
							"from channel \"%3\"\n"
							"was saved in file \"%4\"." )
								.arg( sourceAsString )
								.arg( keyAsString )
								.arg( channelName )
								.arg( propertieConfFileName ) );
				}
				catch( const QtConfFile::Exception & x )
				{
					Log::instance().writeMsgToEventLog( LogLevelError,
						QString( "Unable to save properties for source %1\n"
							"and key %2\n"
							"from channel \"%3\" to file \"%4\".\n"
							"%5" )
								.arg( sourceAsString )
								.arg( keyAsString )
								.arg( channelName )
								.arg( propertieConfFileName )
								.arg( x.whatAsQString() ) );

					QMessageBox::critical( ( parent ? parent : this ),
						tr( "Unable to save properties..." ),
						x.whatAsQString() );
				}
			}
			else
			{
				QString fileName;

				PropertiesCfgFileNameDialog fileNameDialog( fileName,
					d->m_directoryName, ( parent ? parent : this ) );

				if( fileNameDialog.exec() == QDialog::Accepted )
				{
					const Properties properties =
						propertiesDialog.propertiesWidget()->properties();

					PropertiesValue value( fileName,
						source.type(), properties );

					if( type == ExactlyThisSource )
						d->m_exactlyThisSourceMap.insert( key, value );
					else if( type == ExactlyThisSourceInAnyChannel )
						d->m_exactlyThisSourceInAnyChannelMap.insert( key, value );
					else if( type == ExactlyThisTypeOfSource )
						d->m_exactlyThisTypeOfSourceMap.insert( key, value );
					else
						d->m_exactlyThisTypeOfSourceInAnyChannelMap.insert( key, value );

					d->m_model->addPropertie( key, value );

					Log::instance().writeMsgToEventLog( LogLevelInfo,
						QString( "Properties for source %1\n"
							"and key %2\n"
							"from channel \"%3\" has been added.\n"
							"New properties will be saved into file \"%4\"." )
								.arg( sourceAsString )
								.arg( keyAsString )
								.arg( channelName )
								.arg( fileName ) );

					try {
						properties.saveConfiguration(
							d->m_directoryName + fileName );

						Log::instance().writeMsgToEventLog( LogLevelInfo,
							QString( "Properties for source %1\n"
								"and key %2\n"
								"from channel \"%3\" was saved in file \"%4\"." )
									.arg( sourceAsString )
									.arg( keyAsString )
									.arg( channelName )
									.arg( fileName ) );
					}
					catch( const QtConfFile::Exception & x )
					{
						Log::instance().writeMsgToEventLog( LogLevelError,
							QString( "Unable to save properties for source %1\n"
								"and key %2\n"
								"from channel \"%3\" to file \"%4\".\n"
								"%5" )
									.arg( sourceAsString )
									.arg( keyAsString )
									.arg( channelName )
									.arg( fileName )
									.arg( x.whatAsQString() ) );

						QMessageBox::critical( ( parent ? parent : this ),
							tr( "Unable to save properties..." ),
							x.whatAsQString() );
					}
				}
			}
		}
	}
}

void
PropertiesManager::removeProperties( const PropertiesKey & key,
	QWidget * parent )
{
	Q_UNUSED( parent )

	if( key.keyType() == ExactlyThisSource )
		d->m_exactlyThisSourceMap.remove( key );
	else if( key.keyType() == ExactlyThisSourceInAnyChannel )
		d->m_exactlyThisSourceInAnyChannelMap.remove( key );
	else if( key.keyType() == ExactlyThisTypeOfSource )
		d->m_exactlyThisTypeOfSourceMap.remove( key );
	else
		d->m_exactlyThisTypeOfSourceInAnyChannelMap.remove( key );

	Log::instance().writeMsgToEventLog( LogLevelInfo,
		QString( "Properties for key %1 was deleted." )
			.arg( keyToString( key ) ) );
}

void
PropertiesManager::editProperties( const PropertiesKey & key, QWidget * parent )
{
	PropertiesMap::Iterator it;
	bool propertiesExists = false;

	d->findByKey( key, &it, &propertiesExists );

	if( propertiesExists )
	{
		PropertiesDialog propertiesDialog( it.value().valueType(),
			( parent ? parent : this ) );

		propertiesDialog.propertiesWidget()->
			setProperties( it.value().properties() );

		if( propertiesDialog.exec() == QDialog::Accepted )
		{
			const QString fileName = d->m_directoryName +
				it.value().confFileName();
			const QString keyAsString = keyToString( key );

			Log::instance().writeMsgToEventLog( LogLevelInfo,
				QString( "Properties for key %1\n"
					"was edited." )
					.arg( keyAsString ) );

			it.value().properties() =
				propertiesDialog.propertiesWidget()->properties();

			try {
				it.value().properties().saveConfiguration( fileName );

				Log::instance().writeMsgToEventLog( LogLevelInfo,
					QString( "Properties for key %1\n"
						"was saved in file \"%2\"." )
							.arg( keyAsString )
							.arg( fileName ) );
			}
			catch( const QtConfFile::Exception & x )
			{
				Log::instance().writeMsgToEventLog( LogLevelError,
					QString( "Unable to save properties for key %1\n"
						"to file \"%2\".\n"
						"%3" )
							.arg( keyAsString )
							.arg( fileName )
							.arg( x.whatAsQString() ) );

				QMessageBox::critical( ( parent ? parent : this ),
					tr( "Unable to save properties..." ),
					x.whatAsQString() );
			}
		}
	}
}

void
PropertiesManager::saveConfiguration( const QString & fileName )
{
	try {
		PropertiesManagerTag tag( relativeFilePath( d->m_directoryName ),
			d->m_exactlyThisSourceMap,
			d->m_exactlyThisSourceInAnyChannelMap,
			d->m_exactlyThisTypeOfSourceMap,
			d->m_exactlyThisTypeOfSourceInAnyChannelMap,
			windowStateCfg( this ) );

		QtConfFile::writeQtConfFile( tag, fileName,
			QTextCodec::codecForName( "UTF-8" ) );

		Log::instance().writeMsgToEventLog( LogLevelInfo,
			QString( "Properties manager's configuration saved "
				"in file \"%1\"." )
					.arg( fileName ) );
	}
	catch( const QtConfFile::Exception & x )
	{
		Log::instance().writeMsgToEventLog( LogLevelError,
			QString( "Unable to save properties manager's configuration "
				"to file \"%1\"." )
					.arg( fileName ) );

		QMessageBox::critical( this,
			tr( "Unable to save properties configuration..." ),
			x.whatAsQString() );
	}
}

void
PropertiesManager::readPropertiesConfigs( PropertiesMap & map )
{
	QList< PropertiesKey > toRemove;

	for( PropertiesMap::Iterator it = map.begin(),
		last = map.end(); it != last; ++it )
	{
		const QString keyAsString = keyToString( it.key() );

		try {
			PropertiesTag tag;

			QtConfFile::readQtConfFile( tag,
				d->m_directoryName + it.value().confFileName(),
				QTextCodec::codecForName( "UTF-8" ) );

			Log::instance().writeMsgToEventLog( LogLevelInfo,
				QString( "Propertie's configuration for key %1\n"
					"was loaded." )
					.arg( keyAsString ) );

			it.value().properties() = tag.properties();
		}
		catch( const QtConfFile::Exception & x )
		{
			const QString fileName = d->m_directoryName +
				it.value().confFileName();

			Log::instance().writeMsgToEventLog( LogLevelError,
				QString( "Unable to read propertie's configuration for key %1\n"
					"from file \"%2\"." )
						.arg( keyAsString )
						.arg( fileName ) );

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
				QFile file( fileName );
				file.remove();

				Log::instance().writeMsgToEventLog( LogLevelWarning,
					QString( "Propertie's configuration file \"%1\" "
						"was removed." )
							.arg( fileName ) );
			}
		}
	}

	foreach( const PropertiesKey & key, toRemove )
		map.remove( key );
}

void
PropertiesManager::readConfiguration( const QString & fileName )
{
	{
		PropertiesManagerTag tag;

		try {
			QtConfFile::readQtConfFile( tag, fileName,
				QTextCodec::codecForName( "UTF-8" ) );

			Log::instance().writeMsgToEventLog( LogLevelInfo,
				QString( "Properties manager's configuration loaded "
					"from file \"%1\"." )
						.arg( fileName ) );
		}
		catch( const QtConfFile::Exception & x )
		{
			Log::instance().writeMsgToEventLog( LogLevelError,
				QString( "Unable to load properties manager's configuration "
					" from file \"%1\".\n"
					"%2" )
						.arg( fileName )
						.arg( x.whatAsQString() ) );

			QMessageBox::critical( this,
				tr( "Unable to read properties configuration..." ),
				x.whatAsQString() );

			return;
		}

		d->setDirectory( tag.propertiesDirectory() );

		checkPathAndCreateIfNotExists( d->m_directoryName );

		d->m_exactlyThisSourceMap = tag.exactlyThisSourceMap();
		d->m_exactlyThisSourceInAnyChannelMap =
			tag.exactlyThisSourceInAnyChannelMap();
		d->m_exactlyThisTypeOfSourceMap =
			tag.exactlyThisTypeOfSourceMap();
		d->m_exactlyThisTypeOfSourceInAnyChannelMap =
			tag.exactlyThisTypeOfSourceInAnyChannelMap();

		restoreWindowState( tag.windowState(), this );
	}

	if( !d->m_directoryName.endsWith( QChar( '/' ) ) &&
		!d->m_directoryName.endsWith( QChar( '\\' ) ) )
			d->m_directoryName.append( QChar( '/' ) );

	readPropertiesConfigs( d->m_exactlyThisSourceMap );
	readPropertiesConfigs( d->m_exactlyThisSourceInAnyChannelMap );
	readPropertiesConfigs( d->m_exactlyThisTypeOfSourceMap );
	readPropertiesConfigs( d->m_exactlyThisTypeOfSourceInAnyChannelMap );

	initModelAndView();
}

ToolWindowObject *
PropertiesManager::toolWindowObject()
{
	return d->m_toolWindowObject;
}

void
PropertiesManager::initModelAndView()
{
	d->m_ui.m_directory->setText( d->m_directoryName );

	d->m_model->initModel( d->m_exactlyThisSourceMap,
		d->m_exactlyThisSourceInAnyChannelMap,
		d->m_exactlyThisTypeOfSourceMap,
		d->m_exactlyThisTypeOfSourceInAnyChannelMap );
}

void
PropertiesManager::closeEvent( QCloseEvent * event )
{
	hide();

	event->accept();
}

void
PropertiesManager::addProperties()
{
	Como::Source source;
	QString channelName;

	SourcesDialog sourcesDialog( source, channelName, this );

	if( sourcesDialog.exec() == QDialog::Accepted )
		addProperties( source, channelName );
}

void
PropertiesManager::removeProperties()
{
	const QModelIndex index = d->m_sortModel->mapToSource(
		d->m_ui.m_view->currentIndex() );

	if( index.isValid() )
	{
		QMessageBox::StandardButton deletePropertieButton =
			QMessageBox::question( this, tr( "Deletion of the propertie..." ),
				tr( "You are about to delete propertie. Are you sure?" ),
				QMessageBox::Ok | QMessageBox::Cancel,
				QMessageBox::Ok );

		if( deletePropertieButton == QMessageBox::Ok )
		{
			const int row = index.row();

			PropertiesKey key = d->m_model->key( row );

			PropertiesMap::Iterator it;
			bool propertiesExists = false;

			d->findByKey( key, &it, &propertiesExists );

			removeProperties( key );

			d->m_model->removePropertie( row );

			if( propertiesExists )
			{
				QMessageBox::StandardButton deleteFileButton =
					QMessageBox::question( this, tr( "Deletion of the propertie..." ),
						tr( "Delete the file \"%1\" with propertie defenitions?" )
							.arg( it.value().confFileName() ),
						QMessageBox::Ok | QMessageBox::Cancel,
						QMessageBox::Ok );

				if( deleteFileButton == QMessageBox::Ok )
				{
					QFile confFile( d->m_directoryName + it.value().confFileName() );
					confFile.remove();
				}
			}

			d->m_ui.m_removeAction->setEnabled( false );
			d->m_ui.m_editAction->setEnabled( false );
		}
	}
}

void
PropertiesManager::itemSelected( const QModelIndex & index )
{
	if( index.isValid() )
	{
		d->m_ui.m_removeAction->setEnabled( true );
		d->m_ui.m_editAction->setEnabled( true );
	}
}

void
PropertiesManager::editProperties()
{
	const QModelIndex index = d->m_sortModel->mapToSource(
		d->m_ui.m_view->currentIndex() );

	if( index.isValid() )
		editProperties( d->m_model->key( index.row() ) );
}

} /* namespace Globe */

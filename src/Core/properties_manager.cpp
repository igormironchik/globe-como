
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
*/

// Globe include.
#include <Core/properties_manager.hpp>
#include <Core/utils.hpp>
#include <Core/properties_model.hpp>
#include <Core/window_state_cfg.hpp>
#include <Core/tool_window_object.hpp>
#include <Core/channels.hpp>
#include <Core/sources.hpp>
#include <Core/sources_dialog.hpp>
#include <Core/properties_cfg_filename_dialog.hpp>
#include <Core/properties_key_type_dialog.hpp>
#include <Core/properties_dialog.hpp>
#include <Core/properties_widget.hpp>
#include <Core/log.hpp>
#include <Core/globe_menu.hpp>
#include <Core/properties_cfg.hpp>
#include <Core/configuration.hpp>

#include "ui_properties_mainwindow.h"

// Qt include.
#include <QFile>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include <QCloseEvent>
#include <QMenuBar>
#include <QCoreApplication>


namespace Globe {

//
// PropertiesManagerPrivate
//

class PropertiesManagerPrivate {
public:
	explicit PropertiesManagerPrivate( PropertiesManager * parent )
		:	m_directoryName( defaultPropsConfigurationDirectory )
		,	m_model( 0 )
		,	m_sortModel( 0 )
		,	m_toolWindowObject( 0 )
		,	m_parent( parent )
	{
	}

	//! Set directory for the properties configuration files.
	void setDirectory( const QString & dir )
	{
		m_directoryName = relativeFilePath( dir, Configuration::instance().path() );

		if( !m_directoryName.endsWith( QChar( '/' ) ) &&
			!m_directoryName.endsWith( QChar( '\\' ) ) )
				m_directoryName.append( QChar( '/' ) );
	}

	//! Find and initialize iterator for the given key.
	void findByKey( const PropertiesKey & key,
		PropertiesMap::Iterator & it, bool & keyExists )
	{
		keyExists = false;

		if( key.keyType() == ExactlyThisSource )
		{
			it = m_exactlyThisSourceMap.find( key );

			if( it != m_exactlyThisSourceMap.end() )
				keyExists = true;

			return;
		}
		else if( key.keyType() == ExactlyThisSourceInAnyChannel )
		{
			it = m_exactlyThisSourceInAnyChannelMap.find( key );

			if( it != m_exactlyThisSourceInAnyChannelMap.end() )
				keyExists = true;

			return;
		}
		else if( key.keyType() == ExactlyThisTypeOfSource )
		{
			it = m_exactlyThisTypeOfSourceMap.find( key );

			if( it != m_exactlyThisTypeOfSourceMap.end() )
				keyExists = true;

			return;
		}
		else
		{
			it = m_exactlyThisTypeOfSourceInAnyChannelMap.find( key );

			if( it != m_exactlyThisTypeOfSourceInAnyChannelMap.end() )
				keyExists = true;

			return;
		}
	}

	//! Save new properties.
	void saveNewProperties( const PropertiesKey & key, const Properties & p,
		const Como::Source & source,
		PropertiesKeyType type,
		const QString & sourceAsString,
		const QString & keyAsString,
		const QString & channelName,
		QWidget * parent )
	{
		QString fileName;

		PropertiesCfgFileNameDialog fileNameDialog( fileName,
			m_directoryName, ( parent ? parent : m_parent ) );

		if( fileNameDialog.exec() == QDialog::Accepted )
		{
			PropertiesValue value( fileName, source.type(), p );

			if( type == ExactlyThisSource )
				m_exactlyThisSourceMap.insert( key, value );
			else if( type == ExactlyThisSourceInAnyChannel )
				m_exactlyThisSourceInAnyChannelMap.insert( key, value );
			else if( type == ExactlyThisTypeOfSource )
				m_exactlyThisTypeOfSourceMap.insert( key, value );
			else
				m_exactlyThisTypeOfSourceInAnyChannelMap.insert( key, value );

			m_model->addPropertie( key, value );

			Log::instance().writeMsgToEventLog( LogLevelInfo,
				QString( "Properties for source %1\n"
					"and key %2\n"
					"from channel \"%3\" has been added.\n"
					"New properties will be saved into file \"%4\"." )
						.arg( sourceAsString, keyAsString, channelName, fileName ) );

			try {
				savePropertiesConfiguration( Configuration::instance().path() +
					m_directoryName + fileName, p, source.type() );

				Log::instance().writeMsgToEventLog( LogLevelInfo,
					QString( "Properties for source %1\n"
						"and key %2\n"
						"from channel \"%3\" was saved in file \"%4\"." )
							.arg( sourceAsString, keyAsString, channelName, fileName ) );
			}
			catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
			{
				Log::instance().writeMsgToEventLog( LogLevelError,
					QString( "Unable to save properties for source %1\n"
						"and key %2\n"
						"from channel \"%3\" to file \"%4\".\n"
						"%5" )
							.arg( sourceAsString, keyAsString, channelName, fileName, x.desc() ) );

				QMessageBox::critical( 0,
					QObject::tr( "Unable to save properties..." ),
					QObject::tr( "Unable to save properties...\n\n%1" )
						.arg( x.desc() ) );
			}
		}
	}

	//! Save old properties.
	void saveOldProperties( PropertiesMap::Iterator & it, const Properties & p,
		const QString & sourceAsString, const QString & keyAsString,
		const QString & channelName )
	{
		it.value().properties() = p;

		const QString propertieConfFileName =
			Configuration::instance().path() + m_directoryName + it.value().confFileName();

		Log::instance().writeMsgToEventLog( LogLevelInfo,
			QString( "Properties for source %1\n"
				"and key %2\n"
				"from channel \"%3\" has been changed.\n"
				"New properties will be saved into file \"%4\"." )
					.arg( sourceAsString, keyAsString, channelName, propertieConfFileName ) );

		try {
			savePropertiesConfiguration( propertieConfFileName,
				it.value().properties(), it.value().valueType() );

			Log::instance().writeMsgToEventLog( LogLevelInfo,
				QString( "Properties for source %1\n"
					"and key %2\n"
					"from channel \"%3\"\n"
					"was saved in file \"%4\"." )
						.arg( sourceAsString, keyAsString, channelName, propertieConfFileName ) );
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			Log::instance().writeMsgToEventLog( LogLevelError,
				QString( "Unable to save properties for source %1\n"
					"and key %2\n"
					"from channel \"%3\" to file \"%4\".\n"
					"%5" )
						.arg( sourceAsString, keyAsString, channelName, propertieConfFileName,
							x.desc() ) );

			QMessageBox::critical( 0,
				QObject::tr( "Unable to save properties..." ),
				QObject::tr( "Unable to save properties...\n\n%1" )
					.arg( x.desc() ) );
		}
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
	//! Parent.
	PropertiesManager * m_parent;
}; // class PropertiesManagerPrivate


//
// PropertiesManager
//

PropertiesManager::PropertiesManager( QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new PropertiesManagerPrivate( this ) )
{
	init();
}

PropertiesManager::~PropertiesManager()
{
}

static PropertiesManager * propertiesManagerInstancePointer = 0;

void
PropertiesManager::cleanup()
{
	delete propertiesManagerInstancePointer;

	propertiesManagerInstancePointer = 0;
}

PropertiesManager &
PropertiesManager::instance()
{
	if( !propertiesManagerInstancePointer )
	{
		propertiesManagerInstancePointer = new PropertiesManager;

		qAddPostRoutine( &PropertiesManager::cleanup );
	}

	return *propertiesManagerInstancePointer;
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
	d->m_ui.m_view->setActions( d->m_ui.m_addAction,
		d->m_ui.m_editAction, d->m_ui.m_removeAction,
		d->m_ui.m_promoteAction );

	d->m_ui.m_directory->setText( d->m_directoryName );

	QAction * showAction = new QAction( tr( "&Properties" ), this );
	showAction->setShortcut( QKeySequence( tr( "Alt+P" ) ) );
	d->m_toolWindowObject = new ToolWindowObject( showAction, this, this );

	void ( PropertiesManager::*addPropertiesSlot ) () =
		&PropertiesManager::addProperties;

	connect( d->m_ui.m_addAction, &QAction::triggered,
		this, addPropertiesSlot );

	void ( PropertiesManager::*removePropertiesSlot ) () =
		&PropertiesManager::removeProperties;

	connect( d->m_ui.m_removeAction, &QAction::triggered,
		this, removePropertiesSlot );

	connect( d->m_ui.m_view, &PropertiesManagerView::clicked,
		this, &PropertiesManager::itemSelected );

	void ( PropertiesManager::*editPropertiesSlot ) () =
		&PropertiesManager::editProperties;

	connect( d->m_ui.m_editAction, &QAction::triggered,
		this, editPropertiesSlot );

	void ( PropertiesManager::*promotePropertiesSlot ) () =
		&PropertiesManager::promoteProperties;

	connect( d->m_ui.m_promoteAction, &QAction::triggered,
		this, promotePropertiesSlot );
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

		if( it != d->m_exactlyThisSourceMap.cend() )
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

		if( it != d->m_exactlyThisSourceInAnyChannelMap.cend() )
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

		if( it != d->m_exactlyThisTypeOfSourceMap.cend() )
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

		if( it != d->m_exactlyThisTypeOfSourceInAnyChannelMap.cend() )
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

		d->findByKey( key, it, propertiesExists );

		PropertiesDialog propertiesDialog( d->m_directoryName, source.type(),
			( parent ? parent : this ) );

		if( propertiesExists )
			propertiesDialog.propertiesWidget()->
				setProperties( it.value().properties() );

		if( propertiesDialog.exec() == QDialog::Accepted )
		{
			if( propertiesExists )
			{
				d->saveOldProperties( it,
					propertiesDialog.propertiesWidget()->properties(),
					sourceAsString, keyAsString, channelName );
			}
			else
			{
				d->saveNewProperties( key,
					propertiesDialog.propertiesWidget()->properties(),
					source, type, sourceAsString, keyAsString,
					channelName, parent );
			}

			emit propertiesChanged();
		}
	}
}

void
PropertiesManager::removeProperties( const PropertiesKey & key,
	QWidget * parent )
{	
	QMessageBox::StandardButton deletePropertieButton =
		QMessageBox::question( parent, tr( "Deletion of the propertie..." ),
			tr( "You are about to delete propertie. Are you sure?" ),
			QMessageBox::Ok | QMessageBox::Cancel,
			QMessageBox::Cancel );

	if( deletePropertieButton == QMessageBox::Ok )
	{
		PropertiesMap::Iterator it;
		bool propertiesExists = false;

		d->findByKey( key, it, propertiesExists );

		if( propertiesExists )
		{
			QMessageBox::StandardButton deleteFileButton =
				QMessageBox::question( parent,
					tr( "Deletion of the propertie..." ),
					tr( "Delete the file \"%1\" with propertie defenitions?" )
						.arg( it.value().confFileName() ),
					QMessageBox::Ok | QMessageBox::Cancel,
					QMessageBox::Cancel );

			if( deleteFileButton == QMessageBox::Ok )
			{
				QFile confFile( Configuration::instance().path() +
					d->m_directoryName + it.value().confFileName() );
				confFile.remove();
			}
		}

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

		d->m_model->removePropertie( key );

		d->m_ui.m_removeAction->setEnabled( false );
		d->m_ui.m_editAction->setEnabled( false );
		d->m_ui.m_promoteAction->setEnabled( false );

		emit propertiesChanged();
	}
}

void
PropertiesManager::editProperties( const PropertiesKey & key, QWidget * parent )
{
	PropertiesMap::Iterator it;
	bool propertiesExists = false;

	d->findByKey( key, it, propertiesExists );

	if( propertiesExists )
	{
		PropertiesDialog propertiesDialog( d->m_directoryName,
			it.value().valueType(),
			( parent ? parent : this ) );

		propertiesDialog.propertiesWidget()->
			setProperties( it.value().properties() );

		if( propertiesDialog.exec() == QDialog::Accepted )
		{
			const QString fileName = Configuration::instance().path() + d->m_directoryName +
				it.value().confFileName();
			const QString keyAsString = keyToString( key );

			Log::instance().writeMsgToEventLog( LogLevelInfo,
				QString( "Properties for key %1\n"
					"was edited." )
					.arg( keyAsString ) );

			it.value().properties() =
				propertiesDialog.propertiesWidget()->properties();

			emit propertiesChanged();

			try {
				savePropertiesConfiguration( fileName, it.value().properties(),
					it.value().valueType() );

				Log::instance().writeMsgToEventLog( LogLevelInfo,
					QString( "Properties for key %1\n"
						"was saved in file \"%2\"." )
							.arg( keyAsString, fileName ) );
			}
			catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
			{
				Log::instance().writeMsgToEventLog( LogLevelError,
					QString( "Unable to save properties for key %1\n"
						"to file \"%2\".\n"
						"%3" )
							.arg( keyAsString, fileName, x.desc() ) );

				QMessageBox::critical( 0, tr( "Unable to save properties..." ),
					tr( "Unable to save properties...\n\n%1" )
						.arg( x.desc() ) );
			}
		}
	}
}

void
PropertiesManager::promoteProperties( const PropertiesKey & key,
	QWidget * parent )
{
	Como::Source source;
	QString channelName;

	SourcesDialog sourcesDialog( source, channelName, this );

	if( sourcesDialog.exec() == QDialog::Accepted )
	{
		PropertiesKeyType type = NotDefinedKeyType;

		PropertiesKeyTypeDialog	keyTypeDialog( type, ( parent ? parent : this ) );

		if( keyTypeDialog.exec() == QDialog::Accepted )
		{
			PropertiesKey newKey = createKey( type, source, channelName );

			const QString sourceAsString = sourceToString( source );
			const QString keyAsString = keyToString( newKey );

			PropertiesDialog propertiesDialog( d->m_directoryName,
				source.type(), ( parent ? parent : this ) );

			PropertiesMap::Iterator it, from;
			bool propertiesExists = false;

			d->findByKey( newKey, it, propertiesExists );

			QMessageBox::StandardButton button = QMessageBox::NoButton;

			if( propertiesExists )
			{
				button = QMessageBox::question( 0,
					tr( "Such properties already exists..." ),
					tr( "Do you want to edit existing properties?" ),
					QMessageBox::StandardButtons(
						QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel ),
					QMessageBox::Cancel );

				switch( button )
				{
					case QMessageBox::Yes :
						propertiesDialog.propertiesWidget()->
							setProperties( it.value().properties() );

						break;

					case QMessageBox::No :
						{
							propertiesExists = false;

							d->findByKey( key, from, propertiesExists );

							if( propertiesExists )
								propertiesDialog.propertiesWidget()->
									setProperties( from.value().properties() );
						}

						break;

					case QMessageBox::Cancel :
						return;

					default :
						return;
				}
			}
			else
			{
				propertiesExists = false;

				d->findByKey( key, from, propertiesExists );

				if( propertiesExists )
					propertiesDialog.propertiesWidget()->
						setProperties( from.value().properties() );
			}

			if( propertiesDialog.exec() == QDialog::Accepted )
			{
				switch( button )
				{
					case QMessageBox::Yes :
						{
							d->saveOldProperties( it,
								propertiesDialog.propertiesWidget()->properties(),
								sourceAsString, keyAsString, channelName );
						}

						break;

					default :
						{
							d->saveNewProperties( newKey,
								propertiesDialog.propertiesWidget()->properties(),
								source, type, sourceAsString, keyAsString,
								channelName, parent );
						}

						break;
				}

				emit propertiesChanged();
			}
		}
	}
}

void
PropertiesManager::saveConfiguration( const QString & fileName )
{
	QFile file( fileName );

	if( file.open( QIODevice::WriteOnly ) )
	{
		try {
			PropertiesManagerTag tag( defaultPropsConfigurationDirectory,
				d->m_exactlyThisSourceMap,
				d->m_exactlyThisSourceInAnyChannelMap,
				d->m_exactlyThisTypeOfSourceMap,
				d->m_exactlyThisTypeOfSourceInAnyChannelMap,
				windowStateCfg( this ) );

			QTextStream stream( &file );

			cfgfile::write_cfgfile( tag, stream );

			file.close();

			Log::instance().writeMsgToEventLog( LogLevelInfo,
				QString( "Properties manager's configuration saved "
					"in file \"%1\"." )
						.arg( fileName ) );
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			file.close();

			Log::instance().writeMsgToEventLog( LogLevelError,
				QString( "Unable to save properties manager's configuration "
					"to file \"%1\"." )
						.arg( fileName ) );

			QMessageBox::critical( 0,
				tr( "Unable to save properties configuration..." ),
				x.desc() );
		}
	}
	else
	{
		Log::instance().writeMsgToEventLog( LogLevelError,
			QString( "Unable to save properties manager's configuration "
				"to file \"%1\".\nUnable to open file." )
					.arg( fileName ) );

		QMessageBox::critical( 0,
			tr( "Unable to save properties configuration..." ),
			tr( "Unable to open file \"%1\"." ).arg( fileName ) );
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
			readPropertiesConfiguration(
				Configuration::instance().path() + d->m_directoryName + it.value().confFileName(),
				it.value().properties(), it.value().valueType() );

			Log::instance().writeMsgToEventLog( LogLevelInfo,
				QString( "Propertie's configuration for key %1\n"
					"was loaded." )
					.arg( keyAsString ) );
		}
		catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
		{
			const QString fileName = Configuration::instance().path() + d->m_directoryName +
				it.value().confFileName();

			Log::instance().writeMsgToEventLog( LogLevelError,
				QString( "Unable to read propertie's configuration for key %1\n"
					"from file \"%2\"." )
						.arg( keyAsString, fileName ) );

			const QMessageBox::StandardButton button =
				QMessageBox::question( 0,
					tr( "Unable to read properties configuration..." ),
					tr( "Unable to read properties configuration...\n\n"
						"%1\n\n"
						"Do you want to delete this file?" )
							.arg( x.desc() ),
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
PropertiesManager::initWithDefaultCfg()
{
}

void
PropertiesManager::readConfiguration( const QString & fileName )
{
	{
		PropertiesManagerTag tag;

		QFile file( fileName );

		if( file.open( QIODevice::ReadOnly ) )
		{
			try {
				QTextStream stream( &file );

				cfgfile::read_cfgfile( tag, stream, fileName );

				file.close();

				Log::instance().writeMsgToEventLog( LogLevelInfo,
					QString( "Properties manager's configuration loaded "
						"from file \"%1\"." )
							.arg( fileName ) );
			}
			catch( const cfgfile::exception_t< cfgfile::qstring_trait_t > & x )
			{
				file.close();

				Log::instance().writeMsgToEventLog( LogLevelError,
					QString( "Unable to load properties manager's configuration "
						" from file \"%1\".\n"
						"%2" )
							.arg( fileName, x.desc() ) );

				QMessageBox::critical( 0,
					tr( "Unable to read properties configuration..." ),
					x.desc() );

				return;
			}
		}
		else
		{
			Log::instance().writeMsgToEventLog( LogLevelError,
				QString( "Unable to load properties manager's configuration "
					" from file \"%1\".\n"
					"Unable to open file." )
						.arg( fileName ) );

			QMessageBox::critical( 0,
				tr( "Unable to read properties configuration..." ),
				tr( "Unable to open file \"%1\"." ).arg( fileName ) );

			return;
		}

		d->setDirectory( tag.propertiesDirectory() );

		checkDirAndCreateIfNotExists( Configuration::instance().path(), d->m_directoryName );

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
		removeProperties( d->m_model->key( index.row() ), this );
}

void
PropertiesManager::itemSelected( const QModelIndex & index )
{
	if( index.isValid() )
	{
		d->m_ui.m_removeAction->setEnabled( true );
		d->m_ui.m_editAction->setEnabled( true );
		d->m_ui.m_promoteAction->setEnabled( true );
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

void
PropertiesManager::promoteProperties()
{
	const QModelIndex index = d->m_sortModel->mapToSource(
		d->m_ui.m_view->currentIndex() );

	if( index.isValid() )
		promoteProperties( d->m_model->key( index.row() ) );
}

} /* namespace Globe */

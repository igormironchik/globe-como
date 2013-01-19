
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

#include "ui_properties_mainwindow.h"

// Qt include.
#include <QtCore/QFile>
#include <QtGui/QSortFilterProxyModel>
#include <QtGui/QMessageBox>
#include <QtGui/QCloseEvent>
#include <QtGui/QApplication>

// QtConfFile include.
#include <QtConfFile/Utils>

#ifdef DEBUG

// ModelTest include.
#include <modeltest.h>

#endif


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
	PropertiesManagerPrivate(SourcesManager * sourcesManager,
		ChannelsManager * channelsManager )
		:	m_model( 0 )
		,	m_sortModel( 0 )
		,	m_directoryName( defaultConfigurationDirectory )
		,	m_toolWindowObject( 0 )
		,	m_sourcesManager( sourcesManager )
		,	m_channelsManager( channelsManager )
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

	//! Properties map.
	PropertiesMap m_map;
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
	//! Sources manager.
	SourcesManager * m_sourcesManager;
	//! Channels manager.
	ChannelsManager * m_channelsManager;
}; // class PropertiesManagerPrivate


//
// PropertiesManager
//

PropertiesManager::PropertiesManager( SourcesManager * sourcesManager,
		ChannelsManager * channelsManager,
		QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new PropertiesManagerPrivate( sourcesManager, channelsManager ) )
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

#ifdef DEBUG
	new ModelTest( d->m_model, this );
#endif

	d->m_sortModel = new QSortFilterProxyModel( this );

	d->m_sortModel->setSourceModel( d->m_model );

	d->m_ui.m_view->setModel( d->m_sortModel );
	d->m_ui.m_view->setSortingEnabled( true );
	d->m_ui.m_view->setRootIsDecorated( false );
	d->m_ui.m_view->setAlternatingRowColors( true );

	d->m_ui.m_directory->setText( d->m_directoryName );

	QAction * showAction = new QAction( tr( "&Properties" ), this );
	d->m_toolWindowObject = new ToolWindowObject( showAction, this, this );

	connect( d->m_ui.m_quitAction, SIGNAL( triggered() ),
		qApp, SLOT( quit() ) );
	connect( d->m_ui.m_addAction, SIGNAL( triggered() ),
		this, SLOT( addProperties() ) );
	connect( d->m_ui.m_removeAction, SIGNAL( triggered() ),
		this, SLOT( removeProperties() ) );
	connect( d->m_ui.m_view, SIGNAL( clicked( const QModelIndex & ) ),
		this, SLOT( itemSelected( const QModelIndex & ) ) );
}

void
PropertiesManager::initToolsMenu( const QList< ToolWindowObject* > & toolWindows )
{
	QMenu * toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );

	foreach( ToolWindowObject * obj, toolWindows )
		if( obj != d->m_toolWindowObject )
			toolsMenu->addAction( obj->menuEntity() );
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

void
PropertiesManager::addProperties( const Como::Source & source,
	const QString & channelName )
{
	PropertiesKeyType type = NotDefinedKeyType;

	PropertiesKeyTypeDialog	dialog( type, this );

	if( dialog.exec() == QDialog::Accepted )
	{
		PropertiesKey key = createKey( type, source, channelName );

		PropertiesMap::Iterator it = d->m_map.find( key );

		PropertiesDialog propertiesDialog( source.type(), this );

		const bool propertiesExists = ( it != d->m_map.end() );

		if( propertiesExists )
			propertiesDialog.propertiesWidget()->
				setProperties( it.value().properties() );

		if( propertiesDialog.exec() == QDialog::Accepted )
		{
			if( propertiesExists )
			{
				it.value().properties() =
					propertiesDialog.propertiesWidget()->properties();

				it.value().properties().saveConfiguration( d->m_directoryName +
					it.value().confFileName() );
			}
			else
			{
				QString fileName;

				PropertiesCfgFileNameDialog fileNameDialog( fileName,
					d->m_directoryName, this );

				if( fileNameDialog.exec() == QDialog::Accepted )
				{
					const Properties properties =
						propertiesDialog.propertiesWidget()->properties();

					PropertiesValue value( fileName,
						source.type(), properties );

					d->m_map.insert( key, value );

					d->m_model->addPropertie( key, value );

					properties.saveConfiguration( d->m_directoryName + fileName );
				}
			}
		}
	}
}

void
PropertiesManager::removeProperties( const PropertiesKey & key )
{
	PropertiesMap::ConstIterator it = d->m_map.find( key );

	if( it != d->m_map.end() )
		d->m_map.remove( key );
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

		d->setDirectory( tag.propertiesDirectory() );
		d->m_map = tag.propertiesMap();

		restoreWindowState( tag.windowState(), this );
	}

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

ToolWindowObject *
PropertiesManager::toolWindowObject()
{
	return d->m_toolWindowObject;
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

void
PropertiesManager::addProperties()
{
	Como::Source source;
	QString channelName;

	SourcesDialog sourcesDialog( source, channelName, d->m_sourcesManager,
		d->m_channelsManager, this );

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

			PropertiesValue value( d->m_map.value( key ) );

			removeProperties( key );

			d->m_model->removePropertie( row );

			QMessageBox::StandardButton deleteFileButton =
				QMessageBox::question( this, tr( "Deletion of the propertie..." ),
					tr( "Delete the file \"%1\" with propertie defenitions?" )
						.arg( value.confFileName() ),
					QMessageBox::Ok | QMessageBox::Cancel,
					QMessageBox::Ok );

			if( deleteFileButton == QMessageBox::Ok )
			{
				QFile confFile( d->m_directoryName + value.confFileName() );
				confFile.remove();
			}

			d->m_ui.m_removeAction->setEnabled( false );
		}
	}
}

void
PropertiesManager::itemSelected( const QModelIndex & index )
{
	if( index.isValid() )
		d->m_ui.m_removeAction->setEnabled( true );
}

} /* namespace Globe */

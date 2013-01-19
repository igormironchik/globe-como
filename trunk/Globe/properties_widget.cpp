
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
#include <Globe/properties_widget.hpp>
#include <Globe/properties_widget_model.hpp>

// Qt include.
#include <QtGui/QContextMenuEvent>
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QHeaderView>
#include <QtGui/QStyledItemDelegate>
#include <QtGui/QComboBox>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>

#ifdef DEBUG

// ModelTest include.
#include <modeltest.h>

#endif


namespace Globe {

//
// ComboBoxDelegate
//

//! ComboBox item delegate.
class ComboBoxDelegate
	:	public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit ComboBoxDelegate( const QStringList & list,
		QObject * parent = 0 )
		:	QStyledItemDelegate( parent )
		,	m_list( list )
	{
	}

	QWidget * createEditor( QWidget * parent,
		const QStyleOptionViewItem & option,
		const QModelIndex & index ) const
	{
		Q_UNUSED( option );
		Q_UNUSED( index );

		QComboBox * editor = new QComboBox( parent );
		editor->addItems( m_list );

		return editor;
	}

	void setEditorData( QWidget * editor,
		const QModelIndex & index ) const
	{
		QComboBox * combo = qobject_cast< QComboBox* > ( editor );

		const int listIndex = m_list.indexOf( index.data().toString() );

		if( listIndex != -1 )
			combo->setCurrentIndex( listIndex );
	}

	void setModelData( QWidget * editor, QAbstractItemModel * model,
		const QModelIndex & index ) const
	{
		QComboBox * comboBox = qobject_cast< QComboBox* >( editor );

		model->setData( index, comboBox->currentText(), Qt::EditRole );
	}

	void updateEditorGeometry( QWidget * editor,
		const QStyleOptionViewItem & option,
		const QModelIndex & index ) const
	{
		Q_UNUSED( index );

		editor->setGeometry( option.rect );
	}

private:
	//! List with a data for the delegate.
	QStringList m_list;
}; // class ComboBoxDelegate


//
// PropertiesListPrivate
//

class PropertiesListPrivate {
public:
	explicit PropertiesListPrivate( Como::Source::Type valueType )
		:	m_valueType( valueType )
		,	m_model( 0 )
		,	m_contextMenuRequestedIndex( -1 )
	{
	}

	//! Operation mode.
	enum OperationMode {
		//! Operation for the current item.
		OperationForCurrentItem,
		//! Operation for item under cursor.
		OperationForItemUnderCursor
	}; // enum OperationMode

	//! Delete condition.
	void deleteCondition( int index, OperationMode opMode )
	{
		if( index == -1 )
			return;

		m_model->removeCondition( index );

		if( opMode == OperationForItemUnderCursor )
			m_contextMenuRequestedIndex = -1;
	}

	//! Move condition up.
	bool moveConditionUp( int index, OperationMode opMode )
	{
		if( index == -1 )
			return false;

		bool ok = false;

		if( m_model->moveConditionUp( index ) )
			ok = true;

		if( opMode == OperationForItemUnderCursor )
			m_contextMenuRequestedIndex = -1;

		return ok;
	}

	//! Move condition down.
	bool moveConditionDown( int index, OperationMode opMode )
	{
		if( index == -1 )
			return false;

		bool ok = false;

		if( m_model->moveConditionDown( index ) )
			ok = true;

		if( opMode == OperationForItemUnderCursor )
			m_contextMenuRequestedIndex = -1;

		return ok;
	}

	//! Value type.
	Como::Source::Type m_valueType;
	//! Model.
	PropertiesListModel * m_model;
	//! Where context menu was requested?
	int m_contextMenuRequestedIndex;
	//! Delegate for the expression.
	ComboBoxDelegate * m_expressionDelegate;
	//! Delegate for the level.
	ComboBoxDelegate * m_levelDelegate;
}; // class PropertiesListPrivate


//
// PropertiesList
//

PropertiesList::PropertiesList( Como::Source::Type valueType, QWidget * parent )
	:	QTreeView( parent )
	,	d( new PropertiesListPrivate( valueType ) )
{
	init();
}

PropertiesList::~PropertiesList()
{
}

void
PropertiesList::init()
{
	d->m_model = new PropertiesListModel( d->m_valueType, this );

#ifdef DEBUG
	new ModelTest( d->m_model, this );
#endif

	d->m_expressionDelegate = new ComboBoxDelegate(
		QStringList() << "<" << "<=" << "==" << ">=" << ">", this );

	d->m_levelDelegate = new ComboBoxDelegate(
		QStringList() << "none" << "critical" << "error"
			<< "warning" << "debug" << "info", this );

	setModel( d->m_model );
	setRootIsDecorated( false );
	setWordWrap( true );
	header()->setResizeMode( QHeaderView::ResizeToContents );

	setItemDelegateForColumn( 1, d->m_expressionDelegate );
	setItemDelegateForColumn( 3, d->m_levelDelegate );

	connect( d->m_model, SIGNAL( wrongProperties() ),
		this, SLOT( propertiesWrong() ) );
	connect( d->m_model, SIGNAL( changed() ),
		this, SLOT( propertiesChanged() ) );
}

Properties
PropertiesList::properties() const
{
	return d->m_model->properties();
}

void
PropertiesList::setProperties( const Properties & p )
{
	d->m_model->setProperties( p );
}

int
PropertiesList::currentItemIndex() const
{
	const QModelIndex index = currentIndex();

	if( index.isValid() )
		return index.row();
	else
		return -1;
}

int
PropertiesList::itemsCount() const
{
	return d->m_model->rowCount();
}

bool
PropertiesList::isOtherwiseConditionExists() const
{
	return d->m_model->isOtherwiseConditionExists();
}

bool
PropertiesList::isPropertiesOk() const
{
	return true;
}

void
PropertiesList::moveCurrentUp()
{
	if( d->moveConditionUp( currentItemIndex(),
		PropertiesListPrivate::OperationForCurrentItem ) )
	{
		const QModelIndex index = currentIndex();

		setCurrentIndex( d->m_model->index( index.row() - 1, index.column() ) );
	}
}

void
PropertiesList::moveCurrentDown()
{
	if( d->moveConditionDown( currentItemIndex(),
		PropertiesListPrivate::OperationForCurrentItem ) )
	{
		const QModelIndex index = currentIndex();

		setCurrentIndex( d->m_model->index( index.row() + 1, index.column() ) );
	}
}

void
PropertiesList::deleteCurrent()
{
	d->deleteCondition( currentItemIndex(),
		PropertiesListPrivate::OperationForCurrentItem );
}

void
PropertiesList::addCondition()
{
	d->m_model->addCondition();
}

void
PropertiesList::addOtherwiseCondition()
{
	d->m_model->addOtherwiseCondition();
}

void
PropertiesList::propertiesChanged()
{
	emit changed();
}

void
PropertiesList::propertiesWrong()
{
	emit wrongProperties();
}

void
PropertiesList::moveUnderCursorUp()
{
	if( d->moveConditionUp( d->m_contextMenuRequestedIndex,
		PropertiesListPrivate::OperationForItemUnderCursor ) )
	{
		const QModelIndex index = currentIndex();

		setCurrentIndex( d->m_model->index( index.row() - 1, index.column() ) );
	}
}

void
PropertiesList::moveUnderCursorDown()
{
	if( d->moveConditionDown( d->m_contextMenuRequestedIndex,
		PropertiesListPrivate::OperationForItemUnderCursor ) )
	{
		const QModelIndex index = currentIndex();

		setCurrentIndex( d->m_model->index( index.row() + 1, index.column() ) );
	}
}

void
PropertiesList::deleteUnderCursor()
{
	d->deleteCondition( d->m_contextMenuRequestedIndex,
		PropertiesListPrivate::OperationForItemUnderCursor );
}

void
PropertiesList::contextMenuEvent( QContextMenuEvent * event )
{
	QMenu menu( this );

	const QModelIndex modelIndex = indexAt( event->pos() );

	d->m_contextMenuRequestedIndex =
		( modelIndex.isValid() ? modelIndex.row() : -1 );

	if( d->m_contextMenuRequestedIndex > 0 )
	{
		if( d->m_model->isOtherwiseConditionExists() )
		{
			if( d->m_contextMenuRequestedIndex < d->m_model->rowCount() - 1 )
				menu.addAction( QIcon( ":/img/up_22x22.png" ), tr( "Move up" ),
					this, SLOT( moveUnderCursorUp() ) );
		}
		else
			menu.addAction( QIcon( ":/img/up_22x22.png" ), tr( "Move up" ),
					this, SLOT( moveUnderCursorUp() ) );
	}

	if( d->m_contextMenuRequestedIndex != -1 &&
		d->m_contextMenuRequestedIndex < d->m_model->rowCount() - 1 )
	{
		if( d->m_model->isOtherwiseConditionExists() )
		{
			if( d->m_contextMenuRequestedIndex < d->m_model->rowCount() - 2 )
				menu.addAction( QIcon( ":/img/down_22x22.png" ), tr( "Move down" ),
					this, SLOT( moveUnderCursorDown() ) );
		}
		else
			if( d->m_contextMenuRequestedIndex < d->m_model->rowCount() - 2 )
				menu.addAction( QIcon( ":/img/down_22x22.png" ), tr( "Move down" ),
					this, SLOT( moveUnderCursorDown() ) );
	}

	menu.addAction( QIcon( ":/img/add_22x22.png" ), tr( "Add condition" ),
		this, SLOT( addCondition() ) );

	if( !d->m_model->isOtherwiseConditionExists() )
		menu.addAction( QIcon( ":/img/add_22x22.png" ), tr( "Add otherwise condition" ),
			this, SLOT( addOtherwiseCondition() ) );

	if( d->m_contextMenuRequestedIndex != -1 )
		menu.addAction( QIcon( ":/img/remove_22x22.png" ), tr( "Delete condition" ),
			this, SLOT( deleteUnderCursor() ) );

	menu.exec( event->globalPos() );

	event->accept();
}


//
// PropertiesWidgetPrivate
//

class PropertiesWidgetPrivate {
public:
	explicit PropertiesWidgetPrivate( Como::Source::Type valueType )
		:	m_valueType( valueType )
		,	m_conditions( 0 )
		,	m_priority( 0 )
	{
	}

	//! Type of the value.
	Como::Source::Type m_valueType;
	//! List with conditions.
	PropertiesList * m_conditions;
	//! Priority.
	QSpinBox * m_priority;
}; // class PropertiesWidgetPrivate


//
// PropertiesWidget
//

PropertiesWidget::PropertiesWidget( Como::Source::Type valueType,
	QWidget * parent, Qt::WindowFlags f )
	:	QWidget( parent, f )
	,	d( new PropertiesWidgetPrivate( valueType ) )
{
	init();
}

PropertiesWidget::~PropertiesWidget()
{
}

Properties
PropertiesWidget::properties() const
{
	Properties props = d->m_conditions->properties();

	props.setPriority( d->m_priority->value() );

	return props;
}

void
PropertiesWidget::setProperties( const Properties & p )
{
	d->m_priority->setValue( p.priority() );

	d->m_conditions->setProperties( p );
}

PropertiesList *
PropertiesWidget::conditionsList()
{
	return d->m_conditions;
}

void
PropertiesWidget::propertiesChanged()
{
	emit changed();
}

void
PropertiesWidget::propertiesWrong()
{
	emit wrongProperties();
}

void
PropertiesWidget::priorityChanged( int p )
{
	Q_UNUSED( p )

	if( d->m_conditions->isPropertiesOk() )
		emit changed();
}

void
PropertiesWidget::init()
{
	QVBoxLayout * vBox = new QVBoxLayout( this );

	QHBoxLayout * hBox = new QHBoxLayout();

	QLabel * label = new QLabel( this );
	label->setText( tr( "Priority" ) );
	hBox->addWidget(label);

	d->m_priority = new QSpinBox( this );
	d->m_priority->setMinimum(0 );
	d->m_priority->setMaximum( 999 );
	d->m_priority->setSingleStep( 1 );

	hBox->addWidget( d->m_priority );

	QSpacerItem * spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding,
		QSizePolicy::Minimum );

	hBox->addItem( spacer );

	vBox->addLayout( hBox );

	d->m_conditions = new PropertiesList( d->m_valueType, this );

	vBox->addWidget( d->m_conditions );

	connect( d->m_conditions, SIGNAL( wrongProperties() ),
		this, SLOT( propertiesWrong() ) );
	connect( d->m_conditions, SIGNAL( changed() ),
		this, SLOT( propertiesChanged() ) );
	connect( d->m_priority, SIGNAL( valueChanged(int) ),
		this, SLOT( priorityChanged( int ) ) );
}

} /* namespace Globe */

#include "properties_widget.moc"

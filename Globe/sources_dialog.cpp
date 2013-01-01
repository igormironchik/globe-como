
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
#include <Globe/sources_dialog.hpp>
#include <Globe/channels.hpp>
#include <Globe/sources.hpp>
#include <Globe/sources_widget.hpp>
#include <Globe/source_manual_dialog.hpp>

// Qt include.
#include <QtGui/QDialogButtonBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QFrame>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QPushButton>


namespace Globe {

//
// SourcesDialogPrivate
//

class SourcesDialogPrivate {
public:
	SourcesDialogPrivate( Como::Source & source, QString & channelName,
		SourcesManager * sourcesManager,
		ChannelsManager * channelsManager )
		:	m_source( source )
		,	m_channelName( channelName )
		,	m_sourcesManager( sourcesManager )
		,	m_channelsManager( channelsManager )
		,	m_widget( 0 )
		,	m_buttons( 0 )
		,	m_setManuallyButton( 0 )
	{
	}

	//! Source.
	Como::Source & m_source;
	//! Channel's name.
	QString & m_channelName;
	//! Sources manager.
	SourcesManager * m_sourcesManager;
	//! Channels manager.
	ChannelsManager * m_channelsManager;
	//! Widget.
	SourcesWidget * m_widget;
	//! Buttons.
	QDialogButtonBox * m_buttons;
	//! Set source manually button.
	QPushButton * m_setManuallyButton;
}; // class SourcesDialogPrivate


//
// SourcesDialog
//

SourcesDialog::SourcesDialog( Como::Source & source, QString & channelName,
	SourcesManager * sourcesManager,
	ChannelsManager * channelsManager,
	QWidget * parent, Qt::WindowFlags flags )
	:	QDialog( parent, flags )
	,	d( new SourcesDialogPrivate( source, channelName, sourcesManager,
			channelsManager ) )
{
	init();
}

SourcesDialog::~SourcesDialog()
{
}


void
SourcesDialog::init()
{
	QVBoxLayout * layout = new QVBoxLayout( this );

	d->m_widget = new SourcesWidget( d->m_sourcesManager, d->m_channelsManager,
		this );

	QSpacerItem * spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
		QSizePolicy::Expanding );

	QFrame * line = new QFrame( this );
	line->setFrameStyle( QFrame::HLine | QFrame::Sunken );

	d->m_buttons = new QDialogButtonBox(
		QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
		Qt::Horizontal, this );

	d->m_buttons->button( QDialogButtonBox::Ok )->setDefault( true );
	d->m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );

	d->m_setManuallyButton = new QPushButton( tr( "Set Manually" ), this );
	d->m_buttons->addButton( d->m_setManuallyButton,
		QDialogButtonBox::ActionRole );

	layout->addWidget( d->m_widget );
	layout->addSpacerItem( spacer );
	layout->addWidget( line );
	layout->addWidget( d->m_buttons );

	connect( d->m_widget, SIGNAL( sourceSelected( const Como::Source & ) ),
		this, SLOT( sourceSelected( const Como::Source & ) ) );
	connect( d->m_widget, SIGNAL( channelSelected( const QString & ) ),
		this, SLOT( channelSelected( const QString & ) ) );
	connect( d->m_buttons, SIGNAL( accepted() ),
		this, SLOT( accept() ) );
	connect( d->m_buttons, SIGNAL( rejected() ),
		this, SLOT( reject() ) );
	connect( d->m_setManuallyButton, SIGNAL( clicked() ),
		this, SLOT( setSourceManually() ) );
}

void
SourcesDialog::sourceSelected( const Como::Source & source )
{
	d->m_source = source;
	d->m_channelName = d->m_widget->channelName();

	d->m_buttons->button( QDialogButtonBox::Ok )->setEnabled( true );
}

void
SourcesDialog::channelSelected( const QString & channelName )
{
	Q_UNUSED( channelName )

	d->m_buttons->button( QDialogButtonBox::Ok )->setEnabled( false );
}

void
SourcesDialog::setSourceManually()
{
	SourceManualDialog dialog( d->m_source, d->m_channelName,
		d->m_sourcesManager, this );

	if( dialog.exec() == QDialog::Accepted )
		accept();
}

} /* namespace Globe */


/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// QTreeViewClient include.
#include "mainwindow.hpp"
#include "treeview.hpp"
#include "model.hpp"

// Qt include.
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QHostAddress>

// Como include.
#include <Como/ClientSocket>


//
// MainWindow::MainWindowPrivate
//

struct MainWindow::MainWindowPrivate {
	explicit MainWindowPrivate( Como::ClientSocket * socket )
		:	m_socket( socket )
		,	m_model( 0 )
	{}

	Como::ClientSocket * m_socket;
	Model * m_model;
}; // struct MainWindow::MainWindowPrivate


//
// MainWindow
//

MainWindow::MainWindow( Como::ClientSocket * socket,
	QWidget * parent, Qt::WindowFlags flags )
	:	QMainWindow( parent, flags )
	,	d( new MainWindowPrivate( socket ) )
{
	init();
}

MainWindow::~MainWindow()
{
}

void
MainWindow::init()
{
	QMenu * fileMenu = menuBar()->addMenu( tr( "File" ) );
	QAction * quitAction =
		fileMenu->addAction( tr( "Quit" ), this, SLOT( slotQuit() ) );
	quitAction->setShortcut( Qt::CTRL | Qt::Key_Q );

	d->m_model = new Model( d->m_socket, this );

	TreeView * treeView = new TreeView( d->m_model, this );
	treeView->setModel( d->m_model );

	setCentralWidget( treeView );

	connect( d->m_socket, &Como::ClientSocket::connected,
		this, &MainWindow::slotConnected );

	connect( d->m_socket, &Como::ClientSocket::disconnected,
		this, &MainWindow::slotDisconnected );

	slotDisconnected();
}

void
MainWindow::slotQuit()
{
	QApplication::quit();
}

void
MainWindow::slotConnected()
{
	d->m_socket->sendGetListOfSourcesMessage();
}

void
MainWindow::slotDisconnected()
{
	d->m_model->clear();
	d->m_socket->connectTo( QHostAddress::LocalHost, 4545 );
}

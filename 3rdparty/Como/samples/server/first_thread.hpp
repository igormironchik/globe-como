
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef COMO__SAMPLES__SERVER__FIRST_THREAD_HPP__INCLUDED
#define COMO__SAMPLES__SERVER__FIRST_THREAD_HPP__INCLUDED

// Qt include.
#include <QThread>
#include <QScopedPointer>
#include <QObject>


namespace Como {
	class ServerSocket;
} /* namespace Como */

//
// FirstObject
//

/*!
	This is our working object that will operate
	with Como::Source
*/
class FirstObject
	:	public QObject
{
	Q_OBJECT

public:
	explicit FirstObject( Como::ServerSocket * socket,
		QObject * parent = 0 );
	~FirstObject();

private slots:
	//! Switch to state #1.
	void slotSwitchToStateOne();
	//! Switch to state #2.
	void slotSwitchToStateTwo();
	//! Switch to state #3.
	void slotSwitchToStateThree();

private:
	struct FirstObjectPrivate;
	QScopedPointer< FirstObjectPrivate > d;
}; // class FirstObject


//
// FirstThread
//

//! First thread in the server.
class FirstThread
	:	public QThread
{
public:
	explicit FirstThread( Como::ServerSocket * socket,
		QObject * parent = 0 );
	~FirstThread();

protected:
	//! Run the thread.
	void run();

private:
	struct FirstThreadPrivate;
	QScopedPointer< FirstThreadPrivate > d;
}; // class FirstThread

#endif // COMO__SAMPLES__SERVER__FIRST_THREAD_HPP__INCLUDED


/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef COMO__SAMPLES__SERVER__SECOND_THREAD_HPP__INCLUDED
#define COMO__SAMPLES__SERVER__SECOND_THREAD_HPP__INCLUDED

// Qt include.
#include <QThread>
#include <QScopedPointer>
#include <QObject>


namespace Como {
	class ServerSocket;
} /* namespace Como */


//
// SecondObject
//

/*!
	This is our working object that will operate
	with Como::Source
*/
class SecondObject
	:	public QObject
{
	Q_OBJECT

public:
	explicit SecondObject( Como::ServerSocket * socket,
		QObject * parent = 0 );
	~SecondObject();

private slots:
	//! Switch to state #1.
	void slotSwitchToStateOne();
	//! Switch to state #2.
	void slotSwitchToStateTwo();
	//! Switch to state #3.
	void slotSwitchToStateThree();

private:
	struct SecondObjectPrivate;
	QScopedPointer< SecondObjectPrivate > d;
}; // class SecondObject


//
// SecondThread
//

//! First thread in the server.
class SecondThread
	:	public QThread
{
public:
	explicit SecondThread( Como::ServerSocket * socket,
		QObject * parent = 0 );
	~SecondThread();

protected:
	//! Run the thread.
	void run();

private:
	struct SecondThreadPrivate;
	QScopedPointer< SecondThreadPrivate > d;
}; // class SecondThread

#endif // COMO__SAMPLES__SERVER__SECOND_THREAD_HPP__INCLUDED

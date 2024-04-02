
/*
	SPDX-FileCopyrightText: 2012 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef COMO__SAMPLES__SERVER__THIRD_THREAD_HPP__INCLUDED
#define COMO__SAMPLES__SERVER__THIRD_THREAD_HPP__INCLUDED

// Qt include.
#include <QThread>
#include <QScopedPointer>
#include <QObject>


namespace Como {
	class ServerSocket;
} /* namespace Como */

//
// ThirdObject
//

/*!
	This is our working object that will operate
	with Como::Source
*/
class ThirdObject
	:	public QObject
{
	Q_OBJECT

public:
	explicit ThirdObject( Como::ServerSocket * socket,
		QObject * parent = 0 );
	~ThirdObject();

private slots:
	//! Switch to state #1.
	void slotSwitchToStateOne();
	//! Switch to state #2.
	void slotSwitchToStateTwo();
	//! Switch to state #3.
	void slotSwitchToStateThree();

private:
	struct ThirdObjectPrivate;
	QScopedPointer< ThirdObjectPrivate > d;
}; // class ThirdObject


//
// ThirdThread
//

//! First thread in the server.
class ThirdThread
	:	public QThread
{
public:
	explicit ThirdThread( Como::ServerSocket * socket,
		QObject * parent = 0 );
	~ThirdThread();

protected:
	//! Run the thread.
	void run();

private:
	struct ThirdThreadPrivate;
	QScopedPointer< ThirdThreadPrivate > d;
}; // class ThirdThread

#endif // COMO__SAMPLES__SERVER__THIRD_THREAD_HPP__INCLUDED

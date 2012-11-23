
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

#ifndef GLOBE__APPLICATION_CFG_HPP__INCLUDED
#define GLOBE__APPLICATION_CFG_HPP__INCLUDED

// Qt include.
#include <QtCore/QString>
#include <QtCore/QRect>

// QtConfFile include.
#include <QtConfFile/TagNoValue>
#include <QtConfFile/TagScalar>
#include <QtConfFile/ConstraintMinMax>


namespace Globe {

//
// ApplicationCfg
//

//! Configuration of the application.
class ApplicationCfg {
public:
	ApplicationCfg();

	~ApplicationCfg();

	ApplicationCfg( const ApplicationCfg & other );

	ApplicationCfg & operator = ( const ApplicationCfg & other );

	//! \return File name of the main window configuration.
	const QString & mainWindowCfgFile() const;
	//! Set file name of the main window configuration.
	void setMainWindowCfgFile( const QString & fileName );

	//! \return File name of the channels configuration.
	const QString & channelsCfgFile() const;
	//! Set file name of the channels configuration.
	void setChannelsCfgFile( const QString & fileName );

	//! \return Available screen geometry for findows.
	const QRect & availableScreenGeometry() const;
	//! Set available screen geometry for windows.
	void setAvailableScreenGeometry( const QRect & rect );

private:
	//! File name of the main window configuration.
	QString m_mainWindowCfgFileName;
	//! File name of the channels configuration.
	QString m_channelsCfgFileName;
	//! Available screen geometry for windows.
	QRect m_availableScreenGeometry;
}; // class ApplicationCfg


//
// AvailableScreenGeometryTag
//

//! Tag with available screen space for windows.
class AvailableScreenGeometryTag
	:	public QtConfFile::TagNoValue
{
public:
	AvailableScreenGeometryTag( QtConfFile::Tag & owner, const QString & name,
		bool isMandatory = false );

	AvailableScreenGeometryTag( const QRect & rect,
		QtConfFile::Tag & owner, const QString & name, bool isMandatory = false );

	//! \return Geometry.
	QRect geometry() const;

private:
	//! X.
	QtConfFile::TagScalar< int > m_x;
	//! Y.
	QtConfFile::TagScalar< int > m_y;
	//! Width.
	QtConfFile::TagScalar< int > m_width;
	//! Height.
	QtConfFile::TagScalar< int > m_height;
	//! Constraint for width and height.
	QtConfFile::ConstraintMinMax< int > m_constraint;
}; // class AvailableScreenGeometryTag


//
// ApplicationCfgTag
//

//! Tag with the application's configuration.
class ApplicationCfgTag
	:	public QtConfFile::TagNoValue
{
public:
	ApplicationCfgTag();

	explicit ApplicationCfgTag( const ApplicationCfg & cfg );

	//! \return Application's configuration.
	ApplicationCfg cfg() const;

private:
	//! File name of the main window configuration.
	QtConfFile::TagScalar< QString > m_mainWindowCfgFileName;
	//! File name of the channels configuration.
	QtConfFile::TagScalar< QString > m_channelsCfgFileName;
	//! Available screen geometry for windows.
	AvailableScreenGeometryTag m_availableScreenGeometry;
}; // class ApplicationCfgTag

} /* namespace Globe */

#endif // GLOBE__APPLICATION_CFG_HPP__INCLUDED

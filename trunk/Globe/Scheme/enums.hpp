
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

#ifndef GLOBE__SCHEME__ENUMS_HPP__INCLUDED
#define GLOBE__SCHEME__ENUMS_HPP__INCLUDED


namespace Globe {

namespace Scheme {

//
// SceneMode
//

//! Mode of the scene.
enum SceneMode {
	//! View scene.
	ViewScene = 0x00,
	//! Edit scene.
	EditScene = 0x01
}; // enum SceneMode


//
// EditSceneMode
//

//! Edit scene mode.
enum EditSceneMode {
	//! Select items on scene.
	EditSceneSelect = 0x01,
	//! Add new source.
	EditSceneNewSource = 0x02,
	//! Add new text block.
	EditSceneNewText = 0x03
}; // enum EditSceneMode


//
// ItemState
//

//! State of the item.
enum ItemState {
	//! Item selected.
	ItemSelected = 0x00,
	//! Item not selected.
	ItemNotSelected = 0x01
}; // enum ItemState


//
// ResizeMode
//

//! Resize mode.
enum ResizeMode {
	//! Resize mode is off.
	NoResize = 0x00,
	//! Resize mode is on.
	YesResize = 0x01,
	//! Resize to top left corner.
	ResizeTopLeft = 0x03,
	//! Resize to top right corner.
	ResizeTopRight = 0x05,
	//! Resize to bottom right corner.
	ResizeBottomRight = 0x09,
	//! Resize to bottom left corner.
	ResizeBottomLeft = 0x11
}; // enum ResizeMode

} /* namespace Scheme */

} /* namespace Globe */

#endif // GLOBE__SCHEME__ENUMS_HPP__INCLUDED

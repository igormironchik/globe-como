
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012-2017 Igor Mironchik

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

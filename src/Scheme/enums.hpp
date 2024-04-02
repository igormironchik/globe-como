
/*
	SPDX-FileCopyrightText: 2012-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: GPL-3.0-or-later
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
	EditSceneNewText = 0x03,
	//! Add new aggregate.
	EditSceneNewAggregate = 0x04
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

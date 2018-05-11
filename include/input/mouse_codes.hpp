/* Copyright (C) 
 * 2017 - Arden Rasmussen
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */
/**
 * @file mouse_codes.hpp
 * @brief Mouse event codes.
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2017-12-12
 */
#ifndef TUI_INPUT_MOUSE_CODES_HPP_
#define TUI_INPUT_MOUSE_CODES_HPP_

namespace tui {
  /**
   * @brief Mouse event codes.
   */
  enum MouseCodes{
    MOUSE_ERR = 0, //!< No mouse event
    MOUSE_BUTTON_NONE = 1, //!< No mouse button
    MOUSE_BUTTON_LEFT = 2, //!< Left mouse button
    MOUSE_BUTTON_RIGHT = 3, //!< Right mouse button
    MOUSE_BUTTON_MIDDLE = 4, //!< Middle mouse button
    MOUSE_SCROLL_UP = 5, //!< Scroll up
    MOUSE_SCROLL_DOWN = 6, //!< Scroll down
    MOUSE_MOVE = 7, //!< Mouse movement
    MOUSE_BUTTON_DOWN = 8, //!< Mouse button press
    MOUSE_BUTTON_UP = 9 //!< Mouse button release
  };
} // namespace tui

#endif  // TUI_INPUT_MOUSE_CODES_HPP_

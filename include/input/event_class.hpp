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
 * @file event_class.hpp
 * @brief Event class structures
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2017-12-11
 */
#ifndef TUI_INPUT_EVENT_CLASS_HPP_
#define TUI_INPUT_EVENT_CLASS_HPP_

#include "keys.hpp"
#include "mouse_codes.hpp"

namespace tui {
  /**
   * @brief Type of event.
   */
  enum EventType { NONE_EVENT = 0, MOUSE_EVENT = 1, KEYBOARD_EVENT = 2 };

  /**
   * @brief Event data structure.
   * All events are reported as an event structure, containing different data values.
   */
  struct Event {
   public:
     /**
      * @brief Mouse event data structure.
      *
      * Stores the data relevant from a mouse event.
      */
    struct MouseEvent {
     public:
       /**
        * @brief Type of mouse event.
        */
      MouseCodes type = MOUSE_ERR;
      /**
       * @brief Button associated with mouse event.
       */
      MouseCodes button = MOUSE_BUTTON_NONE;
      /**
       * @brief Mouse x position.
       */
      unsigned int x = 0;
      /**
       * @brief Mouse y position.
       */
      unsigned int y = 0;
    };
    /**
     * @brief Keyboard event data structure.
     *
     * Stores the data relevant from a keyboard event.
     */
    struct KeyboardEvent {
     public:
       /**
        * @brief Key code pressed.
        *
        * @sa tui::KeyCodes
        */
       unsigned int key = KEY_ERR;
    };
    /**
     * @brief Event type
     * @sa EventType
     */
    EventType type = NONE_EVENT;
    /**
     * @brief Mouse event data.
     */
    MouseEvent mouse;
    /**
     * @brief Keyboard event data.
     */
    KeyboardEvent keyboard;
  };
}  // namespace tui

#endif  // TUI_INPUT_EVENT_CLASS_HPP_

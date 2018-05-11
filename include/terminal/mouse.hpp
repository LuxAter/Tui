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
 * @file mouse.hpp
 * @brief Mouse interfacing structure.
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2017-12-10
 */

#ifndef TUI_TERMINAL_MOUSE_HPP_
#define TUI_TERMINAL_MOUSE_HPP_

namespace tui {

  /**
   * @brief Defines the enabled mouse reporting system.
   *
   * Defines the different options for mouse reporting systems that are
   * avaliable in the API.
   */
  enum MouseReporting {
    MOUSE_NONE = 0, //!< No mouse reporting.
    MOUSE_REPORTING = 1, //!< Reports on button press and release.
    MOUSE_HIGHLIGHT = 2, //!< Useful for reporting mouse highlighting.
    MOUSE_BUTTON_MOVEMENT = 3, //!< Reports movement when a button is pressed.
    MOUSE_MOVEMENT = 4 //!< Reports all movement.
  };

  /**
   * @brief Enables provided method of mouse reporting.
   *
   * @param report_method Method of mouse reporting to enable.
   */
  void EnabledMouse(MouseReporting report_method = MOUSE_REPORTING);
  /**
   * @brief Disables provided method of mouse reporting.
   *
   * @param report_method Method of mouse reporting to disable.
   */
  void DisableMouse(MouseReporting report_method = MOUSE_REPORTING);

}  // namespace tui

#endif  // TUI_TERMINAL_MOUSE_HPP_
